#ifndef GRAPHMODEL_NAME_H_INCLUDED
#define GRAPHMODEL_NAME_H_INCLUDED

#include <iostream>
#include <map>
#include <string>

#include "exceptions.h"

using namespace std;

enum PartType{
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

typedef map<string, string> DataCFG;
// string train_X_file;
// string train_X_folder;
// string train_y_file;
// string validate_X_file;
// string validate_X_folder;
// string validate_y_file;
// string test_X_file;
// string test_X_folder;
// int X_columns[];
// int y_columns[];
// string data_format;

class Port;

class Connection;

class Part;

class GraphModel;

#endif // GRAPHMODEL_NAME_H_INCLUDED