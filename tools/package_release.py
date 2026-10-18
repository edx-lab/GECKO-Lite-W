"""Package a newly built merged image with installation instructions and a checksum."""
from pathlib import Path
import hashlib
import shutil
import zipfile

ROOT = Path(__file__).resolve().parents[1]


def main():
    image = ROOT / "Gecko-esp32-s3-n16r8.bin"
    application = ROOT / ".pio/build/esp32-s3-n16r8/firmware.bin"
    if not image.is_file() or not application.is_file():
        raise SystemExit("Build first: python -m platformio run -e esp32-s3-n16r8")
    if image.stat().st_mtime < application.stat().st_mtime:
        raise SystemExit("Merged image is older than firmware.bin; rebuild before packaging")
    payload = image.read_bytes()
    if payload[:1] != b"\xe9" or payload[0x10000:0x10001] != b"\xe9":
        raise SystemExit("Expected ESP32-S3 merged image with application at 0x10000")
    app_bytes = application.read_bytes()
    if payload[0x10000:0x10000 + len(app_bytes)] != app_bytes:
        raise SystemExit("Merged image and firmware.bin do not belong to the same build")
    output = ROOT / "dist"
    output.mkdir(exist_ok=True)
    images = [image, application, application.parent / "bootloader.bin", application.parent / "partitions.bin"]
    for path in images:
        if not path.is_file():
            raise SystemExit(f"Missing build output: {path}")
    copied = []
    for path in images:
        destination = output / path.name
        shutil.copy2(path, destination)
        copied.append(destination)
    checksum = output / "SHA256SUMS.txt"
    checksum.write_text("".join(f"{hashlib.sha256(path.read_bytes()).hexdigest()}  {path.name}\n"
                                for path in copied), encoding="ascii")
    instructions = ROOT / "INSTALACION.md"
    archive = output / "Gecko-Lite-W-firmware.zip"
    with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED) as bundle:
        for path in (*copied, checksum, instructions, ROOT / "MANUAL_USUARIO_GECKO.md",
                     ROOT / "LICENSE", ROOT / "THIRD_PARTY.md"):
            bundle.write(path, path.name)
        bundle.write(ROOT / "boards/esp32-s3-n16r8/README.md", "boards/esp32-s3-n16r8/README.md")
    print(f"Release package: {archive}")


if __name__ == "__main__":
    main()
