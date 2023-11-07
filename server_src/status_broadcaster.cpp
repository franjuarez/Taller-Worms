#include "status_broadcaster.h"

StatusBroadcaster::StatusBroadcaster() {}

StatusBroadcaster::~StatusBroadcaster() {}

void StatusBroadcaster::addPlayer(int id, Queue<Serializable*>* playerQueue) {
    playersQueues[id] = playerQueue;
}

void StatusBroadcaster::broadcast(Serializable* game) {
    for (auto& playerQueue : playersQueues) {
        playerQueue.second->push(game);
    }
}

Serializable* StatusBroadcaster::getGame(int id) {
    return playersQueues[id]->pop();
}
