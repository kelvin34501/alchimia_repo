#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "graphmodel.h"
#include "converter.h"

using namespace std;

#pragma region GetFileFuncs

string KerasConverter::getPythonFileModel(const GraphModel &gm){
    vector<int> input_parts_idx = gm.get_input_parts_idx();  // use input parts to determine the start point
    // cout << input_parts_idx.size();
    Part *pap;
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
    // cout << PartTypeString[pap->parttype] << endl;
    tstr = pap->params["input_shape"];
    // if(pap->output_ports[0]->connection != nullptr){
    
    if(pap->ports[1][0]->connection != nullptr){
        // pap = pap->output_ports[0]->connection->to_port->part;
        pap = pap->ports[1][0]->connection->to_port->part;
        // cout << PartTypeString[pap->parttype] << endl;
        tmap = pap->params;  // Is inplace?
        tmap.insert(pair<string, string>("input_shape", tstr));
        addline("model.add(" + string(PartTypeString[pap->parttype]) + "(" + to_param_list(tmap) + "))");
        /* keep adding new parts */

    }
    addline("return model");

    addline(2);
    if_main_state();
    addline("generate_model()");

    return pyfile;
}

string KerasConverter::getPythonFileTrain(const GraphModel &gm){
    newfile();
    group_import();

    return "if __name__ == '__main__':\n\tprint('Default Train File')";
}

string KerasConverter::getPythonFileTest(const GraphModel &gm){
    newfile();
    group_import();

    return "if __name__ == '__main__':\n\tprint('Default Test File')";    
}

#pragma endregion GetFileFuncs

#pragma region SupportFuncs

void KerasConverter::group_import(){
    import_state("numpy", "np");
    import_state("keras.backend", "K");
    import_state("Sequential", "", "keras.models");
    import_state("keras.layers", "L");
}

void KerasConverter::add_layer(PartType parttype, map<string, string> params, string model){
    // PartTypeString[parttype]
}

#pragma endregion SupportFuncs

#pragma region Utils

#pragma endregion
