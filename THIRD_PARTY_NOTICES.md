# GECKO Lite W — inventario de terceros

Versión **v1.0.0** (identificador interno: `dev`).
Adaptación de Bruce por **EDX_LAB**.

Este inventario complementa [THIRD_PARTY.md](THIRD_PARTY.md), que conserva los
avisos históricos de Bruce. No sustituye los archivos LICENSE, COPYING, NOTICE,
las cabeceras de los autores ni las condiciones particulares de cada archivo.
Cada componente conserva sus condiciones particulares. Las licencias no
identificadas se indican expresamente; las atribuciones no sustituyen a las
licencias originales.

## Alcance y referencias

Incluye las dependencias declaradas en `platformio.ini`, las bibliotecas
locales, el código incorporado y los recursos distribuidos con el proyecto.

- **D/** significa `.pio/libdeps/esp32-s3-n16r8/` después de resolver las
  dependencias. Es una ubicación de evidencia local, excluida de Git. Las
  bibliotecas correspondientes se descargan desde las fuentes declaradas.
- **F/** significa el paquete instalado `framework-arduinoespressif32`;
  **I/**, el paquete `framework-espidf`; **T/**, la cadena de herramientas.
  Las rutas son relativas a los paquetes correspondientes.
- «Licencia no identificada» significa que no se ha encontrado evidencia
  suficiente para asignar una licencia al componente o a la parte indicada.
  No significa dominio público ni demuestra, por sí solo, una infracción.
- Una dependencia declarada puede incluir código descartado por LTO y la
  eliminación de secciones. Los recursos de ejemplo y los
  controladores de otras placas se distribuyen como fuentes aunque no se usen.
- Las revisiones Git y las versiones de las dependencias están declaradas en
  [platformio.ini](platformio.ini). Este inventario no sustituye los avisos y
  licencias incluidos en cada dependencia o en el SDK.

En las tablas, **conservar** se refiere al aviso de copyright, permiso,
condiciones y descargo íntegros en el archivo de evidencia, no solo al nombre
abreviado de la licencia. Para Apache deben conservarse también los NOTICE
aplicables. Las licencias copyleft conservan sus obligaciones de fuentes y
avisos, según las condiciones de cada componente.

## 1. Proyecto base y adaptación

| Componente / ubicación | Autores y fuente | Licencia y evidencia | Avisos que conservar |
|---|---|---|---|
| Bruce; base de `src/`, `include/`, HAL, scripts y recursos propios del proyecto | Autores y colaboradores de [BruceDevices/firmware](https://github.com/BruceDevices/firmware); créditos en `README_UPSTREAM.md` | AGPL-3.0-or-later, declarada en `THIRD_PARTY.md` y documentación original; texto AGPLv3 en `LICENSE`. No se extiende automáticamente a terceros | `LICENSE`, créditos originales, cabeceras y `THIRD_PARTY.md` |
| Adaptación GECKO Lite W | EDX_LAB, [MODIFICACIONES.md](MODIFICACIONES.md) | Adaptación distribuida con la licencia del firmware Bruce, respetando las licencias particulares | Aviso de versión modificada, autoría y descripción de cambios; no presentarla como publicación oficial de Bruce |

## 2. Dependencias declaradas en PlatformIO

Las 21 filas corresponden a las 21 declaraciones activas de `lib_deps`.
Las referencias comentadas a módulos retirados no son dependencias activas.

| Componente / versión | Autores y fuente oficial o fork utilizado | Licencia identificada y evidencia | Ubicación / avisos que conservar |
|---|---|---|---|
| WireGuard-ESP32 0.1.5; revisión fijada | Kenta Ida, Daniel Hope; [fork sayacom](https://github.com/sayacom/WireGuard-ESP32-Arduino), origen ciniml / WireGuard-lwIP | BSD-3-Clause; `LICENSE`, README y cabeceras | `D/WireGuard-ESP32`; copyright 2021 Kenta Ida y Daniel Hope; condiciones BSD y cabeceras criptográficas |
| Time 1.6.1 | Michael Margolis, Paul Stoffregen y colaboradores; [Time](https://github.com/PaulStoffregen/Time) | LGPL-2.1-or-later; cabecera `Time.cpp` | `D/Time`; copyright Michael Margolis 2009–2014 y avisos originales |
| LibSSH-ESP32 5.9.0 | Ewan Parker; Aris Adamantiadis y equipo libssh; [LibSSH-ESP32](https://github.com/ewpa/LibSSH-ESP32) | LGPL-2.1-or-later; `COPYING` y `src/libssh/libssh.h`; partes con avisos propios | `D/LibSSH-ESP32`; conservar ambos niveles de autoría y todas las cabeceras |
| Adafruit BusIO 1.17.2-bruce.1 | Adafruit Industries; [fork emericklaw](https://github.com/emericklaw/Adafruit-BusIO_Bruce), origen Adafruit_BusIO | MIT; `LICENSE` | `D/Adafruit BusIO`; copyright 2017 Adafruit Industries y permiso MIT |
| SimpleCLI 1.1.4; revisión fijada | Stefan Kremser / Spacehuhn Technologies; [fork rennancockles](https://github.com/rennancockles/SimpleCLI) | MIT; `LICENSE` | `D/SimpleCLI`; copyright 2019 Stefan Kremser y permiso |
| NTPClient 3.2.1 | Fabrice Weinberg y colaboradores; [NTPClient](https://github.com/arduino-libraries/NTPClient) | MIT; cabecera `NTPClient.cpp` | `D/NTPClient`; copyright 2015 Fabrice Weinberg y permiso |
| ESP32Time 2.0.6 | Felix Biego; [ESP32Time](https://github.com/fbiego/ESP32Time) | MIT; `LICENSE` | `D/ESP32Time`; copyright 2021 Felix Biego y permiso |
| ArduinoJson 7.4.3 | Benoît Blanchon; [ArduinoJson](https://github.com/bblanchon/ArduinoJson) | MIT; `LICENSE.txt`, `library.properties` | `D/ArduinoJson`; copyright 2014–2026 Benoit BLANCHON y permiso |
| ESP8266Audio 2.4.1 | Earle F. Philhower III y autores de codecs; [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) | GPL-3.0-or-later para el envoltorio, `LICENSE` y cabeceras; licencias mixtas de codecs, sección 3 | `D/ESP8266Audio`; copyright de cada archivo, licencias y atribuciones de codecs |
| ESP8266SAM 1.1.0 | Earle F. Philhower III; código SAM de s-macke, procedente de Don't Ask Software; [ESP8266SAM](https://github.com/earlephilhower/ESP8266SAM) | Envoltorio `ESP8266SAM.cpp/.h`: GPL-3.0-or-later. **Licencia no identificada para el sintetizador SAM original**; README, apartado License, declara la falta de una licencia específica | `D/ESP8266SAM`; conservar cabeceras GPL y explicación del README. «Abandonware» y la mención a fair use no son una licencia de redistribución |
| FFT 0.0.1 | Robin Scheibler; [Tinyu-Zhao/FFT](https://github.com/Tinyu-Zhao/FFT) | MIT; `LICENSE` | `D/FFT`; copyright 2017 Robin Scheibler y permiso |
| NimBLE-Arduino 2.5.1 | Ryan Powell / h2zero; Neil Kolban, Apache Software Foundation, Espressif y colaboradores; [NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino) | Apache-2.0; `LICENSE`, `NOTICE`, `src/nimble/LICENSE` y `NOTICE`; TinyCrypt aparte | `D/NimBLE-Arduino`; ambos NOTICE, copyright 2020–2026 Ryan Powell, créditos esp32-snippets y Mynewt |
| JPEGDecoder 2.0.0 | Bodmer, Makoto Kurauchi, Rich Geldreich; [JPEGDecoder](https://github.com/Bodmer/JPEGDecoder) | Dominio público o MIT según `license.txt`; se conserva la alternativa MIT | `D/JPEGDecoder`; copyright 2013 Rich Geldreich y 2019 Makoto Kurauchi/Bodmer; permiso |
| mquickjs 0.0.6; revisión fijada | Fabrice Bellard, Charlie Gordon y colaboradores de Bruce; [fork BruceDevices](https://github.com/BruceDevices/mquickjs) | MIT; `LICENSE` | `D/mquickjs`; copyright 2017–2025 Bellard y Gordon; permiso; cabeceras generadas también en sección 4 |
| OneWire 2.3.8; revisión fijada | Jim Studt, Paul Stoffregen y numerosos colaboradores enumerados en `library.json/.properties`; [fork bmorcelli](https://github.com/bmorcelli/OneWire) | Permiso MIT de la cabecera `OneWire.cpp` | `D/OneWire`; copyright 2007 Jim Studt, lista de colaboradores e historial de adaptaciones |
| ESP32-PsRamFS 1.0.6; revisión fijada | tobozo y colaboradores; [fork bmorcelli](https://github.com/bmorcelli/ESP32-PsRamFS) | MIT; `LICENSE` | `D/ESP32-PSRamFS`; copyright 2021 tobozo y permiso |
| AnimatedGIF 2.2.3 | Larry Bank / BitBank Software; [AnimatedGIF](https://github.com/bitbank2/AnimatedGIF) | Apache-2.0; `LICENSE`. Ejemplos gráficos pueden tener otras licencias | `D/AnimatedGIF`; copyright 2020 BitBank Software y avisos de ejemplos |
| PNGdec 1.1.6 | Larry Bank / BitBank Software; [PNGdec](https://github.com/bitbank2/PNGdec) | Apache-2.0; `LICENSE`; zlib tiene licencia propia | `D/PNGdec`; copyright 2020 BitBank Software y avisos zlib |
| ESPAsyncWebServer 3.12.1 | ESP32Async y autores originales; [ESPAsyncWebServer](https://github.com/ESP32Async/ESPAsyncWebServer) | LGPL-3.0; `LICENSE`, `library.json/.properties` | `D/ESPAsyncWebServer`; conservar autores por archivo y licencia |
| AsyncTCP 3.5.0 | ESP32Async y autores originales; [AsyncTCP](https://github.com/ESP32Async/AsyncTCP) | LGPL-3.0; `LICENSE`, `library.json/.properties` | `D/AsyncTCP`; conservar autores por archivo y licencia |
| FastLED 3.10.3 | Daniel Garcia, Mark Kriegsman, Sam Guyer, Jason Coon, Josh Huber, Zach Vorhies y colaboradores; [FastLED](https://github.com/FastLED/FastLED) | MIT; `LICENSE`; subcomponentes con avisos particulares | `D/FastLED`; copyright 2013 FastLED, permiso y avisos internos |

## 3. Subcomponentes de las dependencias

Estas partes se descargan con su biblioteca; no se deben homogeneizar bajo la
licencia del envoltorio. Su presencia en el paquete descargado no demuestra
que cada codec, ejemplo o función se haya retenido en el ejecutable final.

| Componente / autores / fuente | Ubicación de evidencia | Licencia / avisos que conservar |
|---|---|---|
| Criptografía de WireGuard-lwIP; Daniel Hope, D. J. Bernstein y autores de los algoritmos; [fork utilizado](https://github.com/sayacom/WireGuard-ESP32-Arduino/tree/90aa6b43965c9718d62e59ddd709f856722f8e0b/src/crypto) | `D/WireGuard-ESP32/src/crypto/refc/` | Cabeceras BSD-3-Clause de Daniel Hope, con referencias a código de dominio público como ChaCha. Conservar avisos específicos de cada implementación, el port conserva sus licencias particulares |
| Criptografía de libssh; Aris Adamantiadis, Andrew Moon y autores indicados en archivos; [libssh](https://www.libssh.org/) | `D/LibSSH-ESP32/src/`, `src/libssh/`; cabeceras `poly1305.h`, `curve25519.h` | LGPL-2.1-or-later en libssh; Poly1305 indicado como dominio público de Andrew Moon. Respetar permisos por archivo |
| libmad; Underbit Technologies; [libmad](https://www.underbit.com/products/mad/) | `D/ESP8266Audio/src/libmad/COPYRIGHT`, `COPYING`, `LICENSE` | COPYRIGHT declara GPL-2.0-or-later; también se conserva texto GPLv3. Copyright 2000–2004 Underbit Technologies; la declaración incluye versiones posteriores |
| Helix MP3 y AAC; RealNetworks; [copia utilizada](https://github.com/earlephilhower/ESP8266Audio/tree/2.4.1/src) | `src/libhelix-mp3/LICENSE.txt`, cabeceras `src/libhelix-aac/aacdec.h`, dentro de ESP8266Audio | RPSL / RCSL según aviso y autorización aplicable; no se atribuye una licencia MIT/GPL al codec. Conservar bloques de RealNetworks (1995–2005 según archivo); el resumen del README no reemplaza esas condiciones |
| FLAC; Josh Coalson / Xiph.Org; [FLAC](https://github.com/xiph/flac) | `D/ESP8266Audio/src/libflac/README`, `COPYING.Xiph`, `COPYING.GPL`, `COPYING.LGPL`, `COPYING.FDL` | Codec bajo BSD de Xiph; otros programas LGPL/GPL y documentación GFDL según README. Conservar copyright 2000–2009 Coalson y 2011–2016 Xiph y todos los COPYING |
| Opus; Xiph.Org, Skype, Octasic, Jean-Marc Valin, Timothy B. Terriberry, CSIRO, Gregory Maxwell, Mark Borgerding, Erik de Castro Lopo, Mozilla, Amazon; [Opus](https://github.com/xiph/opus) | `D/ESP8266Audio/src/libopus/COPYING` | BSD de tres cláusulas, con los titulares enumerados en COPYING; conservar avisos y documentos de patentes existentes |
| TinySoundFont; Bernhard Schelling, basado en SFZero de Steve Folta; [TinySoundFont](https://github.com/schellingb/TinySoundFont) | `D/ESP8266Audio/src/libtinysoundfont/LICENSE` | MIT; copyright 2017–2023 Schelling y 2012 Folta; conservar permiso y procedencia |
| StellarPlayer / reproducción MOD; Ronen K. y autores previos; [StellarPlayer](https://github.com/MikesModz/StellarPlayer) | `D/ESP8266Audio/src/AudioGeneratorMOD.cpp` | Envoltorio de Philhower GPL-3.0-or-later; **Licencia no identificada para todas las aportaciones previas de la cadena MOD/PIC32**. La cabecera conserva la procedencia, no una autorización detallada de cada antecesor |
| Apache Mynewt NimBLE; Apache Software Foundation / Espressif; [Mynewt NimBLE](https://github.com/apache/mynewt-nimble) | `D/NimBLE-Arduino/src/nimble/LICENSE`, `NOTICE` | Apache-2.0; conservar copyright 2015–2022 ASF y modificaciones 2017–2022 Espressif |
| TinyCrypt y micro-ecc; Intel, Chris Morrison, Kenneth MacKay; [TinyCrypt](https://github.com/intel/tinycrypt) | `D/NimBLE-Arduino/src/nimble/ext/tinycrypt/LICENSE` y cabeceras ECC/CTR | BSD-3-Clause para TinyCrypt; ECC y partes con condiciones de dos cláusulas según cabecera. Conservar copyright Intel 2017, Morrison 2016 y MacKay 2014 |
| zlib; Jean-loup Gailly, Mark Adler; [zlib](https://github.com/madler/zlib) | `D/PNGdec/src/zlib.h` y archivos asociados | zlib; copyright 1995–2017 según cabecera; no retirar avisos y marcar modificaciones |
| cq_kernel; Kenny Peng; [fuente distribuida](https://github.com/FastLED/FastLED/tree/3.10.3/src/third_party/cq_kernel) | `D/FastLED/src/third_party/cq_kernel/LICENSE`, cabeceras `cq_kernel.*` | Apache-2.0; copyright 2020 Kenny Peng; conservar licencia y cabeceras |
| KISS FFT; Mark Borgerding; [kissfft](https://github.com/mborgerding/kissfft) | `D/FastLED/src/third_party/cq_kernel/kiss_fft.h` y archivos asociados | SPDX BSD-3-Clause en cabeceras; copyright 2003–2010 Mark Borgerding; conservar avisos, separado de Apache de cq_kernel |
| RTTTL; James BM y Daniel Hall, port Philhower; [Rtttl](https://github.com/spicajames/Rtttl) | `D/ESP8266Audio/src/AudioGeneratorRTTTL.cpp` | Envoltorio GPL-3.0-or-later, copyright 2018 Philhower; **Licencia no identificada para las aportaciones anteriores exactas**; conservar referencias al proyecto y gist original |
| ArduinoJson incluido por FastLED; Benoît Blanchon | `D/FastLED/src/third_party/arduinojson/json.hpp` | MIT explícita en cabecera; copyright 2014–2024; conservar aviso, separado de la dependencia ArduinoJson 7.4.3 |
| ObjectFLED / OctoWS2811; Kurt Funderburg, Paul Stoffregen / PJRC; [fuente distribuida](https://github.com/FastLED/FastLED/tree/3.10.3/src/third_party/object_fled) | `D/FastLED/src/third_party/object_fled/src/ObjectFLED.h`, `OjectFLED.cpp` | Permiso MIT en cabecera; copyright 2024 Funderburg y 2013 Stoffregen. Backend Teensy, sin atribuir su uso al ESP32-S3 |
| led_strip; Espressif Systems; [fuente distribuida](https://github.com/FastLED/FastLED/tree/3.10.3/src/third_party/espressif) | `D/FastLED/src/third_party/espressif/led_strip/src/` | SPDX Apache-2.0 en cabeceras; copyright 2022–2024 según archivo; conservar avisos |
| Material `third_party/yves` de FastLED | `D/FastLED/src/third_party/yves/` | **Licencia no identificada** para una aportación independiente sin aviso propio; conservar la procedencia del directorio, sin autoría individual identificada |
| GIF de ejemplos de AnimatedGIF; Cyriak Harris | `D/AnimatedGIF/examples/ESP32-LGFX-SDCard-GifPlayer/SD_Content/LICENSE.txt` | CC BY-NC-SA 4.0. Son ejemplos descargados, no se ha identificado su copia en el paquete GECKO. No extender esta licencia a todos los GIF del proyecto |

## 4. Bibliotecas incluidas en `lib/`

| Componente | Autores / fuente | Licencia y evidencia | Ubicación / avisos |
|---|---|---|---|
| TFT_eSPI 2.5.43, controladores, extensiones y fuentes propias | Bodmer y colaboradores; [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI); Ricard Bitrià Ribes en `TFT_config.h` | Licencias por procedencia descritas en `license.txt`: FreeBSD de dos cláusulas, MIT de Adafruit_ILI9341 y BSD de Adafruit_GFX | `lib/TFT_eSPI/`; conservar íntegro `license.txt` y cabeceras; licencias MIT y BSD según procedencia |
| Adafruit_GFX / fuentes GFXFF | Adafruit Industries; [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library) | BSD; `lib/TFT_eSPI/Fonts/GFXFF/license.txt` y licencia principal TFT_eSPI | Fuentes incluidas y funciones importadas; conservar copyright y condiciones BSD |
| USBHIDKeyboard, USBHIDMouse, CH9329_Keyboard y layouts | Arduino LLC, Peter Barrett y autores de distribuciones de teclado; [Arduino Keyboard](https://github.com/arduino-libraries/Keyboard) | LGPL-2.1-or-later explícita en las cabeceras USB/CH9329. Los layouts sin cabecera no reciben aquí una licencia individual nueva | `lib/Bad_Usb_Lib/`; copyright Arduino LLC 2015, Peter Barrett 2011; conservar cabeceras y avisos particulares |
| USBHID | Espressif Systems; [Arduino-ESP32 USB](https://github.com/espressif/arduino-esp32/tree/master/libraries/USB) | Apache-2.0; cabeceras `USBHID.cpp/.h` | `lib/Bad_Usb_Lib/`; copyright 2015–2020 Espressif, conservar aviso |
| BleKeyboard | T-vK y colaboradores, adaptación NimBLE heredada de Bruce; [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) | **Licencia no identificada** en la copia local ni en un archivo de licencia del árbol upstream consultado | `lib/Bad_Usb_Lib/BleKeyboard.*`; conservar procedencia; la dependencia de NimBLE no identifica la licencia del envoltorio |
| HAL de Bruce y adaptadores TFT_eSPI, LovyanGFX, M5GFX, Arduino_GFX | Colaboradores de [Bruce](https://github.com/BruceDevices/firmware) | Código propio de Bruce bajo su declaración general; **Licencia no identificada para cualquier fragmento ajeno sin aviso individual** | `lib/HAL/display/`, `library.json`; los backends alternativos no implican bibliotecas LovyanGFX/M5GFX/Arduino_GFX incluidas o activas en GECKO |
| SD y sd_diskio | Espressif Systems; Neil Thiessen para CRC; [Arduino-ESP32 SD](https://github.com/espressif/arduino-esp32/tree/master/libraries/SD) | Apache-2.0 según cabeceras locales, no LGPL genérica | `lib/HAL/sd_card/`, `sd_defines.h`, `sd_diskio2.h`; copyright 2015–2016 Espressif y 2014 Neil Thiessen |
| Adafruit AW9523 | Limor Fried / Adafruit Industries; [AW9523](https://github.com/adafruit/Adafruit_AW9523) | BSD según `license.txt` oficial; archivo local simplificado, sin aviso propio; no se ha demostrado identidad completa con upstream | `lib/HAL/io_expander/Adafruit_AW9523.*`; conservar referencia y avisos originales existentes; la licencia de la adaptación exacta no queda acreditada por el nombre |
| PCA9555 | Procedencia heredada de Bruce; autor individual no identificado | **Licencia no identificada** para un componente previo independiente; no hay aviso en los archivos revisados | `lib/HAL/io_expander/PCA9555.*`; sin declaración individual de licencia |
| AXP192 / BQ27220 | Atribuidos históricamente a M5Stack en `THIRD_PARTY.md`; [M5Stack](https://github.com/m5stack) | **Licencia no identificada para estas copias exactas**: sin licencia individual local y sin trazabilidad suficiente para confirmar la atribución MIT del resumen histórico | `lib/utility/AXP192.*`, `bq27220.*`; conservar archivos, procedencia declarada e incertidumbre; no son el medidor ADC de GECKO |
| Teclado M5Cardputer | Forairaaaaa / M5Stack; [M5Cardputer](https://github.com/m5stack/M5Cardputer) | Copyright 2023 en copia local; upstream actual incluye archivos SPDX MIT, pero **Licencia no identificada para la revisión exacta copiada** | `lib/utility/Keyboard*`; código condicionado para otra placa; conservar autor y cabeceras |
| CYD táctil resistivo XPT2046 | Paul Stoffregen, adaptación Piotr Zapart / hexefx; [XPT2046_Touchscreen](https://github.com/PaulStoffregen/XPT2046_Touchscreen) | Permiso tipo MIT con conservación adicional del aviso de financiación; cabeceras locales | `lib/CYD-touch/CYD28_TouchscreenR.*`; copyright 2015 Stoffregen, adaptación agosto 2023 Zapart; sin pantalla táctil en GECKO |
| CYD táctil capacitivo / definiciones Sunton | Bruce y rzeldent según referencia en cabeceras; [Sunton](https://github.com/rzeldent/platformio-espressif32-sunton) | **Licencia no identificada para la copia y adaptaciones exactas** | `lib/CYD-touch/CYD28_TouchscreenC.*` y definiciones de pines R/C; conservar referencias; no inferir licencia del controlador resistivo |
| Cabeceras mquickjs generadas | Fabrice Bellard, Charlie Gordon, Bruce; [fork fijado](https://github.com/BruceDevices/mquickjs/tree/169b5ea7723bf43d7be9631a14f9c2a1ed8c69e1) | MIT del generador y fuente mquickjs; `D/mquickjs/LICENSE`, cabecera de `mqjs_stdlib.c` | `lib/mquickjs_headers/`, `src/modules/bjs_interpreter/mqjs_stdlib.*`; conservar autores/permiso y firma de generación |

### TFT_eSPI_QRcode: autoría y licencias

Ubicación: `lib/TFT_eSPI_QRcode/`. Incluida por Bruce en julio de 2024,
[commit de incorporación](https://github.com/BruceDevices/firmware/commit/4647c9a0c246e1e0bab5173a95db7efc05dcda67).
La biblioteca se conserva sin modificaciones respecto a la
[copia incluida en Bruce](https://github.com/BruceDevices/firmware/tree/a59213f3ec6cd302fa32c2042b2700c9c24d991a/lib/TFT_eSPI_QRcode).

| Parte / autores | Fuente y evidencia | Licencia / avisos |
|---|---|---|
| Codificador original de tz1 | [qrduino](https://github.com/tz1/qrduino), `README` y `COPYING`; `qrbits.h` local idéntico por hash al original | GPLv3 expresamente declarada; copyright 2010 tz1 (`tz@execpc.com`). `qrencode.c` y el marco evolucionaron en descendientes; no se afirma identidad completa del codificador |
| Adaptación ESP8266 de Anun Panya | [ESP8266_QRcode](https://github.com/anunpanya/ESP8266_QRcode); README, historial y autor en metadatos | **Licencia no identificada** para sus aportaciones propias; conservar autor y referencia al original |
| Adaptación de Jose Antonio Espinosa | [ESP_QRcode](https://github.com/yoprogramo/ESP_QRcode); README e historial | **Licencia no identificada** para sus aportaciones propias; conservar autor y procedencia |
| Renderizador TFT de Domenico Silletti | [TFT_eSPI_QRcode](https://github.com/dsilletti/TFT_eSPI_QRcode); `README.md`, `library.json`, `library.properties` | **Licencia no identificada** para las aportaciones propias; conservar los tres autores declarados y referencias |
| Adaptaciones de integración y memoria de Bruce | Historial oficial del directorio; adaptación a `tft_display` y gestión de `qrframe` | La licencia general de Bruce no resuelve las autorizaciones de las aportaciones de terceros anteriores |

La biblioteca se utiliza para generar y mostrar códigos QR, incluidos QR
guardados y la visualización de archivos como QR.

La biblioteca se distribuye como parte de la adaptación heredada de Bruce,
con las atribuciones y condiciones particulares indicadas en la tabla.

## 5. Código y referencias de terceros dentro de `src/`

Una referencia de aprendizaje no demuestra copia literal. Se documentan las
procedencias expresas sin extender la licencia upstream a archivos enteros de
Bruce ni atribuir a los autores citados las modificaciones de GECKO.

| Componentes / ubicación | Autores y fuentes | Licencia y evidencia / avisos que conservar |
|---|---|---|
| Wi-Fi, `src/modules/wifi/wifi_atks.cpp`; detección Pwnagotchi en `pwngrid.cpp` | Just Call Me Koko; [ESP32Marauder](https://github.com/justcallmekoko/ESP32Marauder); risinek, [esp32-wifi-penetration-tool](https://github.com/risinek/esp32-wifi-penetration-tool) | Ambos upstream tienen LICENSE MIT (copyright 2020 Just Call Me Koko y 2021 risinek). Conservar referencias locales y avisos aplicables a fragmentos derivados |
| Sniffer, `src/modules/wifi/sniffer.cpp` | Stefan Kremser / spacehuhn, copyright 2017 en cabecera; referencia Evil-M5Core2 | **Licencia no identificada para el fragmento original exacto**: la cabecera no identifica un repositorio/revisión o permiso suficiente. Conservar copyright y referencias |
| Responder, `src/modules/wifi/responder.cpp` | [7h30th3r0n3/Evil-M5Project](https://github.com/7h30th3r0n3/Evil-M5Project), referencia local | **Licencia no identificada para las aportaciones heredadas exactas**; conservar procedencia |
| Pwnagotchi, `src/modules/pwnagotchi/` | 7h30th3r0n3 ([Evil-M5Core2](https://github.com/7h30th3r0n3/Evil-M5Core2), [PwnGridSpam](https://github.com/7h30th3r0n3/PwnGridSpam)); Vinícius Borriello ([m5-palnagotchi](https://github.com/viniciusbo/m5-palnagotchi)); sduenasg ([pio_palnagotchi](https://github.com/sduenasg/pio_palnagotchi)) | m5-palnagotchi actual: MIT, copyright 2026 Vinícius Borriello. **Licencia no identificada para toda la cadena de aportaciones previas**; no extender ese MIT a los demás proyectos. Conservar todos los créditos de cabeceras |
| Capa JS, `src/modules/bjs_interpreter/interpreter.h` | justinknight93; [Doolittle](https://github.com/justinknight93/Doolittle) | Upstream incluye GPLv3 en LICENSE; conservar crédito local; no se afirma que todo el intérprete de Bruce proceda de Doolittle |
| Subida WebUI, `src/core/wifi/webInterface.cpp` | Cellie; [minimalUploadAuthESP32](https://github.com/CelliesProjects/minimalUploadAuthESP32) | MIT en LICENSE upstream; copyright 2022 Cellie. Conservar referencia y avisos aplicables |
| SSH, `src/modules/wifi/clients.cpp` | M5Stack; [M5Cardputer](https://github.com/m5stack/M5Cardputer), referencia local genérica | **Licencia no identificada para el ejemplo SSH exacto**; la referencia no fija el archivo ni revisión. La referencia genérica no identifica la licencia del fragmento |
| Micrófono, `src/modules/others/mic.cpp` | Mhage; [esp32_SoundRecorder](https://github.com/MhageGH/esp32_SoundRecorder) | MIT, LICENSE.txt upstream; copyright 2018 Mhage; conservar referencia y avisos aplicables |
| JPEG y GIF en `src/core/display.cpp` | Bodmer / JPEGDecoder y Larry Bank / AnimatedGIF, ejemplos enlazados en el código | MIT / Apache-2.0 respectivamente, evidencias en secciones 2–3; conservar procedencia y avisos del código derivado |
| Ejemplos PSRamFS y WebRadio en `src/core/serial_commands/` | tobozo / ESP32-PsRamFS y Philhower / ESP8266Audio | MIT / GPL-3.0-or-later según bibliotecas; conservar enlaces y cabeceras aplicables |
| Ejemplos USB y ESP32 en `badusb_js.cpp` y `serial_commands/util_commands.cpp` | Espressif / Arduino y colaboradores | Condiciones particulares de cada ejemplo; **Licencia no identificada para cada fragmento exacto** si solo existe enlace, sin comparación de revisión. Conservar referencias, sin aplicar Apache a toda la carpeta |
| Escaneo I²C, `src/core/serial_commands/util_commands.cpp` | Guía Adafruit enlazada en el código | **Licencia no identificada para el fragmento exacto**; una guía enlazada no acredita licencia por sí sola |
| Contribuciones integradas de Bruce | Rennan Cockles (`startup_app.*`), Andrea Canale (`NetifClient.cpp`), Fourier / 9dl (`WifiMenu.cpp`), Sor3nt (`ble_ninebot.cpp`), Doominator1 / MarlinSchuck / Ninja-jr (`ble_spam.cpp`, BLE Suite y sniffer), Aleksei Gor / Senape3000 (`timer.*`), IncursioHack (`tururururu.cpp`) | Cabeceras y créditos locales; aportaciones distribuidas dentro del proyecto Bruce bajo su declaración general. No se ha identificado una biblioteca externa independiente para cada autor. Conservar las cabeceras y enlaces originales |
| Documentación MIC enlazada en `mic_js.*` | Senape3000; [fork de Bruce](https://github.com/Senape3000/firmware) | Referencia de documentación; no demuestra una dependencia adicional o copia externa |

## 6. Web, recursos, ejemplos SD y diseños

| Componente / ubicación | Autores / procedencia | Licencia identificada, evidencia y avisos |
|---|---|---|
| Interfaz web, `embedded_resources/web_interface/` | lshaf; [bruce-web-interface](https://github.com/lshaf/bruce-web-interface); crédito explícito en `index.html`; adaptaciones Bruce/GECKO | **Licencia no identificada para la interfaz upstream independiente** en el árbol consultado. Conservar crédito lshaf y referencia; no atribuir AGPL a su contribución solo por estar incorporada |
| Fuentes, iconos y datos gráficos integrados en `include/`, TFT_eSPI y módulos | Bruce y autores señalados en cada archivo; fuentes GFXFF en sección 4 | Licencia de fuentes GFXFF acreditada; **Licencia no identificada para recursos ajenos sin autor/permiso individual**. Marcas, dibujos y melodías pueden estar sujetos a condiciones independientes |
| Imágenes, GIF, diagramas y arte de `media/` | Material heredado de Bruce; autores individuales no identificados en todos los archivos | **Licencia no identificada** de los recursos sin aviso individual. Conservar créditos y enlaces de README. No son todos recursos incrustados en el firmware |
| PCBs y carcasas, `pcbs/` y `media/pcbs/` | Smoochiee; Pirata / bmorcelli; ultramarines y colaboradores, según README/rutas | **Licencia no identificada** para los diseños sin texto de licencia específico; el README los llama open-source, lo que no identifica condiciones concretas. Conservar nombres, documentación, archivos originales y enlaces |
| Temas, `sd_files/themes/` | Ejemplos heredados de Bruce; autores por README cuando consten | **Licencia no identificada** para gráficos y temas sin aviso específico. Conservar documentación y atribuciones |
| Scripts de ejemplo, `sd_files/interpreter/` | Bruce y autores citados; `tamagochi.js`: hxd57 / HawkstoNGriM, [m5-bruce-tamagochi-lite](https://github.com/HawkstoNGriM/m5-bruce-tamagochi-lite) | `tamagochi.js`: upstream incluye GPLv2 en LICENSE; no se ha acreditado cláusula «or later» para la copia exacta. Resto: avisos por archivo; **Licencia no identificada** para aportaciones externas sin permiso explícito |
| Referencias RF de `sd_files/interpreter/rf_brute.js` | mcore1976 / cc1101-tool; UberGuidoZ / Flipper, enlaces de cabecera | **Licencia no identificada para los fragmentos exactos referidos**. Ejemplo conservado; no es prueba de compatibilidad RF del hardware GECKO |
| Mandos IR, `sd_files/infrared/` | Contribuidores no identificados individualmente en todos los datos; Sony_SFRTV5.ir menciona Sigbeqboibe | **Licencia no identificada** para el conjunto de datos; conservar comentarios y autores declarados. Ejemplos heredados, sin hardware IR en GECKO |
| Portales, `sd_files/portals/`, y muestras de `sd_files/wifi/` | Material heredado de Bruce; diseños, logotipos y nombres de servicios de sus titulares | **Licencia no identificada** para todos los HTML, imágenes y marcas sin aviso propio; las marcas conservan las condiciones de sus titulares |
| Payloads BadUSB/BlueDucky, NFC, Pwnagotchi y reverse shell en `sd_files/` | Ejemplos Bruce y autores no individualizados cuando falte aviso | **Licencia no identificada** para material externo sin autorización específica; conservar comentarios y README. Muestras NFC enlazan páginas públicas |

## 7. Plataforma, SDK y herramientas de compilación

No se redistribuyen sus instalaciones completas en Git. Sus bibliotecas de
ejecución y partes del SDK pueden quedar incorporadas al firmware. Las licencias
del núcleo no se pueden aplicar indiscriminadamente a todos los componentes.

| Componente / autores / fuente | Ubicación y evidencia | Licencia / avisos |
|---|---|---|
| PlatformIO Core 6.2.0; PlatformIO Labs y colaboradores; [PlatformIO Core](https://github.com/platformio/platformio-core) | `requirements-build.txt`; herramienta externa | Apache-2.0 según proyecto oficial; conservar sus avisos si se redistribuye la herramienta, que no se incluye en este repositorio |
| pioarduino espressif32; colaboradores pioarduino; [plataforma fijada](https://github.com/pioarduino/platform-espressif32/releases/tag/55.03.39) | URL en `platformio.ini` | **Licencia no identificada para todos los elementos del paquete compuesto** en esta revisión; paquete con componentes de distintas procedencias |
| Arduino-ESP32; Espressif, Arduino y colaboradores; [Arduino-ESP32](https://github.com/espressif/arduino-esp32) | `F/cores/esp32/`, bibliotecas y cabeceras | Condiciones mixtas por archivo: LGPL y Apache, entre otras. Evidencia: cabeceras, `F/cores/esp32/libb64/LICENSE`, `F/libraries/BLE/LICENSE` y NOTICE. No extender una sola licencia a todo el core |
| Paquete de bibliotecas ESP32 con exFAT; Espressif y fork bmorcelli; [lib-builder](https://github.com/bmorcelli/esp32-arduino-lib-builder) | `platform_packages` fija el artefacto `main_esp32-arduino-libs-20260715-140131.tar.gz` | **Licencia no identificada para cada archivo precompilado del paquete exacto**; no hay LICENSE global en la instalación revisada. Conservar referencia exacta y avisos de SDK identificados |
| ESP-IDF; Espressif y colaboradores; [ESP-IDF](https://github.com/espressif/esp-idf) | `I/LICENSE`, componentes y avisos por archivo | Apache-2.0 para el código cubierto por LICENSE; componentes de terceros conservan sus licencias. El IDF instalado se usa como evidencia auxiliar, no demuestra identidad de cada objeto del paquete precompilado |
| FreeRTOS; autores FreeRTOS/Amazon y port Espressif; [FreeRTOS](https://github.com/FreeRTOS/FreeRTOS-Kernel) | Componente SDK `freertos`, cabeceras de kernel | MIT del kernel moderno; verificar avisos de la revisión del paquete para sus modificaciones |
| lwIP; Swedish Institute of Computer Science, Adam Dunkels y colaboradores; [lwIP](https://git.savannah.nongnu.org/cgit/lwip.git/) | Componente SDK `lwip`; cabeceras | BSD de sus cabeceras; conservar titulares y descargos de cada archivo |
| Mbed TLS; Arm y colaboradores; [Mbed TLS](https://github.com/Mbed-TLS/mbedtls) | Bibliotecas SDK `mbedtls`, `mbedcrypto`, `mbedx509` | Licencias por revisión (Apache/GPL y otras opciones en distintas ramas); **Licencia no identificada para la revisión exacta de cada objeto precompilado**; no deducirla de un Mbed TLS instalado diferente |
| FatFs/exFAT; ChaN y port Espressif; [FatFs](https://elm-chan.org/fsw/ff/) | SDK `fatfs`, paquete exFAT fijado | Permiso propio de FatFs según cabeceras; **Licencia no identificada para todas las modificaciones del artefacto precompilado exacto** |
| LittleFS; ARM y colaboradores; [littlefs](https://github.com/littlefs-project/littlefs) | Biblioteca SDK `joltwallet__littlefs`; fuentes del componente | BSD-3-Clause del núcleo; el wrapper y revisión precompilada requieren sus propios avisos |
| SPIFFS; Peter Andersson; [SPIFFS](https://github.com/pellepl/spiffs) | `I/components/spiffs/spiffs/LICENSE` | MIT; copyright 2013–2017 Peter Andersson |
| WPA supplicant / hostapd; Jouni Malinen y colaboradores; [hostap](https://w1.fi/hostapd/) | `I/components/wpa_supplicant/COPYING` | BSD según COPYING actual; conservar copyright 2002–2022 y condiciones por archivo |
| http-parser / NGINX; Ryan Dahl, Igor Sysoev y colaboradores; [http-parser](https://github.com/nodejs/http-parser) | `I/components/http_parser/LICENSE.txt` | Permisos MIT/BSD y procedencia NGINX según texto; conservar ambos niveles de avisos |
| Newlib / libgloss / libc / libm; múltiples titulares; [Newlib](https://sourceware.org/newlib/) | `I/components/newlib/COPYING.NEWLIB`, `T/share/licenses/newlib/` | Licencias mixtas enumeradas por archivo en COPYING.NEWLIB; no hay una única licencia para libc |
| GCC / libgcc / libstdc++; Free Software Foundation y colaboradores; [GCC](https://gcc.gnu.org/) | `T/share/licenses/gcc/COPYING`, `COPYING.LIB`, `COPYING.RUNTIME` | GPL con GCC Runtime Library Exception cuando corresponda; conservar excepción y avisos de las bibliotecas de ejecución |
| TinyUSB, libb64 y demás componentes auxiliares del core | [TinyUSB](https://github.com/hathach/tinyusb), autores de libb64 y del SDK | libb64: `F/cores/esp32/libb64/LICENSE`; TinyUSB y restantes: **Licencia no identificada para cada objeto del paquete exacto** en esta revisión. El nombre de un objeto no identifica su licencia |
| Herramientas externas Python, Git, SCons, esptool, CMake/Ninja y acciones GitHub | Proyectos oficiales respectivos, descargados fuera del repositorio; referencias en workflow y paquetes | No se distribuyen sus instalaciones. Sus propias licencias/avisos deben conservarse si se empaquetan en el futuro; no quedan licenciados por AGPL de GECKO |

Los paquetes precompilados del SDK incluyen componentes de distintas procedencias.
Este inventario no enumera todas las licencias de sus objetos individuales;
se deben consultar los avisos y condiciones correspondientes a cada paquete.

## 8. Alcance de las licencias

`THIRD_PARTY.md` se conserva como atribución histórica. Las condiciones particulares de la configuración
actual se detallan en este inventario:

- ESP8266Audio 2.4.1 tiene envoltorios GPL-3.0-or-later, no una atribución
  general LGPL-2.1. SAM requiere separar envoltorio y sintetizador original.
- Las cabeceras locales del HAL SD declaran Apache-2.0.
- PNGdec fijado aquí es 1.1.6; otras versiones del resumen histórico no fijan
  esta compilación. Las bibliotecas RF/NFC/RTC retiradas que menciona ese
  resumen no se deben contar como dependencias presentes.
- Las atribuciones históricas MIT de toda `utility` no acreditan por sí solas
  las copias exactas sin cabeceras individuales.
- TFT_eSPI_QRcode conserva la licencia acreditada del codificador original y
  las lagunas de sus adaptaciones por separado; no se le asigna AGPL/MIT global.

**Componentes con licencia no identificada total o parcialmente:** aportaciones propias de los forks QR;
núcleo SAM; BleKeyboard; procedencia exacta de ciertos drivers HAL/utility/CYD;
WebUI lshaf; fragmentos Sniffer/Responder/Pwnagotchi y ejemplos sin revisión
fijada; cadena MOD; recursos gráficos, temas, datos IR/portales y diseños sin
licencia específica; correspondencia individual de licencias del SDK
precompilado. Las filas anteriores precisan qué parte sí tiene evidencia.

Se ha documentado GPLv2 en el upstream de `tamagochi.js`; no se presupone
compatibilidad de un componente GPLv2-only con AGPLv3 ni se relicencia el
script. Se distribuye como ejemplo separado, no se compila como parte del
firmware. Debe mantenerse esa separación y conservarse su procedencia.
