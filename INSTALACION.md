# Instalar Gecko Lite W

Este firmware está preparado para **Gecko Lite W, ESP32-S3-N16R8**, flash de 16 MB, PSRAM OPI de 8 MB, pantalla ST7789V y el [pinout del proyecto](boards/esp32-s3-n16r8/README.md). Otro ESP32-S3 puede tener distintos pines, pantalla o memoria. La compatibilidad requiere que coincidan la memoria, el controlador de pantalla y el pinout.

## Instalar un binario ya compilado

Descarga el paquete de firmware de una publicación del mantenedor o de GitHub Actions. Descomprime el ZIP. No necesitas instalar librerías de Arduino ni copiar carpetas del código para usar el binario.

El archivo **Gecko-esp32-s3-n16r8.bin** es completo: incluye arranque, tabla de particiones y aplicación. Se escribe en **0x0**. El archivo firmware.bin de .pio es solamente la aplicación y no se instala en esa dirección.

Con un cable USB con datos, conecta el USB nativo. Una opción de instalación por consola, con Python y esptool instalados:

```sh
python -m pip install esptool==5.3.0
python -m esptool --chip esp32s3 --port COM5 write-flash 0x0 Gecko-esp32-s3-n16r8.bin
```

Sustituye COM5 por el puerto de tu dispositivo. En Linux/macOS puede ser /dev/ttyACM0 o /dev/cu.usbmodem...; no copies el nombre sin comprobarlo. Si no entra en carga, utiliza el procedimiento BOOT/RESET físico de tu placa. B2 del Gecko es un botón de software, no el pin BOOT.

El binario combinado incluye relleno en el espacio de NVS: **cargarlo desde 0x0 puede borrar ajustes y calibración de batería**, aunque no ejecutes erase-flash. Úsalo para instalación completa. Para actualizar conservando NVS con las mismas particiones, usa Upload de PlatformIO o la aplicación separada incluida en el paquete:

```sh
python -m esptool --chip esp32s3 --port COM5 write-flash 0x10000 firmware.bin
```

Esto requiere que el Gecko ya tenga el bootloader y la tabla de particiones de este proyecto; no sirve como primera instalación. El paquete incluye también bootloader.bin y partitions.bin para instalación por componentes. Un borrado completo de flash elimina NVS. Cierra el monitor serie antes de cargar.

SHA256SUMS.txt permite comprobar que descargaste el mismo archivo que se empaquetó. Ejemplo en PowerShell: `Get-FileHash .\Gecko-esp32-s3-n16r8.bin -Algorithm SHA256`.

## Compilar desde el código

1. Descarga el repositorio completo con Code → Download ZIP y descomprímelo, o clónalo con Git.
2. Abre la carpeta que contiene platformio.ini, no solamente src.
3. Instala VS Code con PlatformIO IDE y ejecuta Build para esp32-s3-n16r8. PlatformIO descarga plataforma, compilador ESP32 y librerías declaradas; necesitas internet la primera vez.
4. Usa Upload con el puerto del Gecko, o instala el binario completo generado en la raíz.

Las bibliotecas modificadas dentro de lib forman parte del proyecto: no las sustituyas por las originales. No se debe copiar la carpeta .pio de otro ordenador. FFat forma parte del framework ESP32 y no se instala como una biblioteca de registro independiente.

Alternativa por consola (Python 3.12 y Git instalados; Git hace falta para obtener dependencias):

```sh
python -m pip install -r requirements-build.txt
python -m platformio run -e esp32-s3-n16r8
python -m platformio run -e esp32-s3-n16r8 -t upload --upload-port COM5
```

Al terminar se genera Gecko-esp32-s3-n16r8.bin en la raíz. Para crear un paquete con manual, instrucciones y checksum:

```sh
python tools/package_release.py
```

Los resultados se guardan en dist. El repositorio ignora los binarios de compilaciones locales: deben distribuirse como archivos de una Release o un artefacto de Actions. El flujo Gecko Lite W - build compila en Windows y Linux y adjunta los paquetes; no publica automáticamente una Release.

## Archivos generados y herramientas adicionales

La web viene del código de embedded_resources/web_interface y se comprime localmente durante el build, sin consultar un servicio de minificación. include/webFiles.h e include/current_year.h se generan solos.

El repositorio incluye las cabeceras generadas de MicroQuickJS y su firma: una descarga sin cambios no necesita instalar GCC nativo. Si modificas la API JavaScript o actualizas MicroQuickJS, tendrás que regenerarlas con GCC y soporte de 32 bits. En Linux: gcc-multilib y libc6-dev-i386; en Windows, un GCC compatible configurado con MQJS_HOST_CC. Actualiza también las cabeceras y su firma en Git después de regenerar. El script falla expresamente si faltan o están desactualizadas, en vez de compilar una API incoherente.

Los recursos de la SD son opcionales para arrancar. Para la intro coloca /boot.gif en la raíz de la tarjeta; scripts, temas y capturas se describen en el manual. No se necesita una imagen LittleFS preinstalada para llegar al menú: el firmware inicializa su almacenamiento.

## Solución de problemas

- No encuentra platformio.ini: abre la carpeta completa del proyecto.
- Error descargando librerías: comprueba internet y Git. No copies cabeceras sueltas en src.
- No encuentra WebUI: conserva embedded_resources y los scripts Python de la raíz.
- Error de generación MQJS: restaura las cabeceras correspondientes a esa revisión o instala las herramientas de regeneración.
- No aparece puerto: prueba cable de datos, otro USB y modo de descarga físico. Los controladores dependen del adaptador USB de tu placa.
- Pantalla o botones distintos: verifica el pinout antes de atribuirlo a librerías.

La compilación automática comprueba código y dependencias; las pruebas físicas se hacen en un Gecko compatible. No garantiza compatibilidad con cualquier placa ESP32.
