#ifndef CLIENT_ERROR_H
#define CLIENT_ERROR_H

#include <exception>
#include <iostream>
#include <string>

struct ClientClosed : public std::runtime_error {
    ClientClosed() : std::runtime_error("Client is closed") {} 
}; 

#endif