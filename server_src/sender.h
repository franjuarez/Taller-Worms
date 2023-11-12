#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"
#include "../shared_src/queue.h"
#include "../game_src/serializable.h"
#include "status_broadcaster.h"

class ServerSender : public Thread {

private:
    int id;
    Protocol& protocol;
    Queue<Serializable*>& playerQueue;
    bool& talking;
    // has the queue of each player
public:
    ServerSender(int id, Protocol& protocol, Queue<Serializable*>& playerQueue, bool& talking);
    ~ServerSender();
    void run() override;

};
#endif