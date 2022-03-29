Practica 3. 
Se Creo un proyecto como copia del proyecto realizado para la práctica 2.
Se Creo una carpeta API dentro de la carpeta Drivers en la estructura de directorios del nuevo
proyecto. 
Se Creo dentro de la carpeta API, las subcapetas /src y /inc.
Se encapsularon las funciones necesarias para usar retardos no bloqueantes en un archivo
fuente llamado API_delay.c con su correspondiente archivo de cabecera API_delay.h, y se ubicaron
estos archivos en la carpeta API creada.
En API_delay.h se ubicaron los prototipos de las funciones y declaraciones
typedef uint32_t tick_t; // la biblioteca que se incluyo fue: stdio.h
typedef bool bool_t; // la biblioteca que se incluyo fue: stdbool.h
typedef struct{
tick_t startTime;
tick_t duration;
bool_t running;
} delay_t;
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

En API_delay.c se ubicaron las implementaciones de todas las funciones.

Punto 2.
Se implementa un programa que utiliza retardos no bloqueantes y hace titilar en forma
periódica e independiente los tres leds de la placa NUCLEO-F429ZI de acuerdo a una
secuencia predeterminada como en la práctica 1.
Cada led debe permanecer encendido 200 ms. No debe encenderse más de un led simultáneamente en ningún momento.

Para pensar luego de resolver el ejercicio:
● ¿Se pueden cambiar los tiempos de encendido de cada led fácilmente en un solo
lugar del código o estos están hardcodeados? ¿Hay constantes mágicas?
Se creo un programa que permite facilmente cambiar los delays de cada LED. No hay constantes magicas.

● ¿Qué bibliotecas estándar se debieron agregar a API_delay.h para que el código
compile? Si las funcionalidades de una API propia crecieran, habría que pensar cuál
sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usan en
el ejercicio.
se agragaron las bibliotecas stdio.h y la stdbool.h.

● ¿Es adecuado el control de los parámetros pasados por el usuario que se hace en
las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla
que estén dentro de los rangos correctos?
la funciones de delay controlan el rango correcto. 
