# Práctica Sistemas Empotrados: Librerías
Anabel Díaz Labrador

## Introducción

Realización de una librería para la placa [ADAPT912DT60](http://www.technologicalarts.com/myfiles/ad912dt60.html).

La librería elegida a implementar es un **Generador PWM**. Se va a integrar a un grupo de librerías básicas ya existentes, 
llamadandose el código en su completitud SimpleGel.

## Ejemplos

Los ejemplos desarrollados están en el directorio `Ejemplos`.
Para realizar un nuevo proyecto basta con crear un nuevo subdirectorio
y copiar el `Makefile` del directorio Ejemplo.

### Productos

Al ejecutar el `Makefile`, cada `.c` se compila y enlaza para generar un `.elf`,
que sería el ejecutable.
Se genera también el `.s19` porque es el formato en que
dicho ejecutable se envía, a través de la serial (Serial Port Term), a la placa ADAPT912DT60.

En ésta debe estarse ejecutando el cargador (`CargaRam`) para tener el siguiente
mapa de memoria:

- Los 2Kb de RAM a principio de la memoria. En la parte final de la misma se configura
una tabla de *seudovectores* en direcciones de la `0x07C2` a `0x07FF`

- La tabla de registros de entrada salida en la dirección `0x0800`

- La EEPROM en la dirección `0x0C00`

- Los 28 Kb de flash deshabilitando para poder acceder a memoria externa en el rango
de `0x1000` a `0x7FFF`

## Documentación

El código está documentado utilizando [Doxygen](http://www.doxygen.nl).

Para generar la documentación, ejecutar `make` en la carpeta `doc`.

La documentación se pude acceder desde el fichero `doc/html/index.html`.
Al final del la ejecución del comando `make` se muestra la
URL completa para acceder a la documentación.
