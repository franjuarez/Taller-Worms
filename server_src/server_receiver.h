#ifndef RECEIVER_SERVER_H
#define RECEIVER_SERVER_H

#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "../shared_src/protocol.h"

class ServerReceiver : public Thread {

private:
    Protocol& protocol;
    Queue<std::shared_ptr<Command>>& commandsQueue;
    bool& talking;
public:
    ServerReceiver(Protocol& protocol, Queue<std::shared_ptr<Command>>& commandsQueue, bool& talking);
    ~ServerReceiver();
    void run() override;

};
#endif