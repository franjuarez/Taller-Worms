#include "game_loop.h"

GameLoop::GameLoop(Queue<Command>& commandsQueue, StatusBroadcaster& statusBroadcaster) 
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster) {}

void GameLoop::start() {}

GameLoop::~GameLoop() {}