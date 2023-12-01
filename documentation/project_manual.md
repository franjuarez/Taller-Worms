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
* Control de veriones: git
* Repositorio: GitHub
* Chequeo de memoria: Valgrind

La documentacion utilizada fue la siguiente:

* Para Box2d usamos principalmente la documentacion oficial (que esta en el repositorio de Box2d) junto a  [iforce2d](https://www.iforce2d.net/b2dtut/introduction)
* Para SDL2pp usamos 2: [libSDL2pp](https://sdl2pp.amdmi3.ru/) y [Lazy Foo](https://lazyfoo.net/tutorials/SDL/)
* Para QT usamos [la documentacion oficial](https://doc.qt.io/)
* Para la parte de Testing usamos Catch2 junto a [su documentacion oficial](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#getting-catch2)

## Cronograma

Uno de los mayores problemas encontrados al encarar un proyecto asi de grande fue la division del tiempo y de tareas. Ninguno de los integrantes contaba con experiencia previa en un proyecto de tal magnitud. 

Dividimos el proyecto en 3 partes principales: el frontend, la fisica y la arquitectura de comunicacion. Por ende decidimos organizarnos de manera de que cada uno este a cargo de cada una de estas partes.

Una parte **clave** del trabajo en equipo es la comunicacion, por ende al desarrollar el proyecto fuimos teniendo muchas reuniones (Dailys) en las que fuimos estableciendo prioridades acerca de las Features que ibamos a implementar. Por ende en estas reuniones decidiamos los objetivos cercanos e implementabamos cada uno su parte correspondiente para los Features propuestos.

## Problemas Encontrados

Lo que mas nos costo fue poder acostumbrarnos a las librerias pertinentes a cada parte (Qt, Box2d, SDL, Catch2). Esto nos trajo muchos problemas ya que no sabiamos la mejor manera de hacer las cosas y tuvimos que volver varias veces a cambiar el mismo codigo en diferentes momentos para que ande.

Ademas, otra cosa que nos complico bastante el desarrollo del proyecto fue la inmensidad del mismo. Este es **muy** grande 

## Feedback