#ifndef GRAPHMODEL_NAME_H_INCLUDED
#define GRAPHMODEL_NAME_H_INCLUDED

#include <iostream>
#include <map>
#include <string>

#include "../utils/exceptions.h"

using namespace std;

enum class PartType{
    None,
    InputLayer,  // this is a dummy part type, which does not have a counterpart in Keras
    Dense,
    Conv2D,
    MaxPooling2D,
    Activation,
    Dropout,
    Flatten,
    Reshape,
};
static const char* PartTypeString[] = {
    "None",
    "InputLayer",
    "Dense",
    "Conv2D",
    "MaxPooling2D",
    "Activation",
    "Dropout",
    "Flatten",
    "Reshape",
};

class Port;

class Connection;

class Part;

class GraphModel;

#endif // GRAPHMODEL_NAME_H_INCLUDED
