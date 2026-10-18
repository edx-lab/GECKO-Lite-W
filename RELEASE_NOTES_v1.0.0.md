# GECKO Lite W v1.0.0

Firmware para GECKO Lite W con ESP32-S3-N16R8, derivado de Bruce y adaptado
por EDX_LAB al hardware descrito en este repositorio.

## Versión

Versión de lanzamiento: **v1.0.0**. La cadena interna del firmware indica **dev**.
Los hashes de las fuentes y los cuatro binarios están documentados en
[RELEASE_SOURCE_MANIFEST.json](RELEASE_SOURCE_MANIFEST.json).

## Descargas e instalación

- `GECKO-Lite-W-v1.0.0-firmware.zip`: los cuatro binarios, sus checksums, manual, instrucciones y avisos de terceros.
- `SHA256SUMS.txt`: hash SHA-256 del paquete de firmware.
- **Source code (zip)** y **Source code (tar.gz)**: archivos de fuentes generados automáticamente por GitHub a partir del tag `v1.0.0`.

El paquete de firmware incluye su propio `SHA256SUMS.txt` para los cuatro
binarios. Los nombres originales de los `.bin` se conservan.

Los archivos de código fuente incluyen la configuración del proyecto, sus
bibliotecas locales y la documentación. Las dependencias externas declaradas
en `platformio.ini` se descargan al compilar y no están incluidas en esos archivos.

El binario completo se escribe en **0x0**. Para actualizar una instalación con
las mismas particiones conservando ajustes y calibración en NVS, utiliza
`firmware.bin` en **0x10000** o Upload de PlatformIO. Consulta
[INSTALACION.md](INSTALACION.md) antes de instalar.

Las fuentes correspondientes están en la misma etiqueta **v1.0.0**.

## Créditos y licencias

Basado en Bruce. Se conservan [LICENSE](LICENSE), los
[créditos originales](README_UPSTREAM.md) y [THIRD_PARTY.md](THIRD_PARTY.md).
Las modificaciones de EDX_LAB se describen en
[MODIFICACIONES.md](MODIFICACIONES.md). El
[inventario de terceros](THIRD_PARTY_NOTICES.md) recoge las licencias
identificadas y los componentes sin licencia identificada.
