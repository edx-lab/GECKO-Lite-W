"""Offline checks for resources excluded from Git and paths containing spaces."""
import ast
import importlib.util
import gzip
from pathlib import Path
import re
import subprocess
import tempfile
import unittest
import zipfile
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]


def build_helpers(env):
    tree = ast.parse((ROOT / "patch.py").read_text(encoding="utf-8"))
    # Load the real functions, without running PlatformIO's top-level hooks.
    tree.body = [node for node in tree.body if isinstance(node, (ast.Import, ast.ImportFrom, ast.FunctionDef))]
    namespace = {"env": env}
    exec(compile(tree, "patch.py", "exec"), namespace)
    return namespace


class BuildScriptTests(unittest.TestCase):
    def test_release_package_rejects_mixed_builds_and_includes_images(self):
        spec = importlib.util.spec_from_file_location("package_release", ROOT / "tools/package_release.py")
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        with tempfile.TemporaryDirectory(prefix="Gecko release ") as directory:
            root = Path(directory)
            module.ROOT = root
            build = root / ".pio/build/esp32-s3-n16r8"
            build.mkdir(parents=True)
            app = b"\xe9application"
            (build / "firmware.bin").write_bytes(app)
            for name in ("bootloader.bin", "partitions.bin"):
                (build / name).write_bytes(b"test data")
            image = root / "Gecko-esp32-s3-n16r8.bin"
            image.write_bytes(b"\xe9" + b"\xff" * 65535 + app)
            for name in ("INSTALACION.md", "MANUAL_USUARIO_GECKO.md", "LICENSE", "THIRD_PARTY.md"):
                (root / name).write_text("test documentation", encoding="utf-8")
            pinout = root / "boards/esp32-s3-n16r8/README.md"
            pinout.parent.mkdir(parents=True)
            pinout.write_text("pinout", encoding="utf-8")
            module.main()
            with zipfile.ZipFile(root / "dist/Gecko-Lite-W-firmware.zip") as archive:
                self.assertIsNone(archive.testzip())
                self.assertEqual(archive.read("firmware.bin"), app)
                self.assertIn("SHA256SUMS.txt", archive.namelist())
            image.write_bytes(b"\xe9" + b"\xff" * 65535 + b"\xe9mismatched!")
            with self.assertRaisesRegex(SystemExit, "same build"):
                module.main()

    def test_web_regenerates_missing_header_and_round_trips_utf8(self):
        with tempfile.TemporaryDirectory(prefix="Gecko clean download ") as directory:
            root = Path(directory)
            source = root / "embedded_resources/web_interface"
            source.mkdir(parents=True)
            data = "<title>Gecko español</title>\r\n".encode("utf-8")
            (source / "index.html").write_bytes(data)

            class Env:
                def subst(self, value):
                    return str(root)

            helper = build_helpers(Env())["prepare_www_files"]
            helper()
            header = root / "include/webFiles.h"
            first = header.read_bytes()
            body = re.search(rb"PROGMEM = \{(.*?)\};", first, re.S).group(1)
            compressed = bytes(int(value, 16) for value in re.findall(rb"0x([0-9A-F]{2})", body))
            self.assertEqual(gzip.decompress(compressed), data.replace(b"\r\n", b"\n"))
            header.unlink()  # Git excludes this file even when the checksum exists.
            helper()
            self.assertEqual(first, header.read_bytes())
            (source / "index.html").write_bytes(b"<title>Changed</title>")
            helper()
            self.assertNotEqual(first, header.read_bytes())

    def test_wifi_patch_failure_preserves_archive(self):
        with tempfile.TemporaryDirectory(prefix="Gecko package path ") as directory:
            root = Path(directory)
            archive = root / "esp32s3/lib/libnet80211.a"
            archive.parent.mkdir(parents=True)
            archive.write_bytes(b"original archive")

            class Env:
                def PioPlatform(self):
                    return self

                def BoardConfig(self):
                    return {"build.mcu": "esp32s3"}

                def get_package_dir(self, name):
                    return str(root)

            helper = build_helpers(Env())["prepare_wifi_library"]
            with patch("subprocess.run", side_effect=subprocess.CalledProcessError(1, "objcopy")):
                with self.assertRaises(subprocess.CalledProcessError):
                    helper()
            self.assertEqual(archive.read_bytes(), b"original archive")
            self.assertFalse((archive.parent / ".patched").exists())

            def objcopy(args, check):
                self.assertIsInstance(args, list)
                self.assertEqual(args[-2], str(archive))
                Path(args[-1]).write_bytes(b"patched archive")

            with patch("subprocess.run", side_effect=objcopy):
                helper()
            self.assertEqual(archive.read_bytes(), b"patched archive")
            self.assertEqual(archive.with_suffix(".a.old").read_bytes(), b"original archive")


if __name__ == "__main__":
    unittest.main()
