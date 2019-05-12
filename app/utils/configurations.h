#ifndef CONFIGURATIONS_H_INCLUDED
#define CONFIGURATIONS_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

struct DataCFG{
    string train_X_file;
    string train_X_folder;
    string train_y_file;
    string validate_X_file;
    string validate_X_folder;
    string validate_y_file;
    string test_X_file;
    string test_X_folder;
    vector<int> X_columns;
    vector<int> y_columns;
    // int X_columns[];
    // int y_columns[];
    // int num_X_col;
    // int num_y_col;
    string data_format;
    DataCFG(){
        train_X_file = "";
        train_X_folder = "";
        train_y_file = "";
        validate_X_file = "";
        validate_X_folder = "";
        validate_y_file = "";
        test_X_file = "";
        test_X_folder = "";
        data_format = "";
    }
};

struct ModelCFG{
    string archi_path;
    string weight_path;
    ModelCFG(){
        archi_path = "";
        weight_path = "";
    }
};

struct CompileCFG{
    string archi_path;
    CompileCFG(){
        archi_path = "";
    }
};

struct TrainCFG{
    
};

struct TestCFG{
    
};


#endif // CONFIGURATIONS_H_INCLUDED
