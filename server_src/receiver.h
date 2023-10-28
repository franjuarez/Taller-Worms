#ifndef RECEIVER_H
#define RECEIVER_H

#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"

class Receiver : public Thread {

private:
    Protocol& protocol;
    // has the only queue of the game thread :)
public:
    Receiver(Protocol& protocol);
    ~Receiver();
    void run() override;

};
#endif