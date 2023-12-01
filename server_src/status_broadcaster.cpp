#include "status_broadcaster.h"

StatusBroadcaster::StatusBroadcaster() {}

StatusBroadcaster::~StatusBroadcaster() {}

void StatusBroadcaster::addPlayer(int id, Queue<std::shared_ptr<Serializable>>* playerQueue) {
    playersQueues[id] = playerQueue;
}

void StatusBroadcaster::broadcast(std::shared_ptr<Serializable> game) {
    std::lock_guard<std::mutex> lock(m);
    for (auto& playerQueue : playersQueues) {
        playerQueue.second->push(game);
    }
}

std::shared_ptr<Serializable> StatusBroadcaster::getGame(int id) {
    return playersQueues[id]->pop();
}

void StatusBroadcaster::deletePlayer(int id) {
    std::lock_guard<std::mutex> lock(m);
    playersQueues.erase(id);
}

bool StatusBroadcaster::isEmpty() {
    return playersQueues.size() == 0;
}