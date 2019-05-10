#ifndef GRAPHMODEL_H_INCLUDED
#define GRAPHMODEL_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "graphmodel_name.h"
#include "converter.h"

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
    ~Port(){
        cout << "port deleted" << endl;
    };
};

/* Connection declaration */
class Connection{
public:
    Port *from_port;
    Port *to_port;
    // vector<Port*> ports[2];
    int id;
    Connection(Port *fp=nullptr, Port *tp=nullptr){
        from_port = fp;
        to_port = tp;
        // ports[0] = fp;
        // ports[1] = tp;
    };
    ~Connection(){
        cout << "connection deleted" << endl;
    };
};

/* Part declaration */
/* And some basic operations */
class Part{
public:
    PartType parttype;
    float position_x;
    float position_y;
    vector<Port*> ports[2];
    // vector<Port*> output_ports;
    map<string, string> params;
    int id;
    Part(PartType pt=None, float px=0, float py=0){
        parttype = pt;
        position_x = px;
        position_y = py;
        set_default_params();
    };
    ~Part(){
        for(int j=0; j<2; j++)
        for(int i=0; i<ports[j].size(); i++) delete ports[j][i];
        cout << "part deleted" << endl;
    };
    /* Add ports */
    void AddInputPort(string sh){
        Port *po = new Port(this, 0, sh);
        // input_ports.push_back(po);
        ports[0].push_back(po);
    }
    void AddOutputPort(string sh){
        Port *po = new Port(this, 1, sh);
        // output_ports.push_back(po);
        ports[1].push_back(po);
    }
    /* Connect ports */
    /* Does not check whether shapes of two ports matches here */
    // void ConnectInputPort(Connection *cn, int idx=0){
    void ConnectPort(Connection *cn, bool io, int idx=0){
        // if(idx >= input_ports.size()){
        if(idx >= ports[io].size()){
            throw range_error("input port index out of range");
        }
        // input_ports[idx]->connection = cn;
        ports[io][idx]->connection = cn;
        // cn->from_port = input_ports[idx];
        if(io){
            cn->from_port = ports[io][idx];
        }
        else{
            cn->to_port = ports[io][idx];            
        }
        // cn->ports[!io] = ports[io][idx];
    }
    // void ConnectOutputPort(Connection *cn, int idx=0){
    //     if(idx >= output_ports.size()){
    //         throw range_error("output port index out of range");
    //     }
    //     output_ports[idx]->connection = cn;
    //     cn->to_port = output_ports[idx];
    // }
    /* Set parameters */
    void SetParam(string key, string value){
        params[key] = value;
    }
private:
    void set_default_params();
};

#pragma endregion Components

/* GraphModel declaration */
/* And converter interfaces */
class GraphModel{
public:
    vector<Part*> parts;
    vector<Connection*> connections;
    string model_path;
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
        for(int i=0; i<parts.size(); i++) delete parts[i];
        for(int i=0; i<connections.size(); i++) delete connections[i];
        delete py_cvt;
    }
    string getPythonFileModel() const{
        return py_cvt->getPythonFileModel(*this);
    }
    string getPythonFileTrain() const{
        return py_cvt->getPythonFileTrain(*this);
    }
    string getPythonFileTest() const{
        return py_cvt->getPythonFileTest(*this);
    }
    vector<int> get_input_parts_idx() const;  // index of all potential input parts
    void add(Part *pa);  // add part
    void add(Connection *cn);  // add part
    void addPart(PartType pt=None, float px=0, float py=0);  // add part auto
    void addConnection(int id1, int id2, bool io1, bool io2, int pidx1=0, int pidx2=0);  // add connection auto
private:
    PythonConverter *py_cvt;
};

#endif // GRAPHMODEL_H_INCLUDED
