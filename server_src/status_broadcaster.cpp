#include "status_broadcaster.h"

StatusBroadcaster::StatusBroadcaster() {}

StatusBroadcaster::~StatusBroadcaster() {}

void StatusBroadcaster::addPlayer(int id, Queue<Game>* playerQueue) {
    playersQueues[id] = playerQueue;
}

void StatusBroadcaster::broadcast(Game& game) {
    for (auto& playerQueue : playersQueues) {
        playerQueue.second->push(game);
    }
}

Game StatusBroadcaster::getGame(int id) {
    return playersQueues[id]->pop();
}
