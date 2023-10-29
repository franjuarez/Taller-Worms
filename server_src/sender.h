#ifndef SENDER_H
#define SENDER_H

#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"
#include "../shared_src/queue.h"


class Sender : public Thread {

private:
    Protocol& protocol;
    Queue<Game>& playerQueue;
    // has the queue of each player
public:
    Sender(Protocol&, Queue<Game>& );
    ~Sender();
    void run() override;

};
#endif