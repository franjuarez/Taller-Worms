#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../shared_src/protocol.h"

class Serializable {
public:
    Serializable() {}
    virtual ~Serializable() {}
    virtual void send(Protocol& protocol) = 0;
};

#endif
