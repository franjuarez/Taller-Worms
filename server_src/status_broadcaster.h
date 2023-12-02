#ifndef STATUS_BROADCASTER_H
#define STATUS_BROADCASTER_H

#include "../shared_src/queue.h"

#include "../game_src/serializable.h"

#include <iostream>
#include <map>

class StatusBroadcaster {

private:
    std::mutex m;
    std::map<int, Queue<std::shared_ptr<Serializable>>*> playersQueues;

public:
    StatusBroadcaster();
    ~StatusBroadcaster();
    void addPlayer(int id, Queue<std::shared_ptr<Serializable>>* playerQueue);
    void broadcast(std::shared_ptr<Serializable> game);
    void deletePlayer(int id);
    bool isEmpty();
    std::shared_ptr<Serializable> getGame(int id);
};
#endif
