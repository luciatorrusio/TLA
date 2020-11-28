# Image Manipulator - TPE TLA - 2020 2do C.
Para este trabajo práctico se desarrolló un lenguaje tipado llamado ‘Image Manipulator `IM`’ y el objetivo del mismo es, como su nombre lo indica, poder manipular imágenes de una manera sencilla con unas pocas líneas de código.

Para lograr dicho objetivo, el código generado se traduce a Python y, además, se creó una librería de manejo de imágenes que está disponible de manera nativa en nuestro lenguaje.

### Antes de comenzar
Si bien `IM` es compatible en todos los Sistemas Operativos donde Python es compatible, esta guía de instalación está diseñada para Ubuntu. En caso de querer instalar este lenguaje en otro SO, usar esta guía como referencia.

### Requisitos
Antes de proceder con las instalación, asegurarse de tener instaladas las siguientes herramientas:
- `gcc`
- `make`
- `lex`
- `bison`

A modo de aclaración, las librerias de Python que utiliza `IM` son las que se mencionan a continuación, pero no es necesario que sean instaladas manualmente ya que se incluye un script de instalación:
- numpy
- opencv-python
- python3-matplotlib
- imutils

### Instalación
1. Abrir una terminal en la carpeta raíz del proyecto 
2. Dar permisos de ejecución al script `install.sh` de la siguiente forma:
```bash
chmod +x install.sh
```
3. Ejecutar el script de instalación como se menciona a continuación y dar permisos de administrador cuando sea requerido para que sea posible la correcta instalación de las librerías:
```bash
./install.sh
```

### Guía de uso
Para una descripción detallada de como es la gramática del lenguaje, dirigirse a la sección "Descripción de la gramática" del informe. 
Inicialmente, en el archivo `code.im` de la carpeta raíz, se incluye un 'Hello World' escrito en `IM` a modo de ejemplo. En dicho archivo, reemplazar el ejemplo por el código deseado.

Para compilar el código de `IM`, ejecutar el siguiente comando:
```bash
make compile
```

Si no se modifica el parámetro `INPUT`, por defecto se utiliza `code.im`

```bash
make compile INPUT=myCode.im
```

Si no se modifica el parámetro `OUTPUT`, por defecto se utiliza `out`

```bash
make compile INPUT=myCode.im OUTPUT=MyOutFile
```

En caso de éxito, se generará un archivo llamado como el parámetro `OUTPUT` en la carpeta raíz que contiene el código traducido a Python; caso contrario, se mostrará en pantalla los errores encontrados durante la compilación del código.

Para correr el programa (en caso de que `OUTPUT=out` - por defecto - ), ejecutar la siguiente línea:

```bash
./imma out
```

También es posible compilar y ejecutar nuestro código, pasando los mismos parámetros (`INPUT` y `OUTPUT`) con el comando:

```bash
make run
```

El mismo parámetro puede ser utilizado con `make compile`.

Es importante aclarar que si se intenta compilar 2 archivos distintos (cambiando el parámetro `INPUT`), al correr `make compile` o `make run`, no se sobreescribe el archivo anterior, con lo cual si se desea reemplazar el archivo de salida, se recomienda el uso propuesto originalmente:

```bash
./target/compiler outputFile < inputFile
```
Además, es `NECESARIO` que el script que se ejecute (`outputFile` con `./imma outputFile`) se encuentre en la misma carpeta donde se encuentra la librería `standardLibrary`. De no ser así, el programa no ejecuta.

### Ejemplo
Como ejemplo práctico se detallará a continuación los pasos para generar la imágen de la portada del informe.
El código `IM` que genera dicha imágen, junto con los recursos necesarios se encuentran en el directorio `examples/portada` dentro del directorio raíz del proytecto.
- Para compilar el código, ejecutar la siguiente línea:
```bash
make compile INPUT=examples/portada/portada.im
```
- Para correr el programa, ejecutar:
```bash
./imma out
```

Alternativamente, para compilar y ejecutar el programa, ejecutar:
```bash
make run INPUT=examples/portada/portada.im
```

En el directorio `examples/portada` se encontrará el archivo `portada.jpg`.

### Limpieza de archivos autogenerados
Ejecutar el comando:
```bash
make clean
```