#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <exception>
#include <string>

using namespace std;

class NoInputException : public exception{
    const char* what() const throw(){
        return "Model has no input layer!";
    }
};

class ShapeMismatchException : public exception{
public:
    string msg;
    ShapeMismatchException(string msg=""):msg(msg){}
    const char* what() const throw(){
        return ("Shapes of two ports do not match! " + msg).data();
    }
};

class IOMismatchException : public exception{
    const char* what() const throw(){
        return "IOs of two ports do not match!";
    }
};

class InvalidParameterException : public exception{
public:
    string msg;
    InvalidParameterException(string msg=""):msg(msg){}
    const char* what() const throw(){
        return ("Invalid parameter name or value! " + msg).data();
    }
};

class InvalidPathException : public exception{
public:
    string msg;
    InvalidPathException(string msg=""):msg(msg){}
    const char* what() const throw(){
        return ("Invalid path! " + msg).data();
    }
};

class DataErrorException : public exception{
public:
    string msg;
    DataErrorException(string msg=""):msg(msg){}
    const char* what() const throw(){
        return ("Data error! " + msg).data();
    }
};

#endif // EXCEPTIONS_H_INCLUDED
