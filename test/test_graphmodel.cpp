#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "../converter/converter.h"
#include "graphmodel.h"
// #include "string_utils.h"

using namespace std;

void test_model_basic();
void test_base_converter();
void test_model_gen();
void test_model_train();
void test_model_test();

void set_basic_model(GraphModel &gm);
void print_map(map<string, string> m);

int main()
{
    cout << "start testing" << endl;
    // test_model_basic();
    // test_base_converter();
    getchar();
    // test_model_gen();
    test_model_train();

    cout << "all test pass" << endl;
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
    pa->AddOutputPort("None,256,256,3");
    cout << pa->position_x << ", " << pa->position_y << endl;
    // cout << pa->input_ports.size() << ", " << pa->output_ports.size() << endl;
    cout << pa->ports[0].size() << ", " << pa->ports[1].size() << endl;
    gm.parts.push_back(pa);

    // pa->ConnectOutputPort(cn);
    pa->ConnectPort(cn, 1);

    pa = new Part();
    pa->AddInputPort("None,256,256,3");
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
    cout << "basic model set" << endl;

    getchar();

    ofstream outfile("model_gen.gen");

    // PythonConverter *py_cvt = new KerasConverter();
    CompileCFG cfg;
    cfg.archi_path = "./model.json";
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

void test_model_train(){
    cout << "test_model_train" << endl;

    GraphModel gm(Keras);
    set_basic_model(gm);
    cout << "basic model set" << endl;

    getchar();

    ofstream outfile("model_train.gen");

    TrainCFG cfg;
    cfg.save_weight_path = "./weight.h5";
    gm.model_cfg.archi_path = "./model.json";
    cout << gm.getPythonFileTrain(cfg) << endl;

    if(!outfile.is_open()){
        cout << "error saving files" << endl;
    }
    else{
        outfile << gm.getPythonFileTrain(cfg);
    }

    outfile.close();
}

/* TODO: unit test for part/connection deletion and part info manipulation */
void set_basic_model(GraphModel &gm){
    Part *pa;
    Connection *cn;
    int s1, s2;

    // pa = new Part(PartType::InputLayer);
    // pa->AddOutputPort("256,256,3");
    // gm.add(pa);
    // s1 = pa->id;
    gm.addPart(PartType::InputLayer);
    cout << endl; print_map(gm.getPartInfo(0)); cout << endl;

    // pa = new Part(PartType::Activation);
    // pa->AddInputPort("None,256,256,3");
    // pa->AddOutputPort("None,256,256,3");
    // gm.add(pa);
    // s2 = pa->id;
    gm.addPart(PartType::MaxPooling2D);
    cout << endl; print_map(gm.getPartInfo(1)); cout << endl;

    gm.addConnection(0, 1, 1, 0);
    
    // pa = new Part(PartType::MaxPooling2D);
    // pa->AddInputPort("None,256,256,3");
    // gm.add(pa);
    // s1 = pa->id; 
    gm.addPart(PartType::Activation);
    cout << endl; print_map(gm.getPartInfo(2)); cout << endl;

    gm.addConnection(2, 1, 0, 1);
    cout << endl;
    for(int i=0; i<3; i++){
        cout << endl; print_map(gm.getPartInfo(i)); cout << endl;
    }

    gm.deleteConnection(1);
    cout << endl;
    for(int i=0; i<3; i++){
        cout << endl; print_map(gm.getPartInfo(i)); cout << endl;
    }

    gm.deletePart(1);
    cout << endl;
    for(int i=0; i<3; i++){
        if(i==1)continue;
        cout << endl; print_map(gm.getPartInfo(i)); cout << endl;
    }

    gm.addConnection(0, 2, 1, 0);
    cout << endl;
    for(int i=0; i<3; i++){
        if(i==1)continue;
        cout << endl; print_map(gm.getPartInfo(i)); cout << endl;
    }

    gm.editPart(0, "input_shape", "(128,128,8)");
    cout << endl;
    for(int i=0; i<3; i++){
        if(i==1)continue;
        cout << endl; print_map(gm.getPartInfo(i)); cout << endl;
    }
}

#pragma endregion TestFuncs

void print_map(map<string, string> m){
    for(map<string, string>::iterator iter=m.begin(); iter!=m.end(); iter++){
        cout << "(" << iter->first << ", " << iter->second << ")" << endl;
    }
}
