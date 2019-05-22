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
string KerasConverter::getPythonFileModel(const GraphModel &gm, CompileCFG cfg)
{
    vector<int> input_parts_idx = gm.get_input_parts_idx(); // use input parts to determine the start point
    shared_ptr<Part> pap;
    string tstr;
    map<string, string> tmap;

    // check existance of input part
    if (input_parts_idx.size() <= 0)
    {
        cout << "NoInput";
        getchar();
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
    if (pap->ports[1].size() > 0 && pap->ports[1][0]->connection.lock() != nullptr)
    {
        if (shared_ptr<Port> tmp_port = pap->ports[1][0]->connection.lock()->ports[1].lock())
        {
            pap = tmp_port->part.lock();
        }
        tmap = pap->params; // Is inplace?
        tmap.insert(pair<string, string>("input_shape", tstr));
        add_layer(pap->parttype, tmap);
        while (pap->ports[1].size() > 0 && pap->ports[1][0]->connection.lock() != nullptr)
        {
            if (shared_ptr<Port> tmp_port = pap->ports[1][0]->connection.lock()->ports[1].lock())
            {
                pap = tmp_port->part.lock();
            }
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
    if (cfg.archi_path.find(".json") != string::npos)
    {
        addline("json_str = m.to_json()");
        with_state("codecs.open(r'" + cfg.archi_path + "', 'w', encoding='utf-8')", "outfile");
        addline("outfile.write(json_str)");
        unindent();
    }
    else if (cfg.archi_path.find(".yaml") != string::npos)
    {
        addline("yaml_str = m.to_yaml()");
        with_state("codecs.open(r'" + cfg.archi_path + "', 'w', encoding='utf-8')", "outfile");
        addline("outfile.write(yaml_str)");
        unindent();
    }
    else
    {
        throw InvalidPathException("Architecture can only be json file or yaml file!");
    }

    return pyfile;
}

/* get python file for training */
string KerasConverter::getPythonFileTrain(const GraphModel &gm, TrainCFG cfg)
{
    // set up python file
    newfile();
    group_import();
    import_state("model_from_json", "", "keras.models");
    import_state("model_from_yaml", "", "keras.models");
    addline();

    load_data();
    addline(2);

    // load_model function
    def_state("load_model");
    // load architecture
    if (gm.model_cfg.archi_path.find(".json") != string::npos)
    {
        with_state("codecs.open(r'" + gm.model_cfg.archi_path + "', 'r', encoding='utf-8')", "infile");
        addline("json_str = infile.read()");
        addline("model = model_from_json(json_str)");
        unindent();
    }
    else if (gm.model_cfg.archi_path.find(".yaml") != string::npos)
    {
        with_state("codecs.open(r'" + gm.model_cfg.archi_path + "', 'r', encoding='utf-8')", "infile");
        addline("yaml_str = infile.read()");
        addline("model = model_from_yaml(yaml_str)");
        unindent();
    }
    else
    {
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
    if (cfg.reuse_weight)
    {
        if (gm.model_cfg.weight_path.find(".h5") != string::npos)
        {
            // TODO: possible assertions
            addline("model.load_weights(r'" + gm.model_cfg.weight_path + "')");
        }
        else
        {
            throw InvalidPathException("Model weights can only be HDF5 file!");
        }
    }
    // set TB log
    addline("callbacks = [keras.callbacks.TensorBoard(" + parse_tb_param(cfg.tb_cfg) + ")]");
    // start training
    addline("history = model.fit(" + parse_fit_param(gm.data_cfg, cfg) + ")");
    // save weights
    if (cfg.save_weight_path.find(".h5") != string::npos)
    {
        addline("model.save_weights(r'" + cfg.save_weight_path + "')");
    }
    else
    {
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
string KerasConverter::getPythonFileTest(const GraphModel &gm, TestCFG cfg)
{
    newfile();
    group_import();

    return "if __name__ == '__main__':\n\tprint('Default Test File')";
}

#pragma endregion GetFileFuncs

#pragma region Utils

void KerasConverter::group_import()
{
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

void KerasConverter::add_layer(PartType parttype, map<string, string> params, string model)
{
    addline(model + ".add(L." + string(PartTypeString[as_integer(parttype)]) + "(" + to_param_list(params) + "))");
}

string KerasConverter::parse_compile_param(TrainCFG train_cfg) const
{
    string param = "";
    param += "optimizer='" + train_cfg.optimizer + "', ";
    param += "loss='" + train_cfg.loss + "', ";
    param += "metrics=[";
    for (int i = 0; i < train_cfg.metrics.size(); i++)
    {
        param += "'" + train_cfg.metrics[i] + "',";
    }
    param += "]";
    return param;
}

string KerasConverter::parse_fit_param(TrainCFG train_cfg) const
{
    string param = "x=x_train, y=y_train, ";

    param += "batch_size=" + train_cfg.batch_size + ", ";
    param += "epochs=" + train_cfg.epochs + ", ";
    param += "shuffle=" + train_cfg.shuffle + ", ";
    param += "validation_split=" + train_cfg.validation_split;

    return param;
}

string KerasConverter::parse_tb_param(TBCFG tb_cfg) const
{
    string param = "";
    param += "log_dir='" + tb_cfg.log_dir + "', ";
    param += "histogram_freq=" + tb_cfg.histogram_freq + ", ";
    param += "update_freq=" + tb_cfg.update_freq;
    return param;
}

void kerasConverter::load_data(DataCFG data_cfg)
{
    if (data_cfg.dataset != "")
    {
        if (data_cfg.dataset == "cifar10" ||
            data_cfg.dataset == "cifar100" ||
            data_cfg.dataset == "imdb" ||
            data_cfg.dataset == "reuters" ||
            data_cfg.dataset == "mnist" ||
            data_cfg.dataset == "fashion_mnist" ||
            data_cfg.dataset == "boston_housing")
        {
            import_state(data_cfg.dataset, "", "keras.datasets");
            addline("(x_train, y_train), (x_test, y_test) = " + data_cfg.dataset + ".load_data()");
        }
        else
        {
            throw DataErrorException("Unknown dataset!");
        }
    }
}

#pragma endregion Utils
