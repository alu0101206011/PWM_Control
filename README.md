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
Es necesario tener instalado el paquete m68hc11-gcc.

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

## Funcionamiento
```c
// Puertos:
// Control del clk
#define M6812_PWCLK   (0x0040)
#define M6812B_CON23   (1<<7)
#define M6812B_CON01   (1<<6)
#define M6812B_PCKA2   (1<<5)
#define M6812B_PCKA1   (1<<4)
#define M6812B_PCKA0   (1<<3)
#define M6812B_PCKB2   (1<<2)
#define M6812B_PCKB1   (1<<1)
#define M6812B_PCKB0   (1)


#define M6812_PWPOL   (0x0041)
##############################
// Reloj
#define M6812B_PCLK3   (1<<7)
#define M6812B_PCLK2   (1<<6)
#define M6812B_PCLK1   (1<<5)
#define M6812B_PCLK0   (1<<4)

// Polaridad
#define M6812B_PPOL3   (1<<3)
#define M6812B_PPOL2   (1<<2)
#define M6812B_PPOL1   (1<<1)
#define M6812B_PPOL0   (1)
#############################

// Elección de canales
#define M6812_PWEN   (0x0042)
#define M6812B_PWEN3   (1<<3)
#define M6812B_PWEN2   (1<<2)
#define M6812B_PWEN1   (1<<1)
#define M6812B_PWEN0   (1)

// Duty
#define M6812_PWDTY0
#define M6812_PWDTY1
#define M6812_PWDTY2
#define M6812_PWDTY3

Periodo
#define M6812_PWPER0
#define M6812_PWPER1
#define M6812_PWPER2
#define M6812_PWPER3
```

Puertos donde se encuentra PWM serial.
H2:

Los puertos: 

40 (PP0/PW0)

41 (PP1/PW1)

42 (PP2/PW2)

43 (PP3/PW3)





