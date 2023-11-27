#ifndef INFO_STRUCT_H
#define INFO_STRUCT_H

#include "protocol.h"
#include "socket.h"

struct InfoStruct {
    Protocol prot;
    InfoStruct(Socket&& socket) : prot(std::move(socket)) {}
    InfoStruct(const std::string& hostname, const std::string& servname) : prot(hostname, servname) {}
    ~InfoStruct() {}

};

#endif