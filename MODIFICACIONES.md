# Aviso de modificaciones — GECKO Lite W

**Versión 1.0.0 · EDX_LAB · 18 de octubre de 2026.** Este proyecto es una versión
modificada de **Bruce**, adaptada por **EDX_LAB** para el hardware GECKO Lite W. No se presenta
como una versión original o una publicación oficial del proyecto Bruce.

Se conservan los créditos de los autores originales en README_UPSTREAM.md,
los avisos presentes en el código, LICENSE y THIRD_PARTY.md. El inventario específico de esta adaptación se
encuentra en THIRD_PARTY_NOTICES.md. LICENSE contiene
la GNU Affero General Public License, versión 3. THIRD_PARTY.md identifica la
licencia de Bruce como AGPL-3.0-or-later. Las bibliotecas de terceros conservan
sus propios avisos y licencias.

## Modificaciones de la adaptación

- Entorno único ESP32-S3-N16R8: flash de 16 MB, PSRAM OPI de 8 MB y particiones propias del proyecto.
- Pinout de pantalla ST7789V, SD con bus separado, joystick, B1/B2, buzzer y medida de batería; reset TFT en GPIO 8 y orden de color BGR.
- Retirada de módulos externos y funciones exclusivas RF/sub-GHz, NRF24, LoRa, FM, IR, GPS, NFC/RFID, Ethernet y RTC externo, conservando Wi-Fi/BLE, USB y extras aplicables.
- Intro desde /boot.gif en SD y nombres visibles Gecko, manteniendo referencias al origen Bruce y rutas/API compatibles.
- Indicador de batería y calibración de extremos bajo/lleno persistente en NVS.
- Filtrado de botones a 40 ms y aceptación por pulsación, conservando pulsación larga en el explorador.
- Compilación portable: dependencias fijadas, generación local de WebUI, cabeceras JavaScript correspondientes y empaquetado con checksums.
- Manual e instrucciones en español y flujo de compilación para GitHub Actions.

Este aviso identifica las principales modificaciones respecto a Bruce. Los detalles de implementación se encuentran en el código fuente correspondiente a esta versión.

