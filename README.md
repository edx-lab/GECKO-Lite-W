# Gecko Lite W

Firmware para **Gecko Lite W con ESP32-S3-N16R8** (16 MB flash, 8 MB PSRAM), pantalla ST7789V, SD, joystick, dos botones y buzzer. Adaptación de Bruce centrada en Wi-Fi y Bluetooth LE, conservando USB, archivos, scripts y extras.

Este repositorio contiene el **código fuente completo de la adaptación GECKO
Lite W**, con las modificaciones de EDX_LAB y los archivos necesarios para compilar
mediante PlatformIO. El ZIP de Releases es el paquete de instalación para usuarios;
no sustituye a las fuentes del repositorio.

Versión de lanzamiento: **v1.0.0**. El identificador interno del firmware es
**dev**. Consulta las [notas de la versión](RELEASE_NOTES_v1.0.0.md).

## Descargar e instalar

- **Para instalarlo:** descarga `GECKO-Lite-W-v1.0.0-firmware.zip` y `SHA256SUMS.txt` desde la [Release v1.0.0](https://github.com/edx-lab/GECKO-Lite-W/releases/tag/v1.0.0). El paquete incluye los binarios, el manual y las instrucciones. El binario completo se escribe en **0x0**; consulta [INSTALACION.md](INSTALACION.md) antes de actualizar un equipo con ajustes guardados.
- **Para compilarlo:** utiliza **Source code (zip)** o **Source code (tar.gz)** de esa misma Release, o clona el repositorio. Abre la carpeta que contiene `platformio.ini` en PlatformIO. Las dependencias externas se descargan al compilar y las bibliotecas locales están incluidas en `lib/`.

Consulta [INSTALACION.md](INSTALACION.md) para instrucciones detalladas y comandos. Necesitas internet y Git al preparar dependencias desde el código. PlatformIO genera localmente la carpeta de trabajo `.pio/`.

## Documentación

- [Manual de usuario en español](MANUAL_USUARIO_GECKO.md): funciones, ejemplos y problemas frecuentes.
- [Hardware y pinout](boards/esp32-s3-n16r8/README.md).
- [Características de la adaptación](GECKO.md).
- [Bibliotecas, atribuciones y licencias](THIRD_PARTY_NOTICES.md).

Este binario requiere el hardware y pinout indicados. Una placa ESP32 diferente puede necesitar cambios de memoria, pantalla y conexiones.

## Compilación por consola

Con Python 3.12 y Git instalados, desde la raíz:

```sh
python -m pip install -r requirements-build.txt
python -m platformio run -e esp32-s3-n16r8
python tools/package_release.py
```

El binario completo se genera como `Gecko-esp32-s3-n16r8.bin` y el paquete distribuible en `dist/`. Las dependencias se definen en `platformio.ini`; los recursos web se generan localmente durante la compilación.

El entorno de compilación se ha probado en Windows. Para otras plataformas y para el uso en hardware distinto del descrito, consulta las instrucciones y los requisitos de compatibilidad.

## Créditos y licencia

Basado en **Bruce**. Se conserva su [documentación original](README_UPSTREAM.md),
la [licencia GNU AGPL versión 3](LICENSE) y los [avisos de terceros](THIRD_PARTY.md),
que identifican la licencia de Bruce como AGPL-3.0-or-later. Las aportaciones de EDX_LAB
se identifican en [MODIFICACIONES.md](MODIFICACIONES.md). La documentación original
describe otras placas y funciones que no forman parte de Gecko Lite W.

El [inventario específico](THIRD_PARTY_NOTICES.md) distingue las licencias
acreditadas de las no identificadas. La licencia general no sustituye las
condiciones de terceros.
