#ifndef SENDER_H
#define SENDER_H

#include "../shared_src/queue.h"
#include "../shared_src/thread.h"
#include "../shared_src/protocol.h"

#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"

#include <iostream>
#include <string>

class Sender : public Thread {

private:
    Protocol& protocol;
    
public:
    Sender(Protocol&);
    void run() override;
    ~Sender();
};
#endif
