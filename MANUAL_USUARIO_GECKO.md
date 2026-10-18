# Gecko Lite W — Manual de usuario

**Versión 1.0.0 · Español**  
Para ESP32-S3-N16R8 con pantalla ST7789V, SD, joystick, dos botones, batería y buzzer. Basado en esta adaptación del firmware Bruce.

Este manual describe las funciones de GECKO Lite W v1.0.0 y utiliza los nombres de menú que aparecen en pantalla. Algunas opciones requieren una SD, una conexión Wi-Fi o una conexión BLE activa. La disponibilidad de una función no implica que se haya validado en todas las combinaciones de hardware y dispositivos.

## Índice

1. [Equipo y límites](#1-equipo-y-límites)
2. [Controles y primer arranque](#2-controles-y-primer-arranque)
3. [SD, archivos e intro](#3-sd-archivos-e-intro)
4. [WebUI](#4-webui)
5. [Wi-Fi: conexión y diagnóstico](#5-wi-fi-conexión-y-diagnóstico)
6. [Wi-Fi: herramientas de laboratorio](#6-wi-fi-herramientas-de-laboratorio)
7. [Bluetooth LE](#7-bluetooth-le)
8. [BLE Suite](#8-ble-suite)
9. [USB y automatización](#9-usb-y-automatización)
10. [Scripts y aplicaciones](#10-scripts-y-aplicaciones)
11. [Reloj y extras](#11-reloj-y-extras)
12. [Configuración y temas](#12-configuración-y-temas)
13. [Batería y energía](#13-batería-y-energía)
14. [Problemas frecuentes](#14-problemas-frecuentes)
15. [Comprobación inicial](#15-comprobación-inicial)
16. [Glosario y referencias](#16-glosario-y-referencias)

## 1. Equipo y límites

| Elemento | Qué tienes y para qué sirve |
|---|---|
| ESP32-S3-N16R8 | 16 MB de flash y 8 MB de PSRAM. La PSRAM es memoria de trabajo, no almacenamiento permanente. |
| Wi-Fi | Radio integrada de 2,4 GHz. Las redes exclusivamente de 5 GHz no aparecerán. |
| Bluetooth | Bluetooth Low Energy (BLE). No es un adaptador Bluetooth clásico ni un receptor musical A2DP. |
| Pantalla | ST7789V de 240 × 320, normalmente horizontal a 320 × 240. Sin táctil. |
| Reset de pantalla | TFT RST conectado a GPIO 8 (`TFT_RST=8`); no confundir con B2/RST, conectado a GPIO 18. |
| SD | Archivos, imágenes, scripts, capturas y registros. |
| Joystick y botones | Navegación y teclado en pantalla. |
| Buzzer | Pitidos y tonos; no sustituye a un altavoz con amplificador. |
| USB nativo | Programación, consola y funciones HID/almacenamiento según el modo. Necesita un cable de datos. |
| Batería | Marcada 802540, 3,7 V, 800 mAh y 2,96 Wh. El indicador estima carga por voltaje. |

No lleva RTC externo, micrófono, altavoz I2S, contacto iButton, Ethernet, GPS, infrarrojos, NFC/RFID, NRF24, LoRa ni radio sub-GHz. Se retiraron la mayoría de esos módulos; algunos extras y ajustes genéricos permanecen y se identifican aquí cuando no son utilizables con este montaje.

Las funciones que emiten anuncios, cortan conexiones, escriben en dispositivos o capturan autenticaciones deben probarse en equipos propios y un entorno controlado. En los ejemplos, «equipo de laboratorio» significa uno que controlas y puedes reiniciar. Utiliza datos ficticios para demostrar portales.

## 2. Controles y primer arranque

| Control | Acción habitual |
|---|---|
| Arriba/abajo | Desplazamiento vertical cuando la pantalla lo admite. |
| Izquierda/derecha | Anterior/siguiente o cambiar valores. Algunas aplicaciones heredadas usan estas direcciones en sus listas. |
| Pulsar joystick | Seleccionar, aceptar o ejecutar: `SEL` / `OK`. |
| B1 / SET | También selecciona o acepta. |
| B2 / RST breve | Volver/cancelar al soltar: `ESC`. |
| B2 durante 3 segundos | Reinicia mientras el firmware atiende botones; no corta físicamente la alimentación. |

Mantener una dirección repite la navegación. En ciertas herramientas `SEL` detiene una operación: manda la indicación de la pantalla. En Files, mantener selección puede abrir acciones adicionales. Tras reposo, el primer botón despierta la pantalla: suéltalo y pulsa de nuevo para seleccionar.

Si una aplicación bloquea completamente el procesamiento, B2 puede no responder. En ese caso utiliza el control físico de alimentación de tu montaje.

### Primer arranque

1. Inserta la SD si usarás imágenes, scripts o registros.
2. Enciende y espera al menú principal.
3. Comprueba direcciones, centro y B1.
4. Entra en una categoría y vuelve con B2 breve.
5. Revisa porcentaje de batería e indicadores de la barra superior.
6. Consulta `Config → About` para versión, memoria y almacenamiento.

Las categorías son **WiFi, Bluetooth, Files, Scripts, Clock, Others y Config**. Puedes ocultarlas desde ajustes. `Connect` está dentro de Files en esta adaptación.

## 3. SD, archivos e intro

### Preparación

Usa una tarjeta que el equipo monte correctamente. Antes de formatear, copia su contenido: se borrará. No se ha validado una lista de capacidades/modelos. Ante problemas, prueba una tarjeta conocida con FAT32. Las librerías seleccionadas incluyen soporte exFAT, pero debe comprobarse en tu unidad.

Organización sugerida; crea solo las carpetas que necesites:

```text
/boot.gif
/imagenes/prueba.png
/BadUSB/hola.txt
/BruceJS/hola.js
/temas/gecko.json
/wordlists/prueba.txt
/wg.conf
```

Los nombres Bruce permanecen en ciertas rutas por compatibilidad. No renombres esas carpetas solo porque el menú diga Gecko.

### Intro

Copia **boot.gif en la raíz**. Se reproduce una vez, centrado y a tamaño original. Para llenar la pantalla horizontal, prepara 320 × 240. Una imagen pequeña no se amplía automáticamente.

Sin SD o GIF válido, continúa el arranque. `Config → System Config → InstaBoot: ON` omite la intro. Un botón puede saltarla cuando el reproductor atiende la entrada.

**Ejemplo:** copia un GIF corto, reinicia y comprueba que termina en el menú. Si tarda mucho, reduce duración, fotogramas o tamaño.

### Files → SD Card / LittleFS

SD Card es la tarjeta externa y aparece cuando se monta. LittleFS es almacenamiento interno del firmware.

| Acción | Uso y ejemplo |
|---|---|
| New Folder | Crea `imagenes`. |
| View File | Lee `notas.txt`. |
| File Info | Consulta información antes de copiar o borrar. |
| Copy / Paste | Copia un archivo a otra carpeta mediante el portapapeles. |
| Copy→LittleFS / Copy→SD | Pasa un archivo entre almacenamientos cuando se ofrece. |
| Rename | Cambia `prueba.png` a `colores.png`, conservando la extensión. |
| Delete | Borra el elemento; conserva una copia si lo necesitas. |
| View Image | Abre una imagen compatible PNG/JPG/GIF. Empieza por una pequeña. |
| JS Script Run | Ejecuta JavaScript compatible con el intérprete. |
| BadUSB Run | Ejecuta DuckyScript como teclado USB; ejemplo en el capítulo 9. |
| USB HID Type | Escribe el contenido de un archivo en la ventana activa del PC. |
| Decrypt+Type / Decrypt+Show | Abre contenido cifrado compatible, con contraseña, para escribirlo o verlo. |
| QR code | Representa contenido mediante QR cuando se ofrece; prueba texto breve. |
| CRC32 / MD5 | Calcula huellas para comparar archivos. No prueban quién los creó. |
| Play Audio | Condicionado al soporte de altavoz. No presupongas música usando solo el buzzer. |

Las acciones dependen de la extensión y las funciones compiladas. El cambio de marca no cambia el formato de los archivos cifrados.

### Files → Connect

Comunicación directa mediante ESP-NOW entre equipos con firmware compatible; no envía archivos a cualquier móvil por Bluetooth.

| Opción | Ejemplo |
|---|---|
| Send File | Pon un segundo Gecko/Bruce compatible en recepción, selecciona `notas.txt` y el receptor descubierto. |
| Recv File | Espera el envío desde el segundo equipo; comprueba después el archivo recibido. |
| Send Cmds | Envía órdenes compatibles a otro equipo de laboratorio; empieza con una consulta informativa. |
| Recv Cmds | Espera órdenes del otro equipo y sal al terminar la prueba. |

Si no se encuentran, detén otras funciones de radio y reinicia envío/recepción. La compatibilidad entre versiones no está garantizada.

### Files → Mass Storage

Expone la SD como almacenamiento USB. Conecta por USB nativo con un cable de datos, activa el modo y espera a que el ordenador detecte la unidad.

**Ejemplo:** copia `boot.gif` a la raíz. Expulsa la unidad desde el sistema operativo antes de salir o desconectar. Evita escribir simultáneamente desde WebUI, Files y el ordenador.

## 4. WebUI

Es una página servida por el Gecko, no una web pública. Ruta: **Files → WebUI**. Crear la Wi-Fi desde Start WiFi AP no inicia por sí solo la página.

### Conexión directa

1. Abre `Files → WebUI → AP mode`.
2. Conecta móvil/PC a la Wi-Fi del Gecko.
3. Abre **http://172.0.0.1**.
4. Introduce las credenciales web.

| Dato | Valor inicial del código actual |
|---|---|
| Red | `GeckoNet` |
| Contraseña Wi-Fi | `geckonet` |
| IP en AP mode | `http://172.0.0.1` |
| Nombre local | `http://gecko.local`, si el cliente resuelve mDNS |
| Usuario web | `admin` |
| Contraseña web | `gecko` |

Las credenciales guardadas se conservan: pueden seguir siendo BruceNet/brucenet y admin/bruce, o tus valores personalizados. Consulta la pantalla WebUI. La clave de la red y la clave de la web son distintas.

Si el móvil dice «sin internet», mantén esa Wi-Fi. Si cambia a datos móviles u otra red, puedes perder acceso al Gecko.

### Mediante el router

1. Abre `Files → WebUI → my Network`.
2. Conecta el Gecko a tu Wi-Fi si lo solicita.
3. Conecta móvil/PC a la misma red local.
4. Abre gecko.local o la IP de la pantalla.

Aquí **172.0.0.1 no es la IP asignada por el router**. Una red de invitados puede aislar clientes aunque compartan nombre Wi-Fi.

### Funciones de la página

Incluye exploración de SD/LittleFS, subida/descarga, acciones sobre archivos, ejecución de archivos compatibles, entrada de comandos, navegación remota/pantalla y ajustes de acceso. Su disponibilidad depende del archivo y del estado del firmware.

- **Ejemplo de transferencia:** abre SD/imagenes, sube `prueba.png` y ábrela desde Files.
- **Ejemplo de descarga:** descarga una captura PCAP para inspeccionarla en el ordenador.
- **Ejemplo de control:** abre navegación remota, mueve una selección y verifica el cambio en la pantalla física. No todas las aplicaciones tienen control remoto completo.

Para parar: `Files → WebUI → Stop WebUI`. `WebUi screen` muestra otra vez los datos. Varias herramientas Wi-Fi detienen WebUI automáticamente para usar la radio; actívala de nuevo al terminar.

## 5. Wi-Fi: conexión y diagnóstico

| Opción | Función y ejemplo |
|---|---|
| Connect to Wifi | Busca y conecta como cliente. Selecciona tu router de pruebas e introduce la clave. |
| Start WiFi AP | Crea la red configurada del Gecko. Conecta el móvil y activa WebUI si quieres la página. |
| Turn Off WiFi | Apaga Wi-Fi al terminar una transferencia. |
| AP info | Información de la red conectada. Anota canal/señal/direcciones disponibles. |
| Channel Analyzer | Visualiza actividad por canales. Compara un minuto de observación en dos habitaciones. |
| Jam Detect | Busca patrones interpretados como interferencia/ataque. Compara reposo con tráfico propio; una alerta no demuestra un inhibidor. |
| Scan Hosts | Descubre equipos de la LAN mediante ARP. Compara con la lista de tu router; un ausente puede estar dormido o aislado. |

Una señal de −45 dBm es más intensa que −80 dBm, pero intensidad no equivale a velocidad de internet. Un escaneo recoge lo escuchado en ese intervalo, no un inventario infalible.

### Terminales y servicios

| Opción | Uso y ejemplo |
|---|---|
| Listen TCP | Escucha en el puerto indicado. Haz que tu PC de laboratorio envíe `Hola Gecko` a esa IP/puerto. |
| Client TCP | Conecta a un servidor TCP propio. Prueba una línea en un servidor eco de tu LAN. |
| SOCKS4 Proxy | Proxy SOCKS4 en puerto 1080. Configura una aplicación de prueba con IP del Gecko y ese puerto; no equivale a una VPN. |
| TelNET | Terminal Telnet. Conecta a un equipo de laboratorio con Telnet habilitado; no cifra la sesión. |
| SSH | Terminal SSH. Entra en tu ordenador con servidor SSH y ejecuta `hostname` o `pwd`. |
| Wireguard | Túnel desde `/wg.conf` en la SD. Usa un perfil de tu servidor y verifica comunicación desde él. |

WireGuard lee Address, PrivateKey, PublicKey y Endpoint. El analizador es limitado: no presupongas soporte de todas las opciones de un perfil de escritorio y empieza con endpoint IPv4. No publiques la clave privada.

El registro SSH/Telnet se controla desde `WiFi → Config` y guarda bajo `/Bruce/Terminal/` con SD. **Ejemplo:** actívalo, consulta hostname, sal y revisa el texto. El nombre del interruptor puede indicar la acción a aplicar, no el estado actual.

## 6. Wi-Fi: herramientas de laboratorio

Estas opciones usan la radio integrada, pero algunas emiten tráfico o interrumpen conexiones. No se ha validado su eficacia en este montaje. Los ejemplos se refieren a una red aislada propia y datos ficticios.

### Wifi Atks

| Opción | Qué representa | Ejemplo de evaluación |
|---|---|---|
| Target Atks → Information | Información del objetivo. | Selecciona tu AP de laboratorio y anota canal y seguridad. |
| Deauth | Intento de desconexión de clientes mediante tramas. | En una maqueta con un cliente, observa desconexión y recuperación; la protección de tramas puede impedirlo. |
| Capture Handshake | Captura de intercambio de autenticación. | Reconecta manualmente tu cliente y comprueba si se guarda un intercambio completo. |
| Clone Portal | Identidad de red y página local. | Usa SSID de laboratorio y página rotulada como demostración. |
| Deauth+Clone | Combina desconexión y portal. | Documenta el flujo en una maqueta aislada, no en la red de uso diario. |
| Deauth+Clone+Verify | Añade comprobación al flujo anterior. | Compara datos ficticios y contrasta el resultado real, sin dar una clave por válida solo por el mensaje. |
| Karma Attack | Respuestas a determinadas búsquedas de redes de clientes. | Observa un cliente propio con un perfil ficticio preparado para el ensayo. |
| Beacon SPAM | Anuncios de nombres de red, no múltiples routers funcionales. | Anuncia un único nombre `LAB-GECKO` y comprueba su aparición en tu escáner. |
| Deauth Flood | Emisión repetida de desconexiones. | Ensayo de disponibilidad solo en una maqueta aislada; registra recuperación del cliente. |
| Enhanced Deauth | Variantes de selección de clientes/objetivos. | Revisa el inventario del único cliente de laboratorio antes de emitir. |

Beacon SPAM ofrece `Funny SSID`, `Ricky Roll`, `Random SSID`, `Single SSID` y `Custom SSIDs`. Generan listas predefinidas, aleatorias, un nombre o una lista desde SD/LittleFS. Empieza por un único nombre reconocible. `Station Deauth (Single)`, `Deauth All Clients` y `Deauth Target List` cambian destinatarios; no son escaneos pasivos.

### Evil Portal

Sirve una página local y puede registrar datos de formularios. Las opciones dependen de página y configuración.

**Ejemplo:** usa una página titulada «Demostración Gecko» con un campo «Mensaje de prueba». Conecta tu móvil, envía `hola-laboratorio` y revisa el registro bajo `/BruceEvilCreds`. No utilices credenciales reales ni una página que se haga pasar por un servicio ajeno.

En `WiFi → Config → Evil Wifi Settings` están gateway, tratamiento de contraseña, nombres de endpoints y exposición. Los modos permiten guardar texto, versión parcialmente oculta, contenido oculto o longitud. Ocultar un dato en el registro no significa que el formulario no lo reciba.

`Add Evil Wifi` / `Remove Evil Wifi` gestionan nombres usados por esas herramientas. Ejemplo: añade y después elimina `LAB-GECKO`. `/creds` y `/ssid` son endpoints del portal, no la dirección de entrada a WebUI.

### NetCut

Manipula conectividad local mediante ARP; no es un firewall permanente del router.

| Acción | Ejemplo en maqueta aislada |
|---|---|
| Save & Start | Revisa que la selección corresponde a tus equipos de ensayo. |
| Info | Consulta datos del cliente controlado. |
| Toggle VIP | Marca el equipo exceptuado según la lógica del módulo. |
| Cut All | Ensayo de interrupción sobre una maqueta con un único cliente. |
| Troll Mode / Troll All | Alterna interrupciones para observar recuperación. |
| Troll Timing | Define periodos del ensayo intermitente. |
| Resume / Resume All | Finaliza la interrupción y comprueba recuperación. |
| Re-Scan | Actualiza la lista tras conectar otro equipo propio. |

### Sniffer

Captura paquetes recibidos por radio y guarda PCAP. No convierte automáticamente tráfico cifrado en texto. El canal y sus cambios afectan a lo observado.

| Opción | Uso y ejemplo |
|---|---|
| New File | Separa archivos «antes» y «después» de una reconexión. |
| Capture Mode → Full Sniff | Observación amplia de tráfico del laboratorio. |
| Only EAPOL/HS | Intercambios relacionados con autenticación; reconecta manualmente tu cliente. |
| Sniff Deauth | Observa tramas de desconexión para contrastar una incidencia conocida. |
| Deauth Now | Acción activa; no hace falta para capturar una reconexión manual. |
| Reset Counters | Comienza una observación nueva con estadísticas reiniciadas. |
| Exit Sniffer | Termina antes de retirar SD o descargar archivos. |

Las capturas usan `/BrucePCAP` y, según modalidad, `/BrucePCAP/handshakes`. **Ejemplo:** captura unos segundos, sal y descarga el PCAP mediante WebUI para analizarlo en el ordenador.

### Responder

Responde a ciertas consultas de nombres y puede registrar intercambios de autenticación, incluidos hashes NTLM bajo `/BruceResponder/ntlm_hashes.txt`. No muestra necesariamente una contraseña y no es una consulta pasiva.

**Ejemplo de evaluación:** en una maqueta con cuentas desechables, comprueba si un cliente emite resoluciones inesperadas y si se registra una interacción. No uses una cuenta personal o de trabajo como cuenta de ensayo.

### Geckogotchi

Aplicación de observación/automatización Wi-Fi derivada de Brucegotchi/Pwnagotchi, con interfaz animada y lógica de redes y autenticación. No presupongas funcionamiento exclusivamente pasivo.

**Ejemplo:** observa sus cambios al conectar y desconectar un AP de laboratorio y revisa `/BrucePCAP/handshakes`. Para observación explícitamente pasiva, usa Sniffer sin acciones de desconexión.

### WiFi Pass Recovery

Comprueba candidatos de una lista contra un intercambio compatible en PCAP. No recupera cualquier contraseña ni garantiza resultados con capturas incompletas.

**Ejemplo reproducible:** usa un PCAP de tu red de pruebas y una lista de tres contraseñas ficticias, una de ellas su clave conocida. Guarda una candidata por línea en `/wordlists/prueba.txt`. Selecciona primero la lista y después el PCAP. Introduce el SSID si lo pide. Comprueba que encuentra la candidata esperada. `SEL` aborta la búsqueda. El código filtra longitudes de 8 a 63 caracteres; listas enormes pueden tardar mucho.

### Otros ajustes

- `Change MAC`: dirección personalizada/aleatoria y guardado según menú. Ejemplo: documenta la original y compara identificación en el router de pruebas. No garantiza anonimato.
- `Hidden Networks: ON/OFF`: inclusión de redes ocultas. Ejemplo: compara listas con un AP propio que no anuncie el nombre.
- `SSH/Telnet Log`: controla los registros de terminal descritos en el capítulo anterior.

## 7. Bluetooth LE

| Opción | Función y ejemplo |
|---|---|
| Disconnect | Cierra la conexión BLE mantenida por el menú; desconecta el teclado antes de cambiar de modo. |
| BLE Scan | Descubre anuncios/equipos BLE. Acerca una baliza propia y observa nombre, dirección y señal disponibles. |
| iBeacon | Emite anuncios de baliza. Busca Gecko desde un escáner BLE del móvil; no exige emparejar como teclado. |
| Media Cmds | Controles multimedia HID BLE. Empareja con tu PC y prueba pausa/reproducción. |
| Bad BLE | DuckyScript como teclado BLE. Utiliza el saludo del capítulo 9 en un editor vacío. |
| BLE Keyboard | Escritura manual; introduce `Hola Gecko` en una nota del equipo emparejado. |
| Presenter mode | Control de presentaciones. Prueba avanzar/retroceder en diapositivas de ensayo. |
| BLE Spam | Anuncios y variantes de emparejamiento. Observa una plantilla en tu escáner con intervalos moderados. |
| BLE Suite | Inspección y pruebas avanzadas; empieza por leer el perfil de tu periférico. |
| Ninebot | Secuencias específicas sobre un servicio BLE. Limita la primera prueba a descubrir e identificar tu dispositivo. |

BLE Scan no ve todos los dispositivos Bluetooth clásicos. BLE Sniffer tampoco es un analizador universal de conexiones cifradas. Un equipo puede dejar de anunciarse cuando ya está conectado a otro cliente.

### BLE Spam

Incluye plantillas asociadas a accesorios Apple y variantes como Pixel Fast Pair. El nombre de una plantilla no garantiza ventanas emergentes: depende del receptor y su software.

`Adv ms`, `Gap ms`, `TX Power`, `MAC Rand` y `Restart` ajustan duración/separación de anuncios, potencia, direcciones y reinicio del modo. **Ejemplo:** compara detección en tu teléfono manteniendo valores moderados y detén emisión al terminar.

### Ninebot: alcance real

Opciones conservadas: `Ninebot Max 2G / G30`, `Ninebot F2`, `Ninebot Generic 1/2/3`. Son etiquetas de secuencias enviadas a una característica BLE, no garantía de compatibilidad o de la acción ejecutada. No se ha validado en este montaje. No envíes comandos a un vehículo en movimiento o con alguien montado.

## 8. BLE Suite

Suite experimental. `SAFE`, `VULNERABLE` y `SUCCESS` son resultados de la lógica del programa, no una auditoría independiente ni una prueba concluyente de una vulnerabilidad. El ESP32-S3 usa BLE: una opción llamada HFP o AVRCP no añade Bluetooth clásico.

Los ejemplos siguientes describen objetivos de evaluación sobre periféricos propios de laboratorio. Corrupción, bypass y denegación de servicio pueden bloquear el receptor; no son necesarios para usar Gecko como teclado.

| Entrada principal | Contenido y ejemplo |
|---|---|
| Quick Vulnerability Scan | Clasificación inicial. Contrasta servicios detectados con la documentación de tu periférico. |
| Deep Device Profiling | Perfil de servicios/características. Compara una baliza sencilla con un teclado HID propio. |
| FastPair Attack Suite | Ensayos alrededor de Fast Pair. Comprueba primero si existe el servicio esperado. |
| HFP (Hands-Free) Suite | Pruebas con ese nombre. Documenta «servicio no encontrado» sin concluir seguridad o vulnerabilidad. |
| Audio Suite | Control/estabilidad de servicios de audio. Contrasta pausa con un receptor de ensayo compatible. |
| HID Attack Suite | Servicios de entrada y autenticación. Comprueba permisos de un periférico de desarrollo propio. |
| Memory Corruption Suite | Variantes Fast Pair. Observa estabilidad solo en firmware de laboratorio preparado para el ensayo. |
| DoS Attacks | Saturación y fuzzing. Evalúa recuperación en un receptor aislado, no en tu equipo de uso diario. |
| Payload Delivery | Scripts y autenticación experimental. Ejemplo benigno: saludo en editor de pruebas. |
| Testing Tools | Escritura, audio, protocolo y HID. Revisa permisos en características de tu periférico de desarrollo. |
| Universal Attack Chain | Encadena HFP/HID/FastPair. Documenta fases en una maqueta preparada; no lo uses como primer diagnóstico. |
| BLE Sniffer | Observación de anuncios. Enciende/apaga tu baliza y comprueba aparición. Registros bajo `/BruceSniffer`. |

### Subopciones

| Grupo | Opciones | Interpretación y ejemplo |
|---|---|---|
| FastPair | Quick Vulnerability Test; Memory Corruption Attack; State Confusion Attack; Crypto Overflow Attack; Handshake Fault Attack; Rapid Connection Attack | Ensayos de datos, estados y conexiones. Contrasta el resultado mediante observación externa de un receptor conocido. |
| FastPair, anuncios | Popup Spam: Regular, Fun, Prank, Custom | Diferentes contenidos. Compara dos etiquetas ficticias en tu escáner. |
| FastPair, automático | Run All Exploits; Smart Exploit (Auto Samsung) | Encadena/selecciona pruebas. El nombre Samsung no garantiza compatibilidad con toda la marca. |
| HFP | Test Vulnerability (CVE); Establish HFP Connection; Full HFP Attack Chain; HFP → HID Pivot | Secuencias experimentales. Comprueba existencia real del servicio sin atribuir una CVE por una etiqueta. |
| Audio | AVRCP Media Control; Audio Stack Crash; Telephony Alert Test; Run All Audio Tests | Control/estabilidad. Ejemplo benigno: pausa de una pista propia; Crash puede interrumpir el receptor. |
| HID | Test HID Vulnerability; Force HID Connection; Basic Keystrokes; DuckyScript Injection; OS-Specific Exploits; Run All HID Attacks | Entrada y autenticación. Ejemplo benigno: texto inocuo en editor tras conexión autorizada. |
| Memory Corruption | FastPair Memory Corruption; State Confusion; Crypto Overflow; Handshake Fault; Rapid Connection; Run All FastPair Attacks | Variantes agrupadas. En laboratorio registra también fallos y ausencia de compatibilidad. |
| DoS | Connection Flood; Advertising Spam; Protocol Fuzzer | Saturación/variación de tráfico. Evalúa disponibilidad solo en una maqueta aislada. |
| Payload Delivery | DuckyScript Injection; PIN Brute Force; Auth Bypass Suite | Scripts/pruebas de autenticación. El saludo permite probar entrada sin fuerza bruta ni bypass. |
| Testing Tools | Write Access Test; Audio Control Test; Protocol Fuzzer; HID Service Test | Comprobaciones específicas. Verifica que una característica de solo lectura de tu periférico rechaza escritura. |

`Jam & Connect (NRF24)` fue retirado. No hay un inhibidor NRF24 en este Gecko.

## 9. USB y automatización

Ruta: **Others → BadUSB & HID**. Usa el conector unido al USB nativo y cable de datos; cargar batería no demuestra que el cable transmita datos.

### BadUSB y Bad BLE: saludo

Crea `/BadUSB/hola.txt`:

```text
REM Prueba en un editor ya abierto
DELAY 1500
STRING Hola desde Gecko Lite W
ENTER
```

1. Abre un editor vacío y deja el cursor dentro.
2. Para USB: conecta el cable y abre `Others → BadUSB & HID → BadUSB`.
3. Para BLE: abre `Bluetooth → Bad BLE` y completa el emparejamiento solicitado.
4. Selecciona el archivo y comprueba la frase.

Escribe en **la ventana con foco**; no abre aplicaciones por sí mismo. DELAY son milisegundos, STRING escribe y ENTER pulsa Intro. La compatibilidad con dialectos avanzados DuckyScript es parcial.

En `Config → System Config → Advanced → BadUSB/BLE` configura Keyboard Layout, Key Delay y Show Output. Elige Spanish si coincide con el teclado del PC. Ante símbolos incorrectos, revisa ambos lados.

| Función | Ejemplo |
|---|---|
| USB Keyboard | Escribe manualmente una nota corta en un editor abierto. |
| USB Clicker | Usa un contador local de clics, velocidad baja y aprende a detenerlo antes de dejarlo funcionando. |
| USB U2F | En un entorno de prueba inicia registro/login y pulsa el centro cuando aparezca Confirm now. |
| Mass Storage | Copia archivos a SD mediante Files; expulsa antes de desconectar. |
| Consola serie | Monitor USB a 115200 según el proyecto. Empieza con `help` y consultas informativas. |

U2F es una implementación del firmware, no una llave certificada ni garantía de soporte FIDO2 completo. Usa una cuenta de ensayo y conserva otro método de acceso: cambios de firmware/restablecimiento pueden afectar los datos necesarios para autenticar.

### Consola: familias disponibles

Además de menús y WebUI, el código registra familias de comandos. Usa la ayuda de la versión cargada para su sintaxis exacta; los parámetros no son los mismos que los de una consola Linux.

| Familia | Uso y ejemplo de objetivo |
|---|---|
| Utilidades | Consultar ayuda e información del equipo antes de diagnosticar un fallo. |
| Storage | Consultar y gestionar archivos; empieza por listar una carpeta de prueba. |
| Settings | Leer/modificar ajustes; consulta primero el valor existente. |
| Screen | Operaciones de pantalla, útiles para diagnóstico o control remoto. |
| Power | Acciones de energía/reinicio; no confundirlas con cortar alimentación físicamente. |
| WiFi | Operaciones de conectividad; observa el estado antes de cambiarlo. |
| BadUSB | Automatización HID; reutiliza el saludo inocuo. |
| Interpreter | Lanzar scripts compatibles, empezando por el ejemplo del capítulo siguiente. |
| Sound | Funciones de sonido compiladas para buzzer/altavoz; prueba un tono breve. |
| Crypto | Operaciones sobre contenido cifrado compatible; trabaja con copias. |
| GPIO | Operaciones de pines. En un equipo cerrado no uses pines al azar: pantalla, SD y botones ya los ocupan. |

## 10. Scripts y aplicaciones

Scripts utiliza JavaScript integrado. No es Node.js ni un navegador: solo están disponibles los módulos y funciones del firmware. Un ejemplo de otra placa puede depender de teclado físico, altavoz o módulos ausentes.

### Ejemplo de saludo

Guarda `/BruceJS/hola.js`:

```javascript
var display = require('display');
var keyboard = require('keyboard');

display.setTextSize(2);
display.setTextColor(display.color(0, 255, 0));
display.drawFillRect(0, 0, display.width(), display.height(), display.color(0, 0, 0));
display.drawString('Hola Gecko', 20, 50);
display.drawString('B2 para salir', 20, 90);
while (!keyboard.getEscPress()) {
    delay(20);
}
```

Abre `Scripts → Load...` o ejecútalo desde Files. Usa funciones presentes en los ejemplos/API locales; falta comprobarlo físicamente en tu unidad. B2 sale del bucle.

La búsqueda conserva rutas `/BruceJS` y `/BruceScripts`. Si no aparece en la lista automática, utiliza Load. Cuando hay un intérprete activo, abrir Scripts puede devolver el control a esa aplicación en lugar de abrir otra lista.

| Familia | Uso y ejemplo |
|---|---|
| Display y entrada | Texto, formas y botones, como el saludo. |
| Dialog/keyboard | Solicitar texto o mostrar elecciones mediante diálogos. |
| Device | Consultar placa/batería, como `sd_files/interpreter/Example1.js`. |
| Storage | Archivos mediante la API; por ejemplo guardar puntuaciones en SD. |
| Wi-Fi, BLE, serial | Automatizar funciones expuestas, como registrar datos de tu sensor de laboratorio. |
| Timers/ejecución | Temporizadores y segundo plano según soporte; revisa `timer_background.js`. |
| Audio | Utilidades cuyo resultado depende del hardware y de la función concreta. |

`Config → Install App Store` instala el script de tienda si falta. Necesita conectividad y almacenamiento adecuados; el servicio externo puede cambiar. Las aplicaciones descargadas no están necesariamente adaptadas al joystick. **Ejemplo:** instala una utilidad sencilla, revisa sus requisitos y pruébala manualmente antes de configurarla al inicio.

`Startup App` permite abrir una aplicación automáticamente. **Ejemplo:** selecciona Clock para arrancar en el reloj. Si un script problemático se abre siempre, revisa su archivo/configuración desde un acceso que todavía funcione antes de restablecer el equipo.

## 11. Reloj y extras

### Clock

Hora por software: no necesita RTC externo, pero tras apagado completo no cuenta el tiempo sin alimentación.

En `Config → System Config → Clock` están `Via NTP Set Timezone` y `Set Time Manually`. **Ejemplo:** conecta a Wi-Fi, sincroniza y comprueba la hora. La lista usa desplazamientos UTC; revisa el desfase cuando cambie el horario estacional, sin suponer ajuste automático.

Aceptar en el reloj abre `Timer`, `Back to Clock` y `Exit`.

### Timer

Configura horas, minutos, segundos y aviso sonoro. Anterior/siguiente cambia valores y selección confirma etapas según la pantalla.

**Ejemplo:** configura 00:01:00 con sonido, espera a cero y comprueba el buzzer. No dependas de que siga contando después de apagar/reiniciar.

### Others

| Opción | Función y ejemplo |
|---|---|
| QRCodes | QR guardados de texto/enlaces o acceso Wi-Fi. Escanea el de la red y comprueba las credenciales. |
| Megalodon | Minijuego de tiburón y peces. Mueve el personaje con los controles admitidos y observa puntuación. |
| iButton | Llaves de contacto OneWire. **No utilizable en el montaje actual:** falta contacto/lector. Ejemplo solo con hardware añadido: leer una llave propia compatible. |
| Microphone / Spectrum / Record | Condicionados a micrófono configurado; no aparecen con la configuración de hardware de GECKO Lite W. El buzzer no graba sonido. |

Los QR son datos guardados: al cambiar la contraseña Wi-Fi, comprueba también el contenido del QR. Los enlaces a documentación original siguen apuntando a Bruce.

## 12. Configuración y temas

### Display & UI

| Opción | Uso y ejemplo |
|---|---|
| Brightness | BL está a 3,3 V fijo: 25/50/100 % no regulan la luz físicamente. Cero puede apagar el contenido del panel. |
| Dim Time | Inactividad antes del comportamiento de reposo/atenuación. Prueba 30 s y un botón para despertar. |
| Orientation | Cambia orientación; prueba horizontal y comprueba texto/controles. |
| UI Color | Colores principal, secundario, fondo, canales y guardado. Ejemplo: negro con verde. |
| Invert Color | Inversión del panel, dentro de color. No corrige únicamente rojo/azul intercambiados. |
| UI Theme | Carga tema de almacenamiento. Empieza por una paleta sin imágenes. |

El intercambio rojo/azul se corrigió en `platformio.ini` con `TFT_RGB_ORDER=0` (BGR): requiere una compilación que lo incluya. No hay pantalla táctil; su aviso se silencia solo para esta placa.

RGB565 describe el formato de píxel de 16 bits. BGR describe el orden de los
canales configurado para este panel; son dos aspectos diferentes. El pin de
reset del panel es GPIO 8, según `boards/esp32-s3-n16r8/pins_arduino.h`.

### Tema ligero de ejemplo

Guarda `/temas/gecko.json` como texto UTF-8:

```json
{
  "priColor": "07E0",
  "secColor": "07FF",
  "bgColor": "0000",
  "border": true,
  "label": true,
  "gifDuration": 0
}
```

Selecciónalo desde UI Theme. Usa verde, cian y negro en **RGB565 hexadecimal**, no códigos web de seis dígitos. El cargador puede guardar colores en configuración.

Claves útiles de imágenes: wifi, ble, files, interpreter, clock, others, config. Para un tema completo parte de los ejemplos de `sd_files/themes`, respeta la estructura y usa rutas relativas al tema según el cargador. Las animaciones grandes pueden ralentizar la navegación. La intro sigue siendo `/boot.gif`, independiente de las imágenes de arranque de temas originales.

No se ha implementado un nuevo diseño de menú por tarjetas: aquí se explica el sistema que ya existe y una paleta de ejemplo.

### Audio Config

Sound ON/OFF activa/desactiva avisos soportados. **Ejemplo:** desactívalo y repite una acción que producía un pitido. Sound Volume depende de altavoz y no es un control de volumen musical para este montaje con buzzer.

### System Config

| Opción | Uso y ejemplo |
|---|---|
| InstaBoot | Omite intro; actívalo para llegar directamente al menú. |
| WiFi Startup | Conecta al arrancar según redes guardadas; verifica antes conexión manual. |
| Startup App | Elige Clock o None y comprueba el próximo arranque. |
| Hide/Show Apps | Oculta categorías; Show All las recupera. |
| Clock | Ajuste manual/NTP. |
| Keyboard Language | Distribución del teclado en pantalla; distinta de Keyboard Layout HID del PC. |
| Advanced | Ajustes siguientes. |

### Advanced

| Opción | Uso y ejemplo |
|---|---|
| Set Device pins | SD/I2C/UART e I2C Finder heredados. No cambies el pinout ya fijado del Gecko. I2C Finder necesita conexiones I2C que aquí no se usan. |
| Toggle BLE API | Servicios para clientes de control BLE compatibles. Prueba detección con una herramienta propia de desarrollo; no es una web. |
| BadUSB/BLE | Layout HID, retardo y salida; corrige símbolos comparando con teclado español del PC. |
| BLE name | Nombre de ciertas funciones BLE; otras usan nombres específicos como Gecko-Scanner. |
| Network Creds | Credenciales AP disponibles en el menú. Personaliza SSID/contraseña y comprueba acceso; WebUI muestra sus credenciales web vigentes. |
| Factory Reset | Restablece configuración y reinicia. Haz copia de configuraciones/datos; no es la primera solución a un fallo de conexión. |

### Power, About y desarrollo

Sleep activa reposo y Restart reinicia. Deep Sleep depende del mecanismo de despertar configurado: no se ha validado despertar por joystick. Power Off no tiene un circuito de corte implementado; no equivale a desconectar batería.

About muestra versión, crédito a Bruce, memoria, red, almacenamiento y pantalla. **Ejemplo:** consulta espacio libre si falla cargar una imagen.

Dev Mode, cuando se habilita, incluye Serial use USB, Serial use UART y desactivación del modo. Usa USB: no hay UART externa conectada. Los menús LED dependen de hardware no configurado aquí.

## 13. Batería y energía

Porcentaje junto al icono de la barra superior, actualizado cada 30 s en los menús. La medida interna se limita a aproximadamente una actualización por segundo.

El código promedia 16 lecturas ADC del GPIO 1 y multiplica por dos por el divisor 100k/100k. Calcula el porcentaje entre dos referencias guardadas, baja y llena:

**porcentaje = (lectura − referencia baja) / (referencia llena − referencia baja) × 100**, redondeado a múltiplos de 5 y limitado entre 5 y 100. Se aplica un margen de estabilidad de 2 puntos más allá del umbral de redondeo para evitar oscilaciones al cambiar de pantalla. Sin calibrar, las referencias son 3300 y 4200 mV. La tabla siguiente corresponde al redondeo inicial con esos valores predeterminados; después, el margen puede retener el valor anterior.

| Voltaje estimado | Porcentaje aproximado |
|---|---|
| 4,20 V | 100 % |
| 4,07 V | 85 % |
| 3,90 V | 65 % |
| 3,75 V | 50 % |
| 3,60 V | 35 % |
| 3,30 V o menos | 5 % |

El porcentaje es una estimación lineal basada en voltaje, no una medida de energía almacenada. La capacidad nominal de 800 mAh no interviene directamente en el cálculo. Una lectura inferior al 100 % después de cargar puede deberse a la calibración o al voltaje medido; el porcentaje por sí solo no permite distinguir la causa.

### Calibrar batería llena

1. Espera a que el cargador termine la carga.
2. Desconecta el cargador y deja el Gecko encendido en el menú unos segundos.
3. Abre **Config → Power → Calibrar bateria llena**.
4. Confirma con **Calibrar** y espera «Calibracion guardada».

Se toman 128 lecturas distribuidas en ocho grupos para guardar una referencia de carga completa. Esa lectura corresponderá aproximadamente al 100 %; pequeñas fluctuaciones posteriores son normales. La referencia queda en memoria interna NVS, sin depender de la SD, y se conserva al reiniciar. Un error de lectura o escritura no sustituye la calibración anterior. Se rechazan referencias fuera de 3600–4400 mV estimados, pero estar en ese intervalo no demuestra que la batería esté llena: debes comprobar que el cargador haya terminado.

### Calibrar batería baja

1. Hazlo cuando la batería esté baja y el equipo pueda mantenerse encendido de forma estable, preferiblemente antes de que se apague por falta de energía.
2. Si ya se apagó, recarga lo suficiente para poder encenderlo y guardar el ajuste sin otro apagado.
3. Desconecta el cargador y abre **Config → Power → Calibrar bateria baja**.
4. Confirma y espera «Minimo guardado» antes de apagarlo o volver a cargar.

Esta lectura se asigna al extremo bajo (1 % visible). Si se toma después de una recarga breve, representa ese estado ya recargado, no el voltaje exacto del apagado. No fuerces descargas adicionales ni reinicios repetidos para buscar un cero más bajo. Se promedian también 128 lecturas. La referencia baja debe estar entre 2500 y 3900 mV estimados y al menos 200 mV por debajo de la referencia llena; estos son límites de validación del software, no umbrales recomendados de descarga. Una lectura rechazada conserva el ajuste anterior.

Puedes calibrar cada extremo por separado; el otro se mantiene. Las dos referencias se guardan juntas en un único valor NVS para evitar una actualización parcial. **Config → Power → Restaurar bateria** recupera ambas referencias originales: 3300 y 4200 mV. La calibración se conserva durante el restablecimiento normal de configuración del firmware; para quitarla usa esta opción. Un borrado completo de flash sí la elimina.

Al actualizar, Upload de PlatformIO o la aplicación firmware.bin escrita en 0x10000 conservan NVS si se mantienen las particiones. El binario combinado Gecko-esp32-s3-n16r8.bin escrito desde 0x0 incluye relleno sobre NVS y puede borrar la calibración. Consulta [las instrucciones de instalación](INSTALACION.md) antes de elegir un archivo.

Ejemplo: si guardas 4047 mV como llena y 3200 mV como baja, 4047 corresponde al 100 %, unos 3624 mV al 50 % y 3200 mV al mínimo visible. Esto ajusta el indicador, no aumenta la carga ni vuelve lineal la descarga real. No calibres como llena una batería a media carga.

No hay señal del cargador conectada; el firmware no detecta de forma fiable que esté cargando. BL fijo limita el ahorro de bajar brillo desde el menú. El mínimo 5 % evita el valor 0, que la interfaz trata como ausencia de batería; no garantiza que quede un 5 % de carga real.

**Ejemplo de seguimiento:** anota porcentaje al desconectar cargador, a los cinco minutos y tras una sesión Wi-Fi. Compara tendencias, no minutos restantes exactos. Estos voltajes describen el indicador de software, no las especificaciones del cargador.

## 14. Problemas frecuentes

| Síntoma | Qué comprobar |
|---|---|
| Rojo y azul intercambiados | Firmware con BGR, TFT_RGB_ORDER=0. No lo soluciones mediante Invert Color. |
| Avisos TOUCH_CS repetidos | GECKO Lite W no dispone de pantalla táctil. Utiliza la configuración de placa del proyecto sin añadir un pin táctil ficticio. |
| Batería llena marca 80–90 % | Tras terminar la carga y desconectar el cargador, usa Config → Power → Calibrar bateria llena. |
| No aparece SD Card | Reinicia con SD insertada, comprueba en PC y prueba otra conocida. No formatees sin copia. |
| No reproduce boot.gif | Raíz de SD, GIF válido e InstaBoot desactivado. |
| No abre gecko.local | Usa IP de pantalla: 172.0.0.1 en AP directo; otra asignada por router en my Network. |
| Conectado al Gecko sin web | Activa Files → WebUI; Start WiFi AP no basta. Otra herramienta puede haber detenido la web. |
| Móvil dice sin internet | Normal en AP directo; conserva la Wi-Fi. |
| Contraseña inválida | Mira pantalla y valores guardados anteriores. Wi-Fi y web tienen claves distintas. |
| No aparece mi Wi-Fi | Comprueba 2,4 GHz, cobertura y redes ocultas. |
| No aparece un Bluetooth | Puede ser clásico, no anunciarse o estar conectado. |
| USB solo carga | Cable de datos, puerto nativo y modo USB correcto. |
| PC no ve SD | Activa Mass Storage y verifica que Gecko monta la tarjeta. |
| BadUSB escribe mal | Keyboard Layout coincide con el receptor y editor con foco. |
| No reproduce música/graba | Hay buzzer, no altavoz I2S ni micrófono. |
| Hora incorrecta tras apagar | Sin RTC externo: sincroniza o ajusta. |
| Brillo no varía | Retroiluminación a 3,3 V fijo. |
| Izquierda no vuelve | B2 breve es ESC; izquierda es anterior. |
| B2 reinicia al volver | Suelta antes de tres segundos. |
| Script falla | Revisa módulos y placa objetivo; API de hardware retirado no disponible. |
| BLE Suite dice SUCCESS sin efecto | Contrasta el receptor real; es experimental. |

Al informar de un fallo, anota versión de About, ruta de menú, acción previa, SD/Wi-Fi/BLE activos y mensaje. Para compilación, copia desde el primer error hasta el resumen; warning no significa necesariamente fallo.

## 15. Comprobación inicial

### A. Pantalla y controles

Abre una imagen roja/verde/azul, comprueba orientación y recorre categorías. Acepta con B1 y vuelve con B2. Resultado: colores correctos y una acción por pulsación corta.

### B. Almacenamiento e intro

Copia boot.gif y notas.txt. Lee el texto desde Files, reinicia y observa intro. Activa InstaBoot y comprueba que se omite.

### C. Web local

Activa Files → WebUI → AP mode, conecta móvil y abre http://172.0.0.1. Sube una imagen, ábrela en Files y detén WebUI. Resultado: transferencia sin sacar SD.

### D. Diagnóstico de red

Conecta al router de pruebas, consulta AP info, observa Channel Analyzer y ejecuta Scan Hosts. Compara con el router. No necesitas opciones de desconexión.

### E. USB y BLE

Prueba USB Keyboard en editor vacío y ejecuta hola.txt. Repite por Bad BLE tras emparejar. Resultado: misma frase sin comandos de sistema.

### F. Reloj y batería

Ajusta hora y temporizador de un minuto. Comprueba buzzer y anota batería al principio/final. No evalúes exactitud solo por el porcentaje.

### G. Temas y scripts

Carga la paleta JSON y ejecuta hola.js. Comprueba legibilidad y salida con B2. Si falla, vuelve al tema predeterminado y al script mínimo antes de añadir imágenes/módulos.

## 16. Glosario y referencias

| Término | Significado |
|---|---|
| AP / STA | Punto de acceso / cliente de red. |
| SSID / BSSID | Nombre de red / identificador de punto de acceso. |
| IP / mDNS | Dirección de red / resolución local de nombres como gecko.local. |
| BLE / GATT | Bluetooth de bajo consumo / servicios y características. |
| HID | Dispositivo de entrada, como teclado o ratón. |
| PCAP / EAPOL | Archivo de paquetes / mensajes de autenticación. |
| LittleFS | Almacenamiento interno. |
| ESP-NOW | Comunicación directa entre ESP compatibles usada por Connect. |
| RGB565 | Color de 16 bits de pantalla/temas. |
| ADC | Conversor para medir el divisor de batería. |
| RTC / NTP | Reloj / sincronización de hora por red. |

### Referencias técnicas

Los siguientes archivos del repositorio permiten consultar los detalles de implementación:

- [Menú principal](src/core/main_menu.cpp) y [categorías](src/core/menu_items).
- [Controles y batería](src/gecko_interface.cpp), [pinout](boards/esp32-s3-n16r8/pins_arduino.h), [configuración de compilación](platformio.ini).
- [WebUI](src/core/wifi/webInterface.cpp), [conexión Wi-Fi](src/core/wifi/wifi_common.cpp), [interfaz web](embedded_resources/web_interface).
- [Wi-Fi](src/modules/wifi), [BLE](src/modules/ble), [USB/HID](src/modules/badusb_ble).
- [Archivos](src/core/sd_functions.cpp), [temas](src/core/theme.cpp), [ajustes](src/core/settings.cpp), [scripts](src/modules/bjs_interpreter).
- [Resumen del proyecto](GECKO.md).

La disponibilidad y el comportamiento de algunas funciones dependen de la configuración del dispositivo, los periféricos conectados y los equipos con los que interactúa.
