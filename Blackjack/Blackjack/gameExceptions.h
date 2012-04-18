#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

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

class InvalidScoreException : public std::exception
{
public:
    InvalidScoreException(std::string message = "Invalid Score!") : _message(message) {}
    ~InvalidScoreException() throw() {}
    const char* what() const throw() { return _message.c_str(); }
private:
    std::string _message;
};

class InvalidPlayerException : public std::exception
{
public:
    InvalidPlayerException(std::string message = "Invalid Player!") : _message(message) {}
    ~InvalidPlayerException() throw() {}
    const char* what() const throw() { return _message.c_str(); }
private:
    std::string _message;
};

class InvalidBetException : public std::exception
{
public:
    InvalidBetException(std::string message = "Invalid Bet!") : _message(message) {}
    ~InvalidBetException() throw() {}
    const char* what() const throw() { return _message.c_str(); }
private:
    std::string _message;
};

class FileNotFoundException : public std::exception
{
public:
    FileNotFoundException(std::string filename, std::string message = "Invalid Bet!") : _message(message), _filename(filename) {}
    ~FileNotFoundException() throw() {}
    const char* what() const throw() { return _message.c_str(); }
    const char* filename() const throw() { return _filename.c_str(); }
private:
    std::string _message;
    std::string _filename;
};

#endif // GAMEEXCEPTION_H
