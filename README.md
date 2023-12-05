# **Worms**

![worms-cover](https://github.com/franjuarez/Taller-Worms/assets/90098530/4fe08251-3309-4836-98e1-9c32221e30eb)

## Dependencias
* Sistema operativo Linux
* Cmake - v3.16.3
* libsdl2
* libsdl2-image - v2.6.3
* libsdl2-mixer - v2.6.3
* libsdl2-ttf - v2.20.2
* Qt - v5.15.2

## Instalacion

El juego viene con un instalador para facilitar su uso, este instala todo lo necesario para que el mismo ande.

 Ejecutar:

```bash
chmod +x installer.sh
./installer.sh
```

Si se quiere desinstalar el juego se puede ejecutar:

```bash
chmod +x uninstaller.sh
./uninstaller.sh
```

*NOTA: las lineas con `chmod` solo necesitan ejecutarse 1 vez ya que son para darle permisos al archivo*

## Ejecucion del juego

Una vez instalado el juego este se puede correr desde cualquier directorio de la siguiente manera:

* Primero hay que abrir el servidor, para esto hay que ejecutar en una terminal:

  ```bash
  ./wormsServer <puerto>
  ```

  *Nota: Reemplazar `<puerto>` por el numero puerto deseado.*

* Una vez tengamos el server corriendo en una terminal abrimos otra y ejecutamos lo siguiente:

  ```bash
  ./wormsClient
  ```

  Este comando abrira la interfaz grafica y elgiiendo la IP y el puerto a donde conectarse ya se puede disfrutar de este maravilloso juego.

## Como jugar

Una vez introducida la IP y el puerto veremos la siguiente pantalla:

![start-lobby](https://github.com/franjuarez/Taller-Worms/assets/90098530/3d40a9e2-be88-425a-b91c-4c6c4971a7f6)

### Crear una partida

Para jugar primero hay que crearla, por ende tocamos la opcion: `Create Game`. 

Dentro veremos la siguiente pantalla:

![create-game-lobby](https://github.com/franjuarez/Taller-Worms/assets/90098530/07e0de96-d300-4b7e-82b2-31d75bbb3632)

En esta debemos elegir:
* La cantidad de jugadores (1-4)
* El nombre de la partida
* El mapa a elegir (Clickeandolo o eligiendo uno custom)

Cabe destacar que la partida no empezara hasta que no se unan todos los jugadores.

**IMPORTANTE**: El juego no permite dos partidas con el mismo nombre. Cuando se termina una partida, ese nombre puede ser reutilizado. (Una partida se da como finalizada cuando ambos usuarios cerraron el juego).

### Unirse a una partida

Para unirse a una partida navegamos hacia `Join Game`.

Dentro veremos:

![join-game-lobby](https://github.com/franjuarez/Taller-Worms/assets/90098530/bd984d29-78f4-435d-9d79-dd920881548b)

En esta decidimos a que partida unirnos a traves del menu desplegable. En caso de crear partidas despuesde tener abierto el cliente se puede tocar el boton de refresh para buscar las ultimas partidas creadas.

### Ejemplo

Dejamos un pequeño ejemplo de como se puede crear una partida y unirse a ella usando un mapa oficial:

https://github.com/franjuarez/Taller-Worms/assets/90098530/5981a719-9928-4e01-b0df-fc507f8a5cee

## Configuraciones

Hay disponible un archivo de configuraciones donde se pueden modificar los valores por defecto de diferentes aspectos del juego. Simplemente modificando las variables pertinentes en `configuration.yaml` podes darle tu propio toque al juego para que quede lo mas divertido posible!

Al cambiar las configuraciones **no** hace falta recompilar el proyecto! Solamente corriendolo de vuelta se aplican!

## Mapas

### Seleccion
El juego viene con mapas oficiales por default pero tambien soporta la opcion de agregar mapas custom. La diversion nunca se termina!

Para usar los mapas oficiales basta con clickear su foto y asi iniciar la partida. 

Los custom se pueden seleccionar con el menu desplegable y despues clickeando `choose custom map`

### Creacion/Modificacion

Para poder agregar o modificar mapas existentes se deben seguir los siguientes pasos:

Primero hay que entrar a la carpeta `maps`. Dentro de esta hay un archivo `map_names.yaml` que contiene los nombres de todos los mapas junto con sus archivos correspondientes. Ademas en esta carpeta estan todos los archivos `.txt` de los mapas. 

Para agregar un mapa primero se debe agregar un archivo `.txt` de la siguiente manera:

En cada linea del archivo debe haber una viga o un gusano. En caso de ser una viga se debe indicar: 
  
`beam esquinaIzquierdaX esquinaIzquierdaY angulo largo`

y en caso de ser un gusano:

`worm centroDeMasaX centroDeMasaY`

Finalmente dentro del archivo `map_names.yaml` se debe agregar el nombre del mapa junto con el archivo `.txt` que contiene los datos de este.

Se pueden ver ejemplos dentro de la carpeta que ayudaran a entender mas facilmente el proceso.

Una vez agregado el mapa **hace falta** correr el instalador del proyecto para poder elegirlos

**IMPORTANTE**: Los mapas deben tener *al menos* 4 gusanos para que se soporten hasta 4 jugadores simultaneos

**IMPORTANTE**: NO modificar los nombres de los mapas oficiales

**IMPORTANTE**: Al crear un mapa, tener en cuenta que a partir de 2 metros para arriba, la caida le saca vida al gusano. De inicializar un gusano a altas alturas, este empezara con menos vida.

## Como jugar

* `Flecha Izquierda `: Mueve el gusano a la izquierda
* `Flecha Derecha `: Mueve el gusano a la derecha
* `Enter `: Salto para adelante
* `Backspace `: Salto para atras
* `Mouse `: al moverlo se puede mover libremente la camara por el mundo
* `Armas `:
  * `Rueda Mouse `: Elije el arma que el gusano usara, basandose en el orden del HUD.
  * `Teclas`:
    * `e `: deselecciona las armas (puño limpio)
    * `r `: selecciona la Bazooka
    * `t `: selecciona la Granada verde
    * `y `: selecciona el Hacha
    * `u `: selecciona el RemoteOperated
    * `i `: selecciona el Mortero
    * `o `: selecciona la Granada roja
    * `p `: selecciona la Banana
  * `Numeros [0,5] `: Modifica el tiempo de explosion de las granadas.
  * `Mouse `: Con este se puede elegir el angulo del disparo, con el click se dispara.
* `Cheats`:
  *  `z `: Le suma vida al gusano actual (con un MaxHealth modificable desde el archivo de configuracion)
  *  `x `: Le otorga al gusano todas las armas
  *  `c `: Vuelve a todos los gusanos invencibles, al tocarlo de vuelta se desactiva el cheat
  *  `v `: Deja estatico el turno, sin importar el tiempo/ perdida de vida/ uso de herramienta
  *  `b `: Vuelve a permitir los cambios de turno

* `Musica `: Se puede mutear y desmutear la musica y los SFX (ademas de usando el YAML) con la tecla `m`.


## Testing

El proyecto tambien contiene pruebas del protocolo, para correr estas se tiene que tener instalado el juego y correr:

```bash
chmod +x run_test.sh
./run_test.sh
```
