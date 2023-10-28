#ifndef RECEIVER_H
#define RECEIVER_H

#include "../shared_src/queue.h"
#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"

#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"
#include "../game_src/game_status.h"

#include <iostream>

class Receiver : public Thread {

private:
    Protocol& protocol;
    Queue<GameStatus>& gameStatuses;
public:

    // ideas -> poner GameMap y GameDynamic en un Game y protejerlos con un mutex?
    Receiver(Protocol&, Queue<GameStatus>&);
    void run() override;
    ~Receiver();
};
#endif

// recibir el equipo 
// 1ro una lista de lso nombres
// 2do el mapa que eligio 
// 3ro los dynamics