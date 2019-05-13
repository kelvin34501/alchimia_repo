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

struct TBCFG{
    string log_dir;
    string histogram_freq;
    string update_freq;
    TBCFG(){
        log_dir = "";
        histogram_freq = "1";
        update_freq = "1000";
    }
};

struct CompileCFG{
    string archi_path;
    string pyfile_path;
    CompileCFG(string p1="", string p2=""){
        archi_path = p1;
        pyfile_path = p2;
    }
};

struct TrainCFG{
    string optimizer;
    string loss;
    vector<string> metrics;
    string batch_size;
    string epochs;
    string validation_split;
    string shuffle;
    string save_weight_path;
    bool reuse_weight;
    TBCFG tb_cfg;
    TrainCFG(){
        optimizer = "";
        loss = "";
        batch_size = "32";
        epochs = "1";
        validation_split = "0.0";
        shuffle = "True";
        reuse_weight = false;
        save_weight_path = "";
    }
};

struct TestCFG{
    
};


#endif // CONFIGURATIONS_H_INCLUDED
