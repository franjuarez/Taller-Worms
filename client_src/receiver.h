#ifndef RECEIVER_H
#define RECEIVER_H

#include "../shared_src/queue.h"
#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"

#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"

#include <iostream>

class Receiver : public Thread {

private:
    Protocol& protocol;
    Queue<GameDynamic>& gameStatuses;
public:

    // ideas -> poner GameMap y GameDynamic en un Game y protejerlos con un mutex?
    Receiver(Protocol&, Queue<GameDynamic>&);
    void run() override;
    ~Receiver();
};
#endif
