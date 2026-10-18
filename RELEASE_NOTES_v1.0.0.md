# GECKO Lite W v1.0.0

Firmware para GECKO Lite W con ESP32-S3-N16R8, derivado de Bruce y adaptado
por EDX_LAB al hardware descrito en este repositorio.

## Versión

Versión de lanzamiento: **v1.0.0**. La cadena interna del firmware indica **dev**.
Los hashes de las fuentes y los cuatro binarios están documentados en
[RELEASE_SOURCE_MANIFEST.json](RELEASE_SOURCE_MANIFEST.json).

## Descargas e instalación

- `GECKO-Lite-W-v1.0.0-firmware.zip`: los cuatro binarios, sus checksums, manual, instrucciones y avisos de terceros.
- `GECKO-Lite-W-v1.0.0-source.zip`: código fuente completo, configuración y bibliotecas locales correspondientes a esta versión.
- `SHA256SUMS.txt`: hashes SHA-256 de ambos paquetes ZIP.

El paquete de firmware incluye su propio `SHA256SUMS.txt` para los cuatro
binarios. Los nombres originales de los `.bin` se conservan.

GitHub ofrece también archivos de fuentes ZIP y tar.gz de la etiqueta. El ZIP
fuente adjunto contiene los mismos archivos del proyecto; no incluye
dependencias externas descargadas ni herramientas adicionales. Permite
verificar esta copia de distribución con el checksum adjunto.

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
