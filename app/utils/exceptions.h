#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <exception>
#include <string>

using namespace std;

class NoInputException : public exception{
    const char* what() const noexcept {
        return "Model has no input layer!";
    }
};

class ShapeMismatchException : public exception{
public:
    string msg;
    ShapeMismatchException(string msg="")
        :msg("Shapes of two ports do not match! " + msg){}
    const char* what() const noexcept {
        return msg.data();
    }
};

class IOMismatchException : public exception{
    const char* what() const noexcept {
        return "IOs of two ports do not match!";
    }
};

class InvalidParameterException : public exception{
public:
    string msg;
    InvalidParameterException(string msg="")
        :msg("Invalid parameter name or value! " + msg){}
    const char* what() const noexcept{
        return msg.data();
    }
};

class InvalidPathException : public exception{
public:
    string msg;
    InvalidPathException(string msg=""):msg("Invalid path! " + msg){}
    const char* what() const noexcept{
        return msg.data();
    }
};

class DataErrorException : public exception{
public:
    string msg;
    DataErrorException(string msg=""):msg("Data error! " + msg){}
    const char* what() const noexcept{
        return msg.data();
    }
};

#endif // EXCEPTIONS_H_INCLUDED
