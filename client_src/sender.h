#ifndef SENDER_H
#define SENDER_H

#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "../shared_src/protocol.h"
#include "../game_src/commands.h"

#include <iostream>
#include <string>

class Sender : public Thread {

private:
    Protocol& protocol;
    Queue<Command>& commandsQueue;
public:
    Sender(Protocol&, Queue<Command>& );
    void run() override;
    ~Sender();
};
#endif
