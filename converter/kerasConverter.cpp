#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../graphmodel/graphmodel.h"
#include "../utils/configurations.h"
#include "converter.h"

using namespace std;

#pragma region GetFileFuncs

/* get python file for compilation */
string KerasConverter::getPythonFileModel(const GraphModel &gm, CompileCFG cfg){
    vector<int> input_parts_idx = gm.get_input_parts_idx();  // use input parts to determine the start point
    Part *pap;
    string tstr;
    map<string, string> tmap;

    // check existance of input part
    if(input_parts_idx.size() <= 0){
        cout << "NoInput"; getchar();
        throw NoInputException();
    }
    
    // set up python file
    newfile();
    group_import();
    addline(2);

    // generate_model function
    def_state("generate_model");
    addline("model = Sequential()");
    pap = gm.parts[input_parts_idx[0]];
    tstr = pap->params["input_shape"];
    if(pap->ports[1].size() > 0 && pap->ports[1][0]->connection != nullptr){
        pap = pap->ports[1][0]->connection->ports[1]->part;
        tmap = pap->params;  // Is inplace?
        tmap.insert(pair<string, string>("input_shape", tstr));
        add_layer(pap->parttype, tmap);
        while(pap->ports[1].size() > 0 && pap->ports[1][0]->connection != nullptr){
            pap = pap->ports[1][0]->connection->ports[1]->part;
            add_layer(pap->parttype, pap->params);
        }
    }
    addline("return model");
    unindent();

    // main
    addline(2);
    if_main_state();
    addline("m = generate_model()");
    // save model
    if(cfg.archi_path.find(".json") != string::npos){
        addline("json_str = m.to_json()");
        with_state("codecs.open('" + cfg.archi_path + "', 'w', encoding='utf-8')", "outfile");
        addline("outfile.write(json_str)");
        unindent();
    }
    else if(cfg.archi_path.find(".yaml") != string::npos){
        addline("yaml_str = m.to_yaml()");
        with_state("codecs.open('" + cfg.archi_path + "', 'w', encoding='utf-8')", "outfile");
        addline("outfile.write(yaml_str)");
        unindent();
    }
    else{
        throw InvalidPathException("Architecture can only be json file or yaml file!");
    }

    return pyfile;
}

/* get python file for training */
string KerasConverter::getPythonFileTrain(const GraphModel &gm, TrainCFG cfg){
    // set up python file
    newfile();
    group_import();
    import_state("model_from_json", "", "keras.models");
    import_state("model_from_yaml", "", "keras.models");
    addline(2);

    // load_model function
    def_state("load_model");
    // load architecture
    if(gm.model_cfg.archi_path.find(".json") != string::npos){
        with_state("codecs.open('" + gm.model_cfg.archi_path + "', 'r', encoding='utf-8')", "infile");
        addline("json_str = infile.read()");
        addline("model = model_from_json(json_str)");
        unindent();
    }
    else if(gm.model_cfg.archi_path.find(".yaml") != string::npos){
        with_state("codecs.open('" + gm.model_cfg.archi_path + "', 'r', encoding='utf-8')", "infile");
        addline("yaml_str = infile.read()");
        addline("model = model_from_yaml(yaml_str)");
        unindent();
    }
    else{
        throw InvalidPathException("Architecture can only be json file or yaml file!");
    }
    addline("return model");
    unindent();

    // train_model function
    addline(2);
    def_state("train_model", "model");
    // compile
    addline("model.compile(" + parse_compile_param(cfg) + ")");
    // load weight
    if(cfg.reuse_weight){
        if(gm.model_cfg.weight_path.find(".h5") != string::npos){
            // TODO: possible assertions
            addline("model.load_weights('" + gm.model_cfg.weight_path + "')");
        }
        else{
            throw InvalidPathException("Model weights can only be HDF5 file!");
        }
    }
    // set TB log
    addline("callbacks = [keras.callbacks.TensorBoard(" + parse_tb_param(cfg.tb_cfg) + ")]");
    // start training
    addline("history = model.fit(" + parse_fit_param(gm.data_cfg, cfg) + ")");
    // save weights
    if(cfg.save_weight_path.find(".h5") != string::npos){
        addline("model.save_weights('" + cfg.save_weight_path + "')");
    }
    else{
        throw InvalidPathException("Model weights can only be HDF5 file!");
    }
    unindent();

    // main
    addline(2);
    if_main_state();
    addline("m = load_model()");
    addline("train_model(m)");

    return pyfile;
}

/* TODO: get python file for testing */
string KerasConverter::getPythonFileTest(const GraphModel &gm, TestCFG cfg){
    newfile();
    group_import();

    return "if __name__ == '__main__':\n\tprint('Default Test File')";    
}

#pragma endregion GetFileFuncs

#pragma region Utils

void KerasConverter::group_import(){
    import_state("numpy", "np");
    import_state("keras");
    import_state("keras.backend", "K");
    import_state("Sequential", "", "keras.models");
    import_state("keras.layers", "L");
    addline();
    import_state("codecs");
    import_state("json");
    import_state("yaml");
}

void KerasConverter::add_layer(PartType parttype, map<string, string> params, string model){
    addline(model + ".add(L." + string(PartTypeString[parttype]) + "(" + to_param_list(params) + "))");
}

string KerasConverter::parse_compile_param(TrainCFG train_cfg) const{
    string param = "";
    param += "optimizer='" + train_cfg.optimizer + "', ";
    param += "loss='" + train_cfg.loss + "', ";
    param += "metrics=[";
    for(int i=0; i<train_cfg.metrics.size(); i++){
        param += "'" + train_cfg.metrics[i] + "',";
    }
    param += "]";
    return param;
}

// TODO: parse parameters for fit
string KerasConverter::parse_fit_param(DataCFG data_cfg, TrainCFG train_cfg) const{
    // TODO: WHERE DOES THE TRAINING DATA COME FROM
    string param = "";
    
    return param;
}

string KerasConverter::parse_tb_param(TBCFG tb_cfg) const{
    string param = "";
    param += "log_dir='" + tb_cfg.log_dir + "', ";
    param += "histogram_freq=" + tb_cfg.histogram_freq + ", ";
    param += "update_freq=" + tb_cfg.update_freq;
    return param;
}

#pragma endregion Utils
