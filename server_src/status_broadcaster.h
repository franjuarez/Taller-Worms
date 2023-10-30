#ifndef STATUS_BROADCASTER_H
#define STATUS_BROADCASTER_H

#include "../shared_src/queue.h"

#include "../game_src/game.h"

#include <iostream>
#include <map>

class StatusBroadcaster {

private:
    std::map<int, Queue<Game>*> playersQueues;

public:
    StatusBroadcaster();
    ~StatusBroadcaster();
    void addPlayer(int id, Queue<Game>* playerQueue);
    void broadcast(Game& game);
    Game getGame(int id);
};
#endif
