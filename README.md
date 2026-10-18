# Gecko Lite W

Firmware para **Gecko Lite W con ESP32-S3-N16R8** (16 MB flash, 8 MB PSRAM), pantalla ST7789V, SD, joystick, dos botones y buzzer. Adaptación de Bruce centrada en Wi-Fi y Bluetooth LE, conservando USB, archivos, scripts y extras.

Este repositorio contiene el **código fuente completo de la adaptación GECKO
Lite W**, con las modificaciones de EDX_LAB y los archivos necesarios para compilar
mediante PlatformIO. El ZIP de Releases es el paquete de instalación para usuarios;
no sustituye a las fuentes del repositorio.

Versión de lanzamiento: **v1.0.0**. El identificador interno del firmware es
**dev**. Consulta las [notas de la versión](RELEASE_NOTES_v1.0.0.md).

## Descargar e instalar

- **Para usarlo:** descarga `GECKO-Lite-W-v1.0.0-firmware.zip` y `SHA256SUMS.txt` de la Release v1.0.0. Incluye el binario completo, instrucciones y manual. Se carga en **0x0**. Las compilaciones de Actions tienen sus propios paquetes y checksums.
- **Para compilarlo:** descarga `GECKO-Lite-W-v1.0.0-source.zip`, el archivo de fuentes de la etiqueta v1.0.0 o clona el repositorio completo. Abre la carpeta con platformio.ini en PlatformIO. Las dependencias externas se instalan automáticamente; las librerías modificadas de lib se incluyen en Git.

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

El binario completo se genera como Gecko-esp32-s3-n16r8.bin y el paquete distribuible en dist. El flujo de Actions hace una compilación desde cero en Windows y Linux y adjunta los paquetes; no publica automáticamente una Release.

Las revisiones externas están fijadas en platformio.ini. La web se genera localmente sin minificadores externos. Las cabeceras JavaScript generadas se incluyen para no exigir un compilador nativo al usuario que solo compila esta revisión sin modificar la API.

**Compatibilidad de compilación:** verificada en Windows. El workflow también
incluye Linux, cuya ejecución no está verificada. La validación física completa
de todas las funciones no está acreditada. Consulta [la verificación de la versión](VERIFICACION_PUBLICACION.md).

## Créditos y licencia

Basado en **Bruce**. Se conserva su [documentación original](README_UPSTREAM.md),
la [licencia GNU AGPL versión 3](LICENSE) y los [avisos de terceros](THIRD_PARTY.md),
que identifican la licencia de Bruce como AGPL-3.0-or-later. Las aportaciones de EDX_LAB
se identifican en [MODIFICACIONES.md](MODIFICACIONES.md). La documentación original
describe otras placas y funciones que no forman parte de Gecko Lite W.

El [inventario específico](THIRD_PARTY_NOTICES.md) distingue las licencias
acreditadas de las no identificadas. La licencia general no sustituye las
condiciones de terceros.
