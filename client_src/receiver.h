#ifndef RECEIVER_H
#define RECEIVER_H

#include "../shared_src/queue.h"
#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"

#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"
#include "../game_src/serializable.h"

#include <iostream>

class Receiver : public Thread {

private:
    Protocol& protocol;
    Queue<std::shared_ptr<Serializable>>& gameStatuses;
    bool& keepTalking;
public:
    Receiver(Protocol& protocol, Queue<std::shared_ptr<Serializable>>& q, bool& keepTaliking);
    void run() override;
    ~Receiver();
};

#endif
