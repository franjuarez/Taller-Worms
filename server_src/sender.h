#ifndef SENDER_H
#define SENDER_H

#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"

class Sender : public Thread {

private:
    Protocol& protocol;
    // has the queue of each player
public:
    Sender(Protocol& protocol);
    ~Sender();
    void run() override;

};
#endif