# Worms

## Dependencias
* Cmake - v3.16.3
* libsdl2-image - v2.6.3
* libsdl2-mixer - v2.6.3
* libsdl2-ttf - v2.20.2
* Qt - v5.15.2 (instalar usando `sudo apt-get install qtbase5-dev`)

## Instalacion 

Se cuenta con un archivo `installer.sh` que permite instalar el juego y sus dependencias. Tambien se encarga de la compilacion del mismo, permitiendo al usuario ir directo al paso de "Ejecucion del juego". 

## Compilacion

Al instalarse todas las dependencias ejecutar desde la carpeta raiz del proyecto ejecutar:

* `mkdir build`
* `cd build`
* `cmake ..`
* `make -j4`

### Ejecucion del juego

En una terminal inicial, ejecutar: 

`./wormsServer <puerto>`

Luego desde otra terminal ejecutar el comando:

`./wormsClient`

Aqui se abrira el Lobby, el cual permitira crear una nueva partida, eligiendo el tablero y la cantidad de jugadores, y tambien permitira unirse a una partida en espera de mas jugadores. Para ello es necesario conectarse al puerto usado al iniciar el server. 


## Como jugar

* `Flecha Izquierda`: Mueve el gusano a la izquierda
* `Flecha Derecha`: Mueve el gusano a la derecha
* `Enter`: Salto para adelante
* `Backspace`: Salto para atras
* `Mouse`: al moverlo se puede mover libremente la camara por el mundo
* `Armas`:
  * `Rueda Mouse`: Elije el arma que el gusano usara, basandose en el orden del HUD.
  * `Teclas`:
    * `e`: deselecciona las armas (punio limpio)
    * `r`: selecciona la Bazooka
    * `t`: selecciona la Granada verde
    * `y`: selecciona el Hacha
    * `u`: selecciona el RemoteOperated
    * `i`: selecciona el Mortero
    * `o`: selecciona la Granada roja
    * `p`: selecciona la Banana
  * `Numeros [0,5]`: Modifica el tiempo de explosion de las granadas.
  * `Mouse`: Con este se puede elegir el angulo del disparo, con el click se dispara.
* `Cheats`:
  *  `z`: Le suma vida al gusano actual (con un MaxHealth modificable desde el archivo de configuracion)
  *  `x`: Le otorga al gusano todas las armas
  *  `c`: Vuelve a todos los gusanos invencibles
  *  `v`: Deja estatico el turno, sin importar el tiempo/ perdida de vida/ uso de herramienta
  *  `b`: Vuelve a permitir los cambios de turno

