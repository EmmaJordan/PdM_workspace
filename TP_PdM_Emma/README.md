TP final PdM
Cátedra de Programación de Microprocesadores
Carrera de Especialización en Sistemas Embebidos de la FIUBA.

En este TP final de la materia se comienza a diseñar un Sistema de Control para Equipos de Rayos X,
orientado hacia el proyecto final de la especialización. 
- Se implementa una máquina de estados finita para el estado del sistema: reposo, cambio 
de tiempo y disparo.
- Se implementa una máquina de estados finita para la detección de pulsadores P1, P2 y P3.
La misma consiste en la detección de flancos de subida/bajada de los pulsadores,
con delays no bloqueantes y anti-rebote por software. 
    P1: menos Tiempo
    P2: más Tiempo
    P3: Disparo (userButton)
- Se agrega la interfaz UART para enviar información útil al usuario del Software.
- Se utilizan los 3 leds de la placa como indicadores de información.
    LED1: menos Tiempo 
    LED2: mas Tiempo
    LED3: Disparo
- Se implementa conversión A/D en modo polling para poder leer la tensión del equipo de Rx en [kV]. 
Dicha tensión se transforma a valores 0-3Vcc para la placa Nucleo, con placa
electrónica de desarrollo propio. Se simbolizará dicho comportamiento con un
potenciómetro lineal de 10k en el pin A0 de la placa.

Autor Joan Emmanuel Jordán