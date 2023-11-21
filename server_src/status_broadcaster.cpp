#include "status_broadcaster.h"

StatusBroadcaster::StatusBroadcaster() {}

StatusBroadcaster::~StatusBroadcaster() {}

void StatusBroadcaster::addPlayer(int id, Queue<std::shared_ptr<Serializable>>* playerQueue) {
    playersQueues[id] = playerQueue;
}

void StatusBroadcaster::broadcast(std::shared_ptr<Serializable> game) {
    for (auto& playerQueue : playersQueues) {
        playerQueue.second->push(game);
    }
}

std::shared_ptr<Serializable> StatusBroadcaster::getGame(int id) {
    return playersQueues[id]->pop();
}
