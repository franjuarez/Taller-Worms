
#include "receiver.h"

#include <iostream>

Receiver::Receiver(Protocol& protocol, Queue<GameStatus>& q) : protocol(protocol), gameStatuses(q) {}

void Receiver::run() {
    // primero necesitamos cargar los mapas del juego 

    // cuando se este jugando es cuando recibimos la info de GAME
}

Receiver::~Receiver() {}