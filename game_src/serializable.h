#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../shared_src/protocol.h"

class Protocol;

class Serializable {
public:
    Serializable() {}
    ~Serializable() {}
    virtual void send(Protocol& protocol) = 0;
};
#endif
