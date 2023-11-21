#include <exception>
#include <iostream>
#include <string>

class InvalidMap: public std::exception {
private:
    std::string message_;

public:
    explicit InvalidMap(const char* mensaje): message_(mensaje) {}

    const char* what() const noexcept override { return message_.c_str(); }
};
