#ifndef GRAPHMODEL_H_INCLUDED
#define GRAPHMODEL_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "graphmodel_name.h"
#include "../converter/converter.h"
#include "../utils/configurations.h"

using namespace std;

#pragma region Components

/* Port declaration */
class Port{
public:
    Part *part;
    Connection *connection;
    bool is_output;  // 0 input, 1 output
    string shape;
    Port(Part *pa, bool io, string s){
        part = pa;
        is_output = io;
        shape = s;
        connection = nullptr;
    };
    // ~Port();
    void update_shape(string nsh);
};

/* Connection declaration */
class Connection{
public:
    Port *ports[2];  // 0 input end (output port), 1 output end (input port)
    int id;
    Connection(Port *fp=nullptr, Port *tp=nullptr){
        ports[0] = fp;
        ports[1] = tp;
    };
    ~Connection();
    void update_shape(string nsh);
};

/* Part declaration */
/* And some basic operations */
class Part{
public:
    PartType parttype;
    float position_x;
    float position_y;
    vector<Port*> ports[2];  // 0 input port, 1 output port
    map<string, string> params;
    int id;
    Part(PartType pt=None, float px=0, float py=0){
        parttype = pt;
        position_x = px;
        position_y = py;
        default_init();
    };
    ~Part(){
        // id = -1;
        cout << ports[0].size() << endl;
        cout << ports[1].size() << endl;
        for(int j=0; j<2; j++)
            for(int i=0; i<ports[j].size(); i++)
                if(ports[j][i] != nullptr){
                    // if(ports[j][i]->connection != nullptr){
                    //     ports[j][i]->connection->ports[!ports[j][i]->is_output] = nullptr;
                    // }
                    delete ports[j][i];
                }
        // TODO: notify the front-end to deletePartUI
        cout << "part deleted: " << id << endl;
    };
    /* Add ports */
    void AddInputPort(string sh=""){
        Port *po = new Port(this, 0, sh);
        ports[0].push_back(po);
    }
    void AddOutputPort(string sh=""){
        Port *po = new Port(this, 1, sh);
        ports[1].push_back(po);
    }
    /* Connect ports */
    /* Does not check whether shapes of two ports matches here */
    void ConnectPort(Connection *cn, bool io, int idx=0){
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
private:
    void default_init();
};

#pragma endregion Components

/* GraphModel declaration */
/* And converter interfaces */
class GraphModel{
public:
    vector<Part*> parts;
    vector<Connection*> connections;
    ModelCFG model_cfg;
    DataCFG data_cfg;
    GraphModel(enum Backend be){
        switch (be)
        {
        case Backend::Keras:
            py_cvt = new KerasConverter();
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
        delete py_cvt;
    }
    vector<int> get_input_parts_idx() const;  // index of all potential input parts
    void add(Part *pa);  // add part
    void add(Connection *cn);  // add part
    
    /* Following are the methods that can be called by the controls */
    /* I.E. they are the ones to be tested in the test cases        */
    /*                                                              */
    /* THE REGION IS NOT NAMED AFTER CONTROLS                       */

    #pragma region ModelEditor

    /* addPart: add a part to the model, auto set default parameters */
    /* param:
        pt: PartType
        px: x position of the part
        py: y position of the part
    */
    void addPart(PartType pt=None, float px=0, float py=0);
    /* addConnection: add a connection to the model, auto update io shape */
    /* param:
        id1: id of the first part
        id2: id of the second part
        io1: true if the first part is the output part (connected to the input end of the connection)
        io2: true if the second part is the output part (connected to the input end of the connection)
        pidx1: index of port on the first part
        pidx2: index of port on the second part
    */
    void addConnection(int id1, int id2, bool io1, bool io2, int pidx1=0, int pidx2=0);
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

    #pragma endregion ModelEditor

    #pragma region ModelConverter

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

    #pragma endregion ModelConverter

    #pragma region ModelManager

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

    #pragma endregion ModelManager

private:
    PythonConverter *py_cvt;
};

#endif // GRAPHMODEL_H_INCLUDED
