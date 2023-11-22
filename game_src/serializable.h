#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

class Protocol;

class Serializable {
public:
    Serializable() {}
    ~Serializable() {}
    virtual void send(Protocol& protocol) = 0;
};
#endif
