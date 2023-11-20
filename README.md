# Worms

## Dependencias
* Cmake - v3.16.3
* libsdl2-image - v2.6.3
* libsdl2-mixer - v2.6.3
* libsdl2-ttf - v2.20.2
* Qt - v5.15.2 (instalar usando `sudo apt-get install qtbase5-dev`)

## Compilacion

Al instalarse todas las dependencias ejecutar desde la carpeta raiz del proyecto ejecutar:

* `mkdir build`
* `cd build`
* `cmake ..`
* `make -j4`

Al hacer esto hay 2 formas de ejecutar _actualmente_  el juego:

### Forma 1
Ejecutar:

`./wormsremake`

Y en el lobby crear una partida, eligiendo la direccion, el puerto el mapa y la cantidad de jugadores adecuada.

Luego desde otra terminal ejecutar el mismo comando

`./wormsremake`

Y unirse a la partida utilizando la direccion y puerto anteriormente proporcionados.
De esta forma se le unira a la partida creada.

### Forma 2
Esta forma es mas util para una ejecucion rapida. Seguramente en la entrega final la descartemos pero ayuda a una ejecucion mas
rapida del programa asi que la dejamos para que la correccion sea mas leve.
Dentro del archivo `server_src/main.cpp` cambiar la constante `HARDCODED_PLAYERS` para que se ajuste a la necesaria.
Una vez hecho esto compilar como fue dicho arriba y usar los ejecutables client y server para armar la partida. 

## Como jugar

* `Flecha Izquierda`: Mueve el gusano a la izquierda
* `Flecha Derecha`: Mueve el gusano a la derecha
* `Numeros`: Elije el arma que el gusano usara, basandose en el orden del HUD.
  * `Mouse`: Con este se puede elegir el angulo del disparo, con el click se dispara.
* `Enter`: Salto para adelante
* `Backspace`: Salto para atras
