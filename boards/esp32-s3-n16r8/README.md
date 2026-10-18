# Gecko Lite W — ESP32-S3-N16R8

Única placa y entorno: `esp32-s3-n16r8`.

- Flash QIO de 16 MB, PSRAM OPI de 8 MB y CPU a 240 MHz.
- USB nativo en modo OTG/TinyUSB para conservar CDC, HID y almacenamiento USB.
- Tabla de particiones: `custom_16Mb.csv`.
- Radio Wi-Fi y Bluetooth LE integrada, sin RTC externo.

## Pinout configurado

| Función | GPIO |
| --- | --- |
| TFT CLK / MOSI / CS / DC / RST | 12 / 11 / 10 / 9 / 8 |
| SD CLK / MOSI / MISO / CS | 14 / 13 / 16 / 15 |
| Joystick arriba / abajo / izquierda / derecha | 4 / 5 / 6 / 7 |
| Pulsación del joystick | 21 |
| B1 / SET | 17 |
| B2 / RST | 18 |
| Batería ADC | 1, centro del divisor 100k/100k |
| Buzzer | 38 |

Pantalla ST7789V de 240×320, formato de píxel RGB565 y orden de canales BGR
(`TFT_RGB_ORDER=0`), por HSPI a 40 MHz. TFT RST está conectado a GPIO 8
(`TFT_RST=8`). La orientación
predeterminada es horizontal (320×240, rotación 1). La SD utiliza FSPI separado.
La retroiluminación BL está conectada a 3,3 V: no hay regulación PWM de brillo.
El apagado de pantalla se realiza mediante comandos al panel y no corta BL.

Todos los controles usan `INPUT_PULLUP` y se activan contra GND. Joystick COM
va a GND. Las direcciones navegan por menús y teclado; joystick central y B1
aceptan. B2 vuelve atrás al soltarlo y reinicia al mantenerlo 3 segundos.
Se aplica antirrebote de 40 ms y repetición de direcciones al mantenerlas.
Joystick central y B1 generan una sola aceptación por pulsación; Files conserva
la detección de pulsación larga mediante el estado físico independiente.

La batería se mide con ADC calibrado, atenuación de 11 dB, promedio de 16
muestras y factor ×2. El porcentaje interpola entre referencias de batería baja
y llena, calibrables desde Config → Power y guardadas en NVS. Sin calibrar usa
3300 y 4200 mV; el indicador sigue siendo aproximado. No hay señal para detectar
carga ni circuito de apagado total.
El buzzer utiliza las funciones de tonos existentes en GPIO 38.

`/boot.gif` en la raíz de la SD sustituye a la intro de Bruce. Conviene usar
un GIF del tamaño de la orientación elegida; el reproductor no lo escala.

Para la instalación y las actualizaciones, consulta [INSTALACION.md](../../INSTALACION.md).
