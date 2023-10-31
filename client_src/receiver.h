#ifndef RECEIVER_H
#define RECEIVER_H

#include "../shared_src/queue.h"
#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"

#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"
#include "../game_src/game_status.h"
#include "../game_src/game.h"

#include <iostream>

class Receiver : public Thread {

private:
    Protocol& protocol;
    Queue<Game>& gameStatuses;
public:
    Receiver(Protocol&, Queue<Game>&);
    void run() override;
    ~Receiver();
};

#endif
