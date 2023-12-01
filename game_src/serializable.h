#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../shared_src/protocol.h"

class Protocol;

class Serializable {

private:
    int serializableType = -1;

public:
    Serializable() {}
    ~Serializable() {}
    virtual void send(Protocol& protocol) = 0;
    virtual int getSerType() = 0;
};
#endif
