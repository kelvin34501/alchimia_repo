#ifndef CONFIGURATIONS_H_INCLUDED
#define CONFIGURATIONS_H_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <QString>

using namespace std;

/* Backend for converter to select */
enum class Backend
{
    Keras,
    Pytorch
};

struct ProjectCFG{
    QString name;
    QString location;
    QString pro_desc_path;
    QString python_path;
    QString tensorboard_path;
    Backend backend;
};

struct DataCFG{
    // built-in datasets in keras
    string dataset;
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
    string data_format;
    DataCFG(){
        dataset = "";
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
    ModelCFG(string ap="", string wp=""){
        archi_path = ap;
        weight_path = wp;
    }
};

struct TBCFG{
    string log_dir;
    string histogram_freq;
    string update_freq;
    TBCFG(){
        log_dir = "";
        histogram_freq = "1";
        update_freq = "'batch'";
    }
};

/* CompileCFG: compilation configuration */
/* fields:
    archi_path: string, the storage path for the generated architecture,
        selected by the user before compilation
    pyfile_path: string, the storage path for the python file for compile,
        selected by the user before compilation
*/
struct CompileCFG{
    string archi_path;
    string pyfile_path;
    string archi_name;
    CompileCFG(string an = "", string ap="", string pp=""){
        archi_path = ap;
        pyfile_path = pp;
        archi_name = an;
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
    string save_weight_dir;
    string model_name;
    bool reuse_weight;
    TBCFG tb_cfg;
    TrainCFG(){
        optimizer = "rmsprop";
        loss = "categorical_crossentropy";
        batch_size = "32";
        epochs = "10";
        validation_split = "0.2";
        shuffle = "True";
        reuse_weight = false;
        save_weight_dir = "";
        model_name = "";
    }
};

struct TestCFG{
    string save_dir;
    string file_name;
    TestCFG(){
        save_dir = "D:/a/results";
        file_name = "test_results";
    }
};


#endif // CONFIGURATIONS_H_INCLUDED
