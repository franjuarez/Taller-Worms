#ifndef RECEIVER_H
#define RECEIVER_H

#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "../shared_src/protocol.h"

class Receiver : public Thread {

private:
    Protocol& protocol;
    Queue<Command>& commandsQueue;
    bool& talking;
    // has the only queue of the game thread :)
public:
    Receiver(Protocol& protocol, Queue<Command>& commandsQueue, bool& talking);
    ~Receiver();
    void run() override;

};
#endif