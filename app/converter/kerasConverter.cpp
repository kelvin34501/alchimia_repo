#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../graphmodel/graphmodel.h"
#include "../utils/configurations.h"
#include "converter.h"

using namespace std;

#pragma region GetFileFuncs

string KerasConverter::getPythonFileModel(const GraphModel &gm, CompileCFG cfg){
    vector<int> input_parts_idx = gm.get_input_parts_idx();  // use input parts to determine the start point
    shared_ptr<Part> pap;
    string tstr;
    map<string, string> tmap;

    if(input_parts_idx.size() <= 0){
        cout << "NoInput"; getchar();
        throw NoInputException();
    }

    newfile();
    group_import();
    addline(2);

    def_state("generate_model");
    addline("model = Sequential()");
    pap = gm.parts[input_parts_idx[0]];
    tstr = pap->params["input_shape"];
    if(pap->ports[1].size() > 0 && pap->ports[1][0]->connection.lock() != nullptr){
        if(shared_ptr<Port> tmp_port = pap->ports[1][0]->connection.lock()->ports[1].lock()) {
            pap = tmp_port->part.lock();
        }
        tmap = pap->params;  // Is inplace?
        tmap.insert(pair<string, string>("input_shape", tstr));
        add_layer(pap->parttype, tmap);
        while(pap->ports[1].size() > 0 && pap->ports[1][0]->connection.lock() != nullptr){
            if(shared_ptr<Port> tmp_port = pap->ports[1][0]->connection.lock()->ports[1].lock()) {
                pap = tmp_port->part.lock();
            }
            add_layer(pap->parttype, pap->params);
        }
    }
    addline("return model");

    addline(2);
    if_main_state();
    addline("m = generate_model()");
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

/* TODO: get python file for training */
string KerasConverter::getPythonFileTrain(const GraphModel &gm, TrainCFG cfg){
    newfile();
    group_import();

    def_state("train_model");

    return "if __name__ == '__main__':\n\tprint('Default Train File')";
}

/* TODO: get python file for testing */
string KerasConverter::getPythonFileTest(const GraphModel &gm, TestCFG cfg){
    newfile();
    group_import();

    return "if __name__ == '__main__':\n\tprint('Default Test File')";
}

#pragma endregion GetFileFuncs

#pragma region SupportFuncs

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
    addline(model + ".add(L." + string(PartTypeString[as_integer(parttype)]) + "(" + to_param_list(params) + "))");
}

#pragma endregion SupportFuncs

#pragma region Utils

#pragma endregion Utils
