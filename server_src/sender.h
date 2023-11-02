#ifndef SENDER_H
#define SENDER_H

#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"
#include "../shared_src/queue.h"

#include "status_broadcaster.h"

class Sender : public Thread {

private:
    int id;
    Protocol& protocol;
    Queue<Game>& playerQueue;
    bool& talking;
    // has the queue of each player
public:
    Sender(int id, Protocol& protocol, Queue<Game>& playerQueue, bool& talking);
    ~Sender();
    void run() override;

};
#endif