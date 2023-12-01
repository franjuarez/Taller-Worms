# Manual del Proyecto

Este juego fue implementado por 3 estudiantes, Francisco Juarez, Martina Lozano y Joaquin Pandolfi. Los roles fueron los siguientes:

## Division de tareas

* ### Francisco Juarez

    * Fisicas del juego, hechas usando Box2d
    * YAML

* ### Martina Lozano

    * Protocolo y de sus tests correspondientes
    * Arquitectura Cliente/Servidor
    * Logica del juego

* ### Joaquin Pandolfi

    * Graficos del juego, hecho usando SDL
    * Lobby, hecho usando Qt

## Herramientas y documentacion

Nuestras herramientas principales fueron:

* IDE: Visual Studio Code (utlizando Live Share para las partes compartidas)
* Control de versiones: git
* Chequeo de memoria: Valgrind

La documentacion utilizada fue la siguiente:

* Para Box2d usamos principalmente la documentacion oficial (que esta en el repositorio de Box2d) junto a  [iforce2d](https://www.iforce2d.net/b2dtut/introduction)
* Para SDL2pp usamos 2: [libSDL2pp](https://sdl2pp.amdmi3.ru/) y [Lazy Foo](https://lazyfoo.net/tutorials/SDL/)
* Para QT usamos [la documentacion oficial](https://doc.qt.io/)
* Para la parte de Testing usamos la [documentacion oficial](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#getting-catch2) de Catch2

## Cronograma

Uno de los mayores problemas encontrados al encarar un proyecto asi de grande fue la division del tiempo y de tareas. Ninguno de los integrantes contaba con experiencia previa en un proyecto de tal magnitud. 

Dividimos el proyecto en 3 partes principales: el Frontend, la fisica y la arquitectura de comunicacion cliente/servidor. Por ende decidimos organizarnos de manera de que cada uno este a cargo de cada una de estas partes.

Una parte **clave** del trabajo en equipo es la comunicacion, por ende al desarrollar el proyecto fuimos teniendo muchas reuniones (Dailys) en las que fuimos estableciendo prioridades acerca de las Features que ibamos a implementar. En estas reuniones decidiamos los objetivos cercanos y nos dividiamos asi despues cada uno implementaba su parte correspondiente para los Features propuestos.

La primera semana la dedicamos a hacer una PoC de box2d y SDL, en esta participamos todos los integrantes. Fue una buena practica para no solo familiarizarnos con ambas herramientas, sino con las de compilacion (cmake).

## Problemas Encontrados

Lo que mas nos costo fue poder acostumbrarnos a las librerias pertinentes a cada parte (Qt, Box2d, SDL, Catch2). Esto nos trajo muchos problemas ya que no sabiamos la mejor manera de hacer las cosas y tuvimos que volver varias veces a cambiar el mismo codigo en diferentes momentos para arreglarlo.

Ademas, otra cosa que nos complico bastante en el desarrollo del proyecto fue la inmensidad del mismo. Este es **muy** grande por ende organizarnos fue todo un reto. Aunque hicimos lo dicho anteriormente tuvimos partes donde estabamos implementando muchos Features en simultaneo y a la vez arreglando otros, por ende la organizacion costo mucho.

Otro factor que nos complico al inicio del proyecto fue el cmake, nos costo bastante y nos fue dificil encontrar como hacer las cosas correctamente. Al inicio perdimos bastante tiempo entendiendo como linkear archivos y carpetas.

## Feedback

Si bien estuvo muy bueno aprender a familiarisarse con librerias nuevas, esto fue muy complicado en el tiempo estipulado. Al tener poco tiempo no le pudimos dedicar una buena parte a la lectura de la documentacion y familiarizacion de la libreria, por ende se nos complico mucho llegar bien con las cosas. Ademas las librerias tienen sus restricciones que no nos dejaron poder implementar el proyecto de la mejor manera, ya que no proveen mecanismos para hacer ciertas cosas y el buscarle la vuelta hizo que las cosas no queden al 100%. Hubiese estado bueno tener alguna libreria mas util o un poco de tiempo mas.
