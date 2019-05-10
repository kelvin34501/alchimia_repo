#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <exception>

using namespace std;

class NoInputException : public exception{
    const char* what() const throw(){
        return "Model has no input layer";
    }
};

class ShapeMismatchException : public exception{
    const char* what() const throw(){
        return "Shapes of two ports do not match";
    }
};

class IOMismatchException : public exception{
    const char* what() const throw(){
        return "IOs of two ports do not match";
    }
};

#endif // EXCEPTIONS_H_INCLUDED