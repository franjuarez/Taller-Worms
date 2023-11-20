# Worms

## Dependencias
(asociar con links o algo)
* Cmake - v3.16.3
* libSDL2pp - v0.18.1
* Box2d - v2.4.1
* Qt - v5.15.2 (instalar usando `sudo apt-get install qtbase5-dev`)
* yaml-cpp - v0.8.0

## Compilacion

Al instalarse todas las dependencias ejecutar desde la carpeta raiz del proyecto ejecutar:

`mkdir build`
`cd build`
`cmake ..`
`make -j4`

Al hacer esto hay 2 formas de ejecutar _actualmente_  el juego:

### Forma 1
Ejecutar:

`./wormsremake`

Y en el lobby crear una partida, eligiendo el mapa y la cantidad de jugadores adecuada.

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

`Flecha Izquierda`: Mueve el gusano a la izquierda
`Flecha Derecha`: Mueve el gusano a la derecha
`Numeros`: Elije el arma que el gusano usara, basandose en el orden del HUD. Con el mouse 
`Enter`: 
`Backspace`: 
`Space`: 