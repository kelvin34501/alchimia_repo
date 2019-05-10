#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "graphmodel.h"

using namespace std;

#pragma region GraphModel

/* Index of all potential input parts */
vector<int> GraphModel::get_input_parts_idx() const{
    vector<int> idx;
    for(int i=0; i<parts.size(); i++){
        // if(parts[i]->input_ports.size() <= 0 && parts[i]->output_ports.size() >= 0){
        //     idx.push_back(i);
        // }
        if(parts[i]->parttype == PartType::InputLayer){
            idx.push_back(i);
        }
    }
    return idx;
}

void GraphModel::add(Part *pa){
    // char str[8];
    // sprintf(str, "%07X", parts.size());
    // pa->id = "P" + string(str);
    pa->id = parts.size();
    parts.push_back(pa);
}

void GraphModel::add(Connection *cn){
    // char str[8];
    // sprintf(str, "%07X", connections.size());
    // cn->id = "C" + string(str);
    cn->id = connections.size();
    connections.push_back(cn);
}

void GraphModel::addPart(PartType pt, float px, float py){
    Part *pa = new Part(pt, px, py);
    add(pa);
}

void GraphModel::addConnection(int id1, int id2, bool io1, bool io2, int pidx1, int pidx2){
    // int id1, id2;
    Connection *cn;

    // sscanf(pid1.data(), "%X", &id1);
    // sscanf(pid2.data(), "%X", &id2);
    if(!(io1 ^ io2)){
        cout << "IOMismatch"; getchar();
        throw IOMismatchException();
    }
    if(parts[id1]->ports[io1][pidx1]->shape != parts[id2]->ports[io2][pidx2]->shape){
        cout << "ShapeMismatch"; getchar();
        throw ShapeMismatchException();
    }
    if(io1){
        cn = new Connection(parts[id2]->ports[io2][pidx2], parts[id1]->ports[io1][pidx1]);
    }
    else{
        cn = new Connection(parts[id1]->ports[io1][pidx1], parts[id2]->ports[io2][pidx2]);        
    }
    parts[id1]->ConnectPort(cn, io1, pidx1);
    parts[id2]->ConnectPort(cn, io2, pidx2);
    add(cn);
}

#pragma endregion GraphModel

#pragma region Part

void Part::set_default_params(){
    switch (parttype)
    {
    case PartType::InputLayer:
        params.insert(pair<string, string>("input_shape", "(256,256,3)"));
        break;
    
    case PartType::Dense:
        params.insert(pair<string, string>("units", "64"));
        break;
    
    case PartType::Conv2D:
        params.insert(pair<string, string>("filters", "32"));
        params.insert(pair<string, string>("kernel_size", "(3,3)"));
        params.insert(pair<string, string>("stride", "(1,1)"));
        params.insert(pair<string, string>("padding", "'valid'"));
        break;
    
    case PartType::MaxPooling2D:
        params.insert(pair<string, string>("pool_size", "(2,2)"));
        params.insert(pair<string, string>("stride", "None"));
        params.insert(pair<string, string>("padding", "'valid'"));
        break;
    
    case PartType::Activation:
        params.insert(pair<string, string>("activation", "'softmax'"));
        break;

    case PartType::Dropout:
        params.insert(pair<string, string>("rate", "0.2"));
        break;
    
    case PartType::Flatten:
        break;
    
    case PartType::Reshape:
        params.insert(pair<string, string>("target_shape", "(-1,1)"));
        break;

    default:
        break;
    }

    params.insert(pair<string, string>("name", "'" + string(PartTypeString[parttype]) + "'"));
}


#pragma endregion Part