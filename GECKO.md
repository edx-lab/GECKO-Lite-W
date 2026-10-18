# Gecko Lite W

Consulta el [manual de usuario completo en español](MANUAL_USUARIO_GECKO.md), con funciones, ejemplos, controles y solución de problemas.

GECKO Lite W es una adaptación de Bruce centrada en Wi-Fi y Bluetooth LE, con
USB, multimedia, extras, scripts, almacenamiento, pantalla y ajustes.

Se han retirado RF/sub-GHz, NRF24, LoRa, FM, infrarrojos, GPS, NFC/RFID y el
controlador Ethernet, junto con sus menús, comandos serie, interfaces JavaScript,
ajustes y dependencias exclusivas. También se ha retirado de BLE Suite la opción
`Jam & Connect (NRF24)` y el código de jamming que utilizaba ese accesorio.

Se han eliminado los controladores RTC externos BM8563 y PCF85063A (`lib/RTC`),
su inicialización y todas las ramas de código que los utilizaban. Se conservan
`ESP32Time`, `NTPClient` y las funciones de hora por software: no necesitan un
chip RTC. Tras un apagado completo, la hora guardada no cuenta el tiempo sin
alimentación; se corrige por Wi-Fi/NTP o manualmente.

El escáner de equipos Wi-Fi y sus utilidades compartidas se conservan en
`src/core/network/`; no necesitan un módulo Ethernet. Las funciones Wi-Fi y BLE
restantes utilizan la radio integrada del ESP32 y, cuando procede, la SD.

## Hardware configurado

- ESP32-S3-N16R8: 16 MB de flash y 8 MB de PSRAM.
- Lector SD y TFT ST7789V de 2 pulgadas, 240×320, formato RGB565 y orden BGR.
- Joystick de cinco direcciones y dos botones adicionales.
- Entrada ADC en GPIO 1 con divisor 100k/100k y buzzer en GPIO 38.

`platformio.ini` contiene únicamente el entorno `esp32-s3-n16r8`, con flash de
16 MB y PSRAM OPI de 8 MB. La configuración de placa, Docker y el workflow
de compilación utilizan este entorno; no incluye perfiles de otras placas
ni tablas de particiones de 4 u 8 MB.

El [pinout y los controles](boards/esp32-s3-n16r8/README.md) están implementados
en `boards/esp32-s3-n16r8/`. La pantalla usa HSPI y la SD, FSPI. B1 y el centro
del joystick aceptan; B2 vuelve atrás al soltarlo y reinicia tras 3 segundos.
BL va directo a 3,3 V, sin regulación de brillo. USB, multimedia y las funciones
Wi-Fi/BLE se conservan en el código.

## Intro de arranque

Coloca `boot.gif` en la raíz de la SD (`/boot.gif`). Se reproduce una vez,
centrado y a su tamaño original; cualquier botón permite saltarlo. Si no hay
SD o no se puede abrir el GIF, el arranque continúa sin intro. La imagen
de arranque se obtiene únicamente de `/boot.gif` en SD.
La opción de arranque instantáneo sigue omitiendo la intro.

## Compatibilidad y validación

La compilación en Windows está verificada. El workflow de GitHub Actions incluye
Windows y Linux; la ejecución de Linux no está verificada. Las cabeceras
JavaScript incluidas permiten compilar esta versión sin instalar GCC nativo.
No se acredita una validación física completa de todas las funciones.
Consulta [la verificación de la versión](VERIFICACION_PUBLICACION.md).

Consulta [instalación](INSTALACION.md) para compilar e instalar el firmware.

## Identidad Gecko

Los menús, anuncios Wi-Fi/BLE, USB y WebUI usan Gecko. La información del dispositivo conserva el crédito al firmware Bruce. WebUI: `http://gecko.local`. Valores iniciales: AP `GeckoNet` / `geckonet`; WebUI `admin` / `gecko`. Las credenciales guardadas se conservan durante actualizaciones que no sobrescriban su almacenamiento. Las rutas de la SD, formatos de archivos y API de scripts conservan sus nombres compatibles con Bruce. El binario combinado se genera como `Gecko-esp32-s3-n16r8.bin`. Para conservar NVS y calibración al actualizar, consulta INSTALACION.md y utiliza Upload de PlatformIO o la aplicación separada con las mismas particiones.
