#ifndef SENDER_H
#define SENDER_H

#include "./shared_src/queue.h"
#include <iostream>
#include <string>

class Sender {

private:
    Queue<std::string> mensajes;
public:
    Sender();
    ~Sender();
};
#endif
