#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>

#include "graphmodel.h"
#include "../utils/string_utils.h"  // TODO: this cause reinlcusion of the file?

using namespace std;

void print_vector(vector<int> v){
    for(int i=0;i<v.size();i++) cout << v[i] << ' ';
}

#pragma region GraphModel

/* Index of all potential input parts */
vector<int> GraphModel::get_input_parts_idx() const{
    vector<int> idx;
    for(int i=0; i<parts.size(); i++){
        if(parts[i] != nullptr && parts[i]->parttype == PartType::InputLayer){
            idx.push_back(i);
        }
    }
    return idx;
}

int GraphModel::add(shared_ptr<Part> pa){
    pa->id = parts.size();
    parts.push_back(pa);
    return parts.size() - 1;
}

int GraphModel::add(shared_ptr<Connection> cn){
    cn->id = connections.size();
    connections.push_back(cn);
    return connections.size() - 1;
}

int GraphModel::addPart(PartType pt, float px, float py){
    shared_ptr<Part> pa = make_shared<Part>(pt, px, py);
    pa->default_init();
    return add(pa);
}

int GraphModel::addConnection(int id1, int id2, bool io1, bool io2, int pidx1, int pidx2){
    shared_ptr<Connection> cn;

    if(!(io1 ^ io2)){
        cout << "IOMismatch"; getchar();
        throw IOMismatchException();
    }
    if(parts[id1]->ports[io1][pidx1]->shape != ""
            && parts[id2]->ports[io2][pidx2]->shape != ""
            && parts[id1]->ports[io1][pidx1]->shape != parts[id2]->ports[io2][pidx2]->shape){
        cout << "ShapeMismatch"; getchar();
        throw ShapeMismatchException();
    }

    if(io1 && parts[id1]->ports[io1][pidx1]->shape != ""){
        parts[id2]->update_shape(parts[id1]->ports[io1][pidx1]->shape);
        parts[id2]->ports[io2][pidx2]->shape = parts[id1]->ports[io1][pidx1]->shape;
    }
    else if(io2){
        parts[id1]->update_shape(parts[id2]->ports[io2][pidx2]->shape);
        parts[id1]->ports[io1][pidx1]->shape = parts[id2]->ports[io2][pidx2]->shape;
    }
    if(io1){
        cn = make_shared<Connection>(parts[id2]->ports[io2][pidx2], parts[id1]->ports[io1][pidx1]);
    }
    else{
        cn = make_shared<Connection>(parts[id1]->ports[io1][pidx1], parts[id2]->ports[io2][pidx2]);
    }
    parts[id1]->ConnectPort(cn, io1, pidx1);
    parts[id2]->ConnectPort(cn, io2, pidx2);
    
    return add(cn);
}

void Part::default_init(){
    switch (parttype)
    {
    case PartType::InputLayer:
        params.insert(pair<string, string>("input_shape", "(256,256,3)"));
        AddOutputPort("None," + params["input_shape"].substr(1, params["input_shape"].length()-2) + ",");
        break;
    
    case PartType::Dense:
        params.insert(pair<string, string>("units", "64"));
        AddInputPort("");
        AddOutputPort("None," + params["units"] + ",");
        break;
    
    case PartType::Conv2D:
        params.insert(pair<string, string>("filters", "32"));
        params.insert(pair<string, string>("kernel_size", "(3,3)"));
        params.insert(pair<string, string>("strides", "(1,1)"));
        params.insert(pair<string, string>("padding", "'valid'"));
        AddInputPort("");
        AddOutputPort("");
        break;
    
    case PartType::MaxPooling2D:
        params.insert(pair<string, string>("pool_size", "(2,2)"));
        params.insert(pair<string, string>("strides", "(2,2)"));
        params.insert(pair<string, string>("padding", "'valid'"));
        AddInputPort("");
        AddOutputPort("");
        break;
    
    case PartType::Activation:
        params.insert(pair<string, string>("activation", "'softmax'"));
        AddInputPort("");
        AddOutputPort("");
        break;

    case PartType::Dropout:
        params.insert(pair<string, string>("rate", "0.2"));
        AddInputPort("");
        AddOutputPort("");
        break;
    
    case PartType::Flatten:
        AddInputPort("");
        AddOutputPort("");
        break;
    
    case PartType::Reshape:
        params.insert(pair<string, string>("target_shape", "(-1,1)"));
        AddInputPort("");
        AddOutputPort("");
        break;

    default:
        break;
    }

    params.insert(pair<string, string>("name", "'" +
                                       string(PartTypeString[as_integer(parttype)])
                                       + "'"));
}

map<string, string> GraphModel::getPartInfo(int id) const{
    if(id >= parts.size() || parts[id] == nullptr){
        throw out_of_range("The part does not exist!");
    }
    return parts[id]->getPartInfo();
}

map<string, string> GraphModel::editPart(int id, string key, string value){
    if(id >= parts.size() || parts[id] == nullptr){
        throw out_of_range("The part does not exist!");
    }
    return parts[id]->editPart(key, value);
}

void GraphModel::deletePart(int id){
    if(id >= parts.size() || parts[id] == nullptr){
        throw out_of_range("The part does not exist!");
    }
    for(int io=0; io<2; io++){
        for(int i=0; i<parts[id]->ports[io].size(); i++){
            if(parts[id]->ports[io][i] != nullptr && parts[id]->ports[io][i]->connection.lock() != nullptr){
                // connections[parts[id]->ports[io][i]->connection->id] = nullptr;
                deleteConnection(parts[id]->ports[io][i]->connection.lock()->id);
            }
        }
    }
    // delete parts[id];
    parts[id] = nullptr;
}

void GraphModel::deleteConnection(int id){
    if(id >= connections.size() || connections[id] == nullptr){
        throw out_of_range("The connection does not exist");
    }
    // delete connections[id];
    connections[id] = nullptr;
}

/* TODO: shape change update for other types */
void Part::update_shape(string nsh){
    vector<int> vi, vk, vs;
    int res = 1;
    switch (parttype)
    {
    case PartType::InputLayer:
        cout << "update shape" << endl;
        for(int i=0; i<ports[1].size(); i++){
            ports[1][i]->update_shape("None," + params["input_shape"].substr(1, params["input_shape"].size()-2));
        }
        break;

    case PartType::Dense:
        for(int i=0; i<ports[1].size(); i++){
            ports[1][i]->update_shape("None," + params["units"]);
        }
        if(nsh != "-"){
            if(nsh != "" && substr_count(nsh, ",") != 1){
                throw ShapeMismatchException("Input of dense layer should only have 2-dimensional shape!");
            }
            ports[0][0]->update_shape(nsh);
        }
        break;
    
    case PartType::Conv2D:
        if(nsh != "-"){
            if(nsh != "" && substr_count(nsh, ",") != 4){
                throw ShapeMismatchException("Input of conv2d layer should only have 4-dimensional shape!");
            }
            ports[0][0]->update_shape(nsh);
        }
        if(ports[0][0]->shape == ""){
            for(int i=0; i<ports[1].size(); i++){
                ports[1][i]->update_shape("");
            }
        }
        else{
            for(int i=0; i<ports[1].size(); i++){
                vi = stot(ports[0][0]->shape);
                vk = stot(params["kernel_size"]);
                vs = stot(params["strides"]);
                if(params["padding"] == "'same'"){
                    for(int j=0; j<vs.size(); j++){
                        vi[j+1] = ceil(double(vi[j+1]) / vs[j]);
                    }
                }
                else if(params["padding"] == "'valid'"){
                    for(int j=0; j<vs.size(); j++){
                        vi[j+1] = ceil(double(vi[j+1] - vk[j] + 1) / vs[j]);
                    }
                }
                else{
                    throw InvalidParameterException("Padding can only be 'same' or 'valid'!");
                }
                vi[vi.size()-1] = atoi(params["filters"].c_str());
                ports[1][i]->update_shape(ttos(vi));
            }
        }
        break;
    
    case PartType::MaxPooling2D:
        if(nsh != "-"){
            cout << nsh << endl;
            // cout << substr_count(nsh, ",") << endl;
            if(nsh != "" && substr_count(nsh, ",") != 4){
                throw ShapeMismatchException("Input of maxpooling2d layer should only have 4-dimensional shape!");
            }
            // cout << ports[0].size() << endl;
            ports[0][0]->update_shape(nsh);
        }
        if(ports[0][0]->shape == ""){
            for(int i=0; i<ports[1].size(); i++){
                ports[1][i]->update_shape("");
            }
        }
        else{
            for(int i=0; i<ports[1].size(); i++){
                vi = stot(ports[0][0]->shape);
                // cout << ports[0][0]->shape << " "; print_vector(vi); cout << endl;
                vk = stot(params["pool_size"]);
                // cout << params["pool_size"] << " "; print_vector(vk); cout << endl;
                vs = stot(params["strides"]);
                // cout << params["strides"] << " "; print_vector(vs); cout << endl;
                // cout << vs.size() << endl;
                if(params["padding"] == "'same'"){
                    for(int j=0; j<vs.size(); j++){
                        vi[j+1] = ceil(double(vi[j+1]) / vs[j]);
                    }
                    // cout << 1 << endl;
                }
                else if(params["padding"] == "'valid'"){
                    for(int j=0; j<vs.size(); j++){
                        vi[j+1] = ceil(double(vi[j+1] - vk[j] + 1) / vs[j]);
                    }
                    // cout << 2 << endl;
                }
                else{
                    throw InvalidParameterException("Padding can only be 'same' or 'valid'!");
                }
                // print_vector(vi);
                ports[1][i]->update_shape(ttos(vi));
                // cout << ttos(vi) << endl;
            }
        }
        break;
    
    case PartType::Activation:
        if(nsh != "-"){
            ports[0][0]->update_shape(nsh);
            for(int i=0; i<ports[1].size(); i++){
                ports[1][i]->update_shape(nsh);
            }
        }
        break;

    case PartType::Dropout:
        if(nsh != "-"){
            ports[0][0]->update_shape(nsh);
            for(int i=0; i<ports[1].size(); i++){
                ports[1][i]->update_shape(nsh);
            }
        }
        break;
    
    case PartType::Flatten:
        if(nsh != "-"){
            if(nsh != ""){
                vi = stot(nsh);
                if(vi.size() <= 1){
                    throw ShapeMismatchException("Input shape of the flatten layer should have at least 2 dimensions!");
                }
            }
            ports[0][0]->update_shape(nsh);
        }
        vi = stot(ports[0][0]->shape);
        for(int i=1; i<vi.size(); i++) res *= vi[i];  // starts from 1, because vi[0] = -1
        for(int i=0; i<ports[1].size(); i++){
            ports[1][i]->update_shape("None," + to_string(res));
        }
        break;
    
    case PartType::Reshape:
        /* TODO: not sure whether to remove this */
        break;

    default:
        break;
    }
}

map<string, string> Part::getPartInfo() const{
    map<string, string> tmap = params;
    tmap["num_input_port"] = to_string(ports[0].size());
    for(int i=0; i<ports[0].size(); i++){
        tmap["shape_input_port_" + to_string(i)] = ports[0][i]->shape;
    }
    tmap["num_output_port"] = to_string(ports[1].size());
    for(int i=0; i<ports[1].size(); i++){
        tmap["shape_output_port_" + to_string(i)] = ports[1][i]->shape;
    }
    tmap["id"] = to_string(id);

    return tmap;
}

map<string, string> Part::editPart(string key, string value){
    int dif;
    bool io;
    string sh = "";
    shared_ptr<Port> po;

    // add or remove ports
    if(key == "num_input_port" || key == "num_output_port"){
        io = (key == "num_output_port");
        dif = atoi(value.c_str()) - ports[io].size();
        if(dif > 0){
            if(ports[io].size() > 0){
                sh = ports[io][0]->shape;
            }
            while(0 < dif--){
                if(io){
                    AddOutputPort(sh);
                }
                else{
                    AddInputPort(sh);
                }
            }
        }
        else{
            while(0 > dif++){
                po = ports[io].back();
                // delete po;
                ports[io].pop_back();
            }
        }
    }
    // update parameters
    else if(params.count(key)){
        params[key] = value;
        update_shape();
        /* TODO: check if there are other updates to be made */
    }
    else{
        throw InvalidParameterException("No matching name!");
    }

    return getPartInfo();
}

#pragma endregion Part

#pragma region Port

// Port::~Port(){
//     if(connection != nullptr){
//         delete connection;
//     }
//     cout << "port deleted" << endl;
// };

void Port::update_shape(string nsh){
    shape = nsh;
    cout << "port shape update" << endl;
    // pass shape update down to next part
    if(is_output && connection.lock() != nullptr){
        connection.lock()->update_shape(nsh);
    }
}

#pragma endregion Port

#pragma region Connection

Connection::~Connection(){
    // make sure the deletion is not invoked by the part to update
    if(std::shared_ptr<Port> tmp_port = ports[1].lock()) {
        // acquire port
        if(std::shared_ptr<Part> tmp_part = tmp_port->part.lock()) {
            // acquire part
            tmp_part->update_shape("");  // clear shape
        }
        tmp_port->connection.lock() = nullptr;
    }
    if(std::shared_ptr<Port> tmp_port = ports[0].lock()) {
        // acquire port
        tmp_port->connection.lock() = nullptr;
    }
    
    // TODO: notify front-end to deleteConnectionUI
    cout << "connection deleted: " << id << endl;
}

void Connection::update_shape(string nsh){
    cout << "connection shape update" << endl;
    if(std::shared_ptr<Port> tmp_port = ports[1].lock()){
        tmp_port->update_shape(nsh);  // update shape of port
        if(std::shared_ptr<Part> tmp_part = tmp_port->part.lock()) {
            // acquire part
            tmp_part->update_shape(nsh);  // pass down shape update
        }
    }
}

#pragma endregion Connection
