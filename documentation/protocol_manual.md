# Documentacion Tecnica

## Requisitos 

????


## El Juego

La logica de comunicacion se dividio en dos partes: cliente y servidor. El servidor es quien cuenta con la logica del juego, tambien asi esta en contacto con la fisica provista por box2d. Por otro lado, el jugador solo maneja la parte visual y los comandos del usuario. El cliente y el  servidor se comunican mediante sockets, haciendo uso de un protocolo de comunicacion. Para simplificar la comunicacion, se hizo uso de la herencia de los objetos la cual permite contar con dos clases madre que envielven la logica necesaria.

El uso de un socket aceptador en el servidor permite contar con un juego multijugador, una clase Player permite encapsular el comportamiento de cada cliente, enviando y recibiendo sus mensajes. 

La consigna pide un juego multi-partidas, donde puedan suceder 2 o mas partidas en simultaneo, para ello se hace uso de las Threads. Cada partida se encuentra en su propia thread, asi tambien la clase encargada de unir a los jugadores a una partida existente o crear una nueva, de esta forma puede esperar el input del usuario sin bloquear al socket aceptador. 

