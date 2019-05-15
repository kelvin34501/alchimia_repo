#ifndef GRAPHMODEL_H_INCLUDED
#define GRAPHMODEL_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "graphmodel_name.h"
#include "../converter/converter.h"
#include "../utils/configurations.h"
#include "../utils/enum_cast.hpp"

using namespace std;

/* Port declaration */
class Port{
public:
    weak_ptr<Part> part;
    weak_ptr<Connection> connection;
    bool is_output;  // 0 input, 1 output
    string shape;
    Port(shared_ptr<Part> pa, bool io, string s){
        part = pa;
        is_output = io;
        shape = s;
        connection = shared_ptr<Connection>(nullptr);
    }
    // ~Port();
    Port() {}
    void update_shape(string nsh);
};

/* Connection declaration */
class Connection{
public:
    weak_ptr<Port> ports[2];  // 0 input end (output port), 1 output end (input port)
    int id;
    Connection(shared_ptr<Port> fp=nullptr, shared_ptr<Port> tp=nullptr) {
        ports[0] = fp;
        ports[1] = tp;
    }
    ~Connection();
    void update_shape(string nsh);
};

/* Part declaration */
/* And some basic operations */
class Part: public enable_shared_from_this<Part> {
public:
    PartType parttype;
    float position_x;
    float position_y;
    // if the value of one parameter is a STRING in PYTHON code,
    // you MUST ADD '' TO THE VALUE, e.g. "'same'" (padding)
    vector<shared_ptr<Port>> ports[2];  // 0 input port, 1 output port
    map<string, string> params;
    int id;
    Part(PartType pt=PartType::None, float px=0, float py=0){
        parttype = pt;
        position_x = px;
        position_y = py;
    }
    ~Part(){
        // id = -1;
        cout << ports[0].size() << endl;
        cout << ports[1].size() << endl;
        /*for(int j=0; j<2; j++)
            for(int i=0; i<ports[j].size(); i++)
                if(ports[j][i] != nullptr){
                    // if(ports[j][i]->connection != nullptr){
                    //     ports[j][i]->connection->ports[!ports[j][i]->is_output] = nullptr;
                    // }
                    delete ports[j][i];
                }*/
        // TODO: notify the front-end to deletePartUI
        cout << "part deleted: " << id << endl;
    }
    /* Add ports */
    void AddInputPort(string sh=""){
        shared_ptr<Port> po = make_shared<Port>(shared_from_this(), 0, sh);
        ports[0].push_back(po);
    }
    void AddOutputPort(string sh=""){
        shared_ptr<Port> po = make_shared<Port>(shared_from_this(), 1, sh);
        ports[1].push_back(po);
    }
    /* Connect ports */
    /* Does not check whether shapes of two ports matches here */
    void ConnectPort(shared_ptr<Connection> cn, bool io, int idx=0){
        if(idx >= ports[io].size()){
            throw range_error("Input port index out of range!");
        }
        ports[io][idx]->connection = cn;
        cn->ports[!io] = ports[io][idx];
    }
    /* Set parameters */
    void SetParam(string key, string value){
        params[key] = value;
    }
    void update_shape(string nsh="-");  // update the input and output shape of connected parts recursively, this is used when connecting parts and modifying parts parameters
    map<string, string> getPartInfo() const;  // get part info
    map<string, string> editPart(string key, string value);  // edit part

    void default_init();
};

/* GraphModel declaration */
/* And converter interfaces */
class GraphModel{
public:
    vector<shared_ptr<Part>> parts;
    vector<shared_ptr<Connection>> connections;
    ModelCFG model_cfg;
    DataCFG data_cfg;
    GraphModel() {} // do nothing, only used for deserialization
    GraphModel(enum Backend be){
        switch (be)
        {
        case Backend::Keras:
            py_cvt = unique_ptr<PythonConverter>(new KerasConverter());
            break;
        
        default:
            break;
        }
    }
    ~GraphModel(){
        for(int i=0; i<parts.size(); i++){
            // cout << (parts[i] != nullptr) << endl;
            if(parts[i] != nullptr){
                // cout << parts[i]->id << endl;
                // getchar();
                deletePart(i);
                // getchar();
            }
        }
        // cout << 2 << endl;
        for(int i=0; i<connections.size(); i++)
            if(connections[i] != nullptr){
                deleteConnection(i);
            }
        //delete py_cvt;
    }
    vector<int> get_input_parts_idx() const;  // index of all potential input parts
    int add(shared_ptr<Part> pa);  // add part
    int add(shared_ptr<Connection> cn);  // add part
    
    /* Following are the methods that can be called by the controls */
    /* I.E. they are the ones to be tested in the test cases        */
    /*                                                              */
    /* THE REGION IS NOT NAMED AFTER CONTROLS                       */


    /* addPart: add a part to the model, auto set default parameters */
    /* param:
        pt: PartType
        px: x position of the part
        py: y position of the part
    */
    int addPart(PartType pt=PartType::None, float px=0, float py=0);
    /* addConnection: add a connection to the model, auto update io shape */
    /* param:
        id1: id of the first part
        id2: id of the second part
        io1: true if the first part is the output part (connected to the input end of the connection)
        io2: true if the second part is the output part (connected to the input end of the connection)
        pidx1: index of port on the first part
        pidx2: index of port on the second part
    */
    int addConnection(int id1, int id2, bool io1, bool io2, int pidx1=0, int pidx2=0);
    /* getPartInfo: returns a map containing all information of the part */
    /* param:
        id: id of the part
    */
    map<string, string> getPartInfo(int id) const;
    /* editPart: update part parameters, auto update other things */
    /* param:
        id: id of the part
        key: parameter name, should be the parameter that belongs to the part type (throw exceptions)
        value: parameter value, should be valid value of the parameter (throw exceptions)
       
       WARNING:
        if the value of one parameter is a STRING in PYTHON code,
        you MUST ADD '' TO THE VALUE, e.g. "'same'" (padding)
    */
    map<string, string> editPart(int id, string key, string value);
    /* deletePart: delete part, auto delete connections to it */
    /* param:
        id: id of the part, throw exceptions if the id does not exists or deleted before
    */
    void deletePart(int id);
    /* deleteConnection: delete connection, auto update port shape */
    /* param:
        id: id of the connection, throw exceptions if the id does not exists or deleted before
    */
    void deleteConnection(int id);

    /* getPythonFileModel: returns the python file string for model generation */
    string getPythonFileModel(CompileCFG cfg) const{
        return py_cvt->getPythonFileModel(*this, cfg);
    }
    /* getPythonFileTrain: returns the python file string for model training */
    string getPythonFileTrain(TrainCFG cfg) const{
        return py_cvt->getPythonFileTrain(*this, cfg);
    }
    /* getPythonFileTest: returns the python file string for model testing */
    string getPythonFileTest(TestCFG cfg) const{
        map<string, string> test_cfg;
        return py_cvt->getPythonFileTest(*this, cfg);
    }

    void setArchiPath(string path){
        if(path.find(".json") != string::npos){
            model_cfg.archi_path = path;
        }
        else if(path.find(".yaml") != string::npos){
            model_cfg.archi_path = path;
        }
        else{
            throw InvalidPathException("Architecture can only be json file or yaml file!");
        }
    };

    void setWeightPath(string path){
        if(path.find(".h5") != string::npos){
            model_cfg.weight_path = path;
        }
        else{
            throw InvalidPathException("Model weights can only be HDF5 file!");
        }
    }

    unique_ptr<PythonConverter> py_cvt;
};

#endif // GRAPHMODEL_H_INCLUDED
