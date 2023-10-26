#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <iostream>

class Protocol {

private:
    bool was_closed;

    void sentUintEight(uint8_t);
    void sentUintSixteen(uint16_t);
    void sentUintThirtyTwo(uint32_t);
    void sendString(std::string);

    uint8_t receiveUintEight();
    uint16_t receiveUintSixteen();
    uint32_t receiveUintThirtyTwo();
    std::string receiveString();

    void checkClosed();

public:
    Protocol();
    ~Protocol();

};
#endif
