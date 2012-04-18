#ifndef INVALIDCARDEXCEPTION_H
#define INVALIDCARDEXCEPTION_H

#include "card.h"

#include <stdexcept>
#include <exception>
#include <string>

class InvalidCardException : public std::exception
{
public:
    InvalidCardException(std::string message = "Invalid Card!") : _message(message) {}
    ~InvalidCardException() throw() {}
    const char* what() const throw() { return _message.c_str(); }
private:
    std::string _message;
};

#endif // INVALIDCARDEXCEPTION_H
