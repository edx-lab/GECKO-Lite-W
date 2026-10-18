# Verificación de GECKO Lite W v1.0.0

Versión de lanzamiento: **v1.0.0**. Identificador interno del firmware: **dev**.

## Fuentes y binarios

El paquete `GECKO-Lite-W-v1.0.0-firmware.zip` contiene los cuatro binarios, sus
checksums, instrucciones, manual, documentación de hardware y avisos de
licencia. El repositorio contiene las fuentes, bibliotecas locales, recursos
y configuración necesarios para compilar mediante PlatformIO. El paquete
`GECKO-Lite-W-v1.0.0-source.zip` contiene ese mismo árbol del proyecto.

Las 617 entradas identificadas en
[RELEASE_SOURCE_MANIFEST.json](RELEASE_SOURCE_MANIFEST.json) coinciden con
las fuentes de la compilación verificada. Los cuatro binarios del paquete
tienen los siguientes SHA-256:

| Archivo | SHA-256 |
|---|---|
| `Gecko-esp32-s3-n16r8.bin` | `67076e97131e97ca2c48e7a0da2cb150deaf5f5a32a7faf8781d442095d93695` |
| `firmware.bin` | `4519e90263c951274caa6315211a4236195426bdd3f94037fc4a4184df4eb5de` |
| `bootloader.bin` | `e0bc59928d2e4d928eea7a8d61b4008fcb1758edcd694a792394c0c882a56fa9` |
| `partitions.bin` | `8ba38283c69e4f31707e425089152391603a27ab336b94fb27833e46e04d74c0` |

La aplicación del binario combinado, a partir de 0x10000, coincide con
`firmware.bin`. El archivo `SHA256SUMS.txt` adjunto a la Release identifica
ambos ZIP. Dentro del paquete de firmware, otro `SHA256SUMS.txt` identifica
los cuatro `.bin`.

## Validación

Compilación limpia correcta en Windows el **18 de octubre de 2026**.
También se verificaron los scripts de preparación y empaquetado y se realizó
una auditoría estática de 253 archivos. El workflow incluye Windows y Linux;
la ejecución de Linux no está verificada. No se acredita una validación
física completa de todas las funciones.

La correspondencia entre fuentes y binarios se comprobó contra los archivos
y registros de la compilación conservada. No es una atestación firmada durante
el build ni una demostración de recompilación reproducible bit a bit.

## Hardware

- Pantalla ST7789V: reset en GPIO8, orden de canales BGR, formato RGB565.
- Antirrebote de botones: 40 ms.
- Calibración de batería baja y llena almacenada en NVS.

Consulta el [pinout completo](boards/esp32-s3-n16r8/README.md) y las
[instrucciones de instalación](INSTALACION.md). Para conservar NVS al actualizar
con las mismas particiones, utiliza `firmware.bin` en 0x10000 o Upload de
PlatformIO. La imagen completa en 0x0 puede sobrescribir ajustes y calibración.

## Atribuciones

La licencia general del firmware es AGPLv3, con la declaración original de
Bruce AGPL-3.0-or-later. Las condiciones particulares de terceros se detallan
en [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md). Se conservan los
[avisos históricos](THIRD_PARTY.md), [créditos originales](README_UPSTREAM.md)
y el [aviso de modificaciones de EDX_LAB](MODIFICACIONES.md).
