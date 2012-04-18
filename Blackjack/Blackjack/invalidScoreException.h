#ifndef INVALIDSCOREEXCEPTION_H
#define INVALIDSCOREEXCEPTION_H

#include "card.h"

#include <stdexcept>
#include <exception>
#include <string>
#include <ctime>

class InvalidCardScoreException : public std::exception
{
public:
    InvalidCardScoreException(std::string message = "Invalid Card Score!") : _message(message) {}
    ~InvalidCardScoreException() throw() {}
    const char* what() const throw() { return _message.c_str(); }
private:
    std::string _message;
};

#endif // INVALIDSCOREEXCEPTION_H