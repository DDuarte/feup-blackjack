/*!
 * \file game_exceptions.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef GAME_EXCEPTIONS_H
#define GAME_EXCEPTIONS_H

#include "utilities.h"
#include "card.h"

#include <stdexcept>
#include <exception>
#include <string>

/*!
 * \class InvalidCardException
 *
 * \brief Card is invalid
 *
 */
class InvalidCardException : public std::exception
{
public:
    //! Constructor
    InvalidCardException(std::string message = "Invalid Card!") : _message(message) {}
    //! Destructor
    ~InvalidCardException() throw() {}
    //! Error message
    const char* what() const throw() { return _message.c_str(); }
private:
    std::string _message;
};

/*!
 * \class InvalidPlayerException
 *
 * \brief Player or player action invalid
 *
 */
class InvalidPlayerException : public std::exception
{
public:
    //! Constructor
    InvalidPlayerException(std::string message = "Invalid Player!") : _message(message) {}
    //! Destructor
    ~InvalidPlayerException() throw() {}
    //! Error message
    const char* what() const throw() { return _message.c_str(); }
private:
    std::string _message;
};

/*!
 * \class InvalidBetException
 *
 * \brief Player's bet is invalid
 *
 */
class InvalidBetException : public std::exception
{
public:
    //! Constructor
    InvalidBetException(std::string message = "Invalid Bet!") : _message(message) {}
    //! Destructor
    ~InvalidBetException() throw() {}
    //! Error message
    const char* what() const throw() { return _message.c_str(); }
private:
    std::string _message;
};

/*!
 * \class FileNotFoundException
 *
 * \brief Required file was not found
 *
 */
class FileNotFoundException : public std::exception
{
public:
    //! Constructor
    FileNotFoundException(std::string filename, std::string message = "File not found!") : _message(message), _filename(filename) {}
    //! Destructor
    ~FileNotFoundException() throw() {}
    //! Error message
    const char* what() const throw() { return _message.c_str(); }
    //! File that was not found
    const char* filename() const throw() { return _filename.c_str(); }
private:
    std::string _message;
    std::string _filename;
};

/*!
 * \class InvalidDelegateException
 *
 * \brief Delegate is invalid
 *
 */
class InvalidDelegateException : public std::exception
{
public:
    //! Constructor
    InvalidDelegateException(std::string message = "Invalid Delegate!") : _message(message) {}
    //! Destructor
    ~InvalidDelegateException() throw() {}
    //! Error message
    const char* what() const throw() { return _message.c_str(); }
private:
    std::string _message;
};

#endif // GAME_EXCEPTIONS_H
