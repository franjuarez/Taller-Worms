#ifndef STATUS_BROADCASTER_H
#define STATUS_BROADCASTER_H

#include "../shared_src/queue.h"

#include "../game_src/serializable.h"

#include <iostream>
#include <map>

class StatusBroadcaster {

private:
    std::map<int, Queue<Serializable*>*> playersQueues;

public:
    StatusBroadcaster();
    ~StatusBroadcaster();
    void addPlayer(int id, Queue<Serializable*>* playerQueue);
    void broadcast(Serializable* game);
    Serializable* getGame(int id);
};
#endif
