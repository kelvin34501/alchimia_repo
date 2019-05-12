#include <iostream>
#include <fstream>

#include "../converter/converter.h"
#include "graphmodel.h"

using namespace std;

void test_model_basic();
void test_base_converter();
void test_model_gen();
void test_model_train();
void test_model_test();

void set_basic_model(GraphModel &gm);

int example()
{
    cout << "start testing" << endl;
    // test_model_basic();
    // test_base_converter();
    getchar();
    test_model_gen();

    getchar();
    return 0;
}

#pragma region TestFuncs

void test_model_basic(){
    cout << "test_model_basic" << endl;

    GraphModel gm(Keras);
    Part *pa;
    Connection *cn;

    cn = new Connection();

    pa = new Part();
    pa->AddOutputPort("-1,256,256,3");
    cout << pa->position_x << ", " << pa->position_y << endl;
    // cout << pa->input_ports.size() << ", " << pa->output_ports.size() << endl;
    cout << pa->ports[0].size() << ", " << pa->ports[1].size() << endl;
    gm.parts.push_back(pa);

    // pa->ConnectOutputPort(cn);
    pa->ConnectPort(cn, 1);

    pa = new Part();
    pa->AddInputPort("-1,256,256,3");
    cout << pa->position_x << ", " << pa->position_y << endl;
    // cout << pa->input_ports.size() << ", " << pa->output_ports.size() << endl;
    cout << pa->ports[0].size() << ", " << pa->ports[1].size() << endl;
    gm.parts.push_back(pa);

    // pa->ConnectInputPort(cn);
    pa->ConnectPort(cn, 0);

    // cout << gm.getPythonFileModel() << endl;
}

void test_base_converter(){
    cout << "test_base_converter" << endl;

    ofstream outfile("base_cvt.gen");

    PythonConverter *py_cvt = new KerasConverter();
    cout << py_cvt->test_base_converter() << endl;

    if(!outfile.is_open()){
        cout << "error saving files" << endl;
    }
    else{
        outfile << py_cvt->test_base_converter();
    }

    outfile.close();
    delete py_cvt;
}

void test_model_gen(){
    cout << "test_model_gen" << endl;

    GraphModel gm(Keras);
    set_basic_model(gm);
    // cout << gm.parts.size();
    // cout << gm.parts[0]->ports[1].size();
    // cout << "basic model set" << endl;

    ofstream outfile("model_gen.gen");

    CompileCFG cfg;
    cfg.archi_path = "./model.json";
    // PythonConverter *py_cvt = new KerasConverter();
    // cout << py_cvt->getPythonFileModel(gm) << endl;
    cout << gm.getPythonFileModel(cfg) << endl;

    if(!outfile.is_open()){
        cout << "error saving files" << endl;
    }
    else{
        outfile << gm.getPythonFileModel(cfg);
    }

    outfile.close();
    // delete py_cvt;
}


void set_basic_model(GraphModel &gm){
    // GraphModel gm(Keras);
    Part *pa;
    Connection *cn;
    int s1, s2;

    // cn = new Connection();

    pa = new Part(PartType::InputLayer);
    pa->AddOutputPort("-1,256,256,3");
    // cout << PartTypeString[pa->parttype] << endl;
    // gm.parts.push_back(pa);
    gm.add(pa);
    // pa->ConnectOutputPort(cn);
    // pa->ConnectPort(cn, 1);
    s1 = pa->id;

    pa = new Part(PartType::Activation);
    pa->AddInputPort("-1,256,256,3");
    // cout << PartTypeString[pa->parttype] << endl;
    // gm.parts.push_back(pa);
    gm.add(pa);
    // pa->ConnectInputPort(cn);
    // pa->ConnectPort(cn, 0);
    s2 = pa->id;

    // gm.add(cn);
    gm.addConnection(s1, s2, 1, 0);
    // cout << gm.getPythonFileModel() << endl;
}

#pragma endregion TestFuncs
