#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"
#include "../shared_src/queue.h"
#include "../game_src/serializable.h"
#include "status_broadcaster.h"

class ServerSender : public Thread {

private:
    Protocol& protocol;
    Queue<std::shared_ptr<Serializable>>& playerQueue;
    bool& talking;
    // has the queue of each player
public:

    ServerSender(Protocol& protocol, Queue<std::shared_ptr<Serializable>>& playerQueue, bool& talking);
    ~ServerSender();

    void run() override;

};
#endif