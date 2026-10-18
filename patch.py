"""Prepare Gecko builds without online minifiers or shell-dependent paths."""
from pathlib import Path
import gzip
import hashlib
import os
import shutil
import subprocess

Import("env")


def prepare_wifi_library():
    platform = env.PioPlatform()
    package = platform.get_package_dir("framework-arduinoespressif32-libs")
    mcu = env.BoardConfig().get("build.mcu", "")
    directory = Path(package) / mcu / "lib"
    marker = directory / ".patched"
    if marker.exists():
        return
    original = directory / "libnet80211.a"
    if not original.is_file():
        raise RuntimeError(f"Missing Wi-Fi archive: {original}")
    suffix = ".exe" if os.name == "nt" else ""
    compiler = platform.get_package_dir("toolchain-xtensa-esp-elf")
    if not compiler:
        compiler = platform.get_package_dir(f"toolchain-xtensa-{mcu}")
    if not compiler:
        raise RuntimeError("PlatformIO did not install the ESP32-S3 toolchain")
    objcopy = Path(compiler) / "bin" / f"xtensa-{mcu}-elf-objcopy{suffix}"
    temporary = directory / "libnet80211.a.gecko-tmp"
    subprocess.run([str(objcopy), "--weaken-symbol=ieee80211_raw_frame_sanity_check",
                    str(original), str(temporary)], check=True)
    if not temporary.is_file() or not temporary.stat().st_size:
        raise RuntimeError("Wi-Fi patch produced no archive")
    backup = directory / "libnet80211.a.old"
    if not backup.exists():
        shutil.copy2(original, backup)
    os.replace(temporary, original)
    marker.write_text("Gecko Lite W\n", encoding="utf-8")


def prepare_www_files():
    root = Path(env.subst("$PROJECT_DIR"))
    assets = root / "embedded_resources" / "web_interface"
    header = root / "include" / "webFiles.h"
    stamp = assets / "checksum.sha256"
    files = sorted(p for p in assets.iterdir() if p.suffix in (".html", ".css", ".js"))
    if not files:
        raise RuntimeError(f"Missing WebUI source files: {assets}")
    digest = hashlib.sha256(b"gecko-web-v1\n")
    contents = []
    for path in files:
        data = path.read_bytes().replace(b"\r\n", b"\n")
        contents.append((path, data))
        digest.update(path.name.encode("utf-8") + b"\0" + data + b"\0")
    checksum = digest.hexdigest()
    if header.exists() and stamp.exists() and stamp.read_text().strip() == checksum:
        print("[Gecko WebUI] Up to date")
        return
    output = ["#ifndef WEB_FILES_H\n#define WEB_FILES_H\n#include <Arduino.h>\n",
              "// Generated from embedded_resources/web_interface; do not edit.\n"]
    for path, data in contents:
        compressed = gzip.compress(data, mtime=0)
        name = path.name.replace(".", "_")
        output.append(f"const uint8_t {name}[] PROGMEM = {{\n")
        for start in range(0, len(compressed), 15):
            output.append("  " + ", ".join(f"0x{value:02X}" for value in compressed[start:start+15]) + ",\n")
        output.append(f"}};\nconst uint32_t {name}_size = {len(compressed)};\n")
    output.append("#endif\n")
    header.parent.mkdir(parents=True, exist_ok=True)
    temporary = header.with_suffix(".h.tmp")
    temporary.write_text("".join(output), encoding="utf-8", newline="\n")
    os.replace(temporary, header)
    stamp.write_text(checksum, encoding="ascii")
    print(f"[Gecko WebUI] Embedded {len(files)} files locally (no external service)")


prepare_wifi_library()
prepare_www_files()
