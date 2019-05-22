#ifndef TST_CASE_H
#define TST_CASE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "converter/converter.h"
#include "graphmodel/graphmodel.h"

using namespace testing;

void compare_map(map<string,string> m1, map<string,string> m2);

//TEST(case, set)
//{
//    EXPECT_EQ(0, 0);
//    ASSERT_THAT(0, Eq(0));
//}

TEST(addPart, Inputlayer)
{

    GraphModel gm(Backend::Keras);
    int id;
    id = gm.addPart(PartType::InputLayer);

    map<string,string> oracle;
    oracle["input_shape"] = "(256,256,3)";
    oracle["num_input_port"] = "0";
    oracle["num_output_port"] = "1";
    oracle["shape_output_port_0"] = "None,256,256,3,";

    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(addPart, Dense)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;

    id = gm.addPart(PartType::Dense);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "None,64,";
    //Confirm it later.

    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(addPart, Conv2D)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;

    id = gm.addPart(PartType::Conv2D);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(addPart, MaxPooling2D)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;

    id = gm.addPart(PartType::MaxPooling2D);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(addPart, Activation)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;

    id = gm.addPart(PartType::Activation);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(addPart, Dropout)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;

    id = gm.addPart(PartType::Dropout);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(addPart, Flatten)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;

    id = gm.addPart(PartType::Flatten);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}


TEST(editPart,Inputlayer)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;
    id = gm.addPart(PartType::InputLayer);

    gm.editPart(id,"input_shape","(128,128,3)");
    gm.editPart(id,"num_output_port","2");
    gm.editPart(id,"name","MyInput");

    oracle["name"] = "MyInput";
    oracle["num_input_port"] = "0";
    oracle["num_output_port"] = "2";
    oracle["shape_output_port_0"] = "None,128,128,3,";
    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(editPart,Conv2D)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;
    id = gm.addPart(PartType::Conv2D);
    gm.editPart(id,"filters","64");
    gm.editPart(id,"padding","'same'");
    gm.editPart(id,"kernel_size","(2,2)");
    gm.editPart(id,"strides","(2,2)");


    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";
    oracle["filters"] = "64";
    oracle["kernel_size"] = "(2,2)";
    oracle["strides"] = "(2,2)";
    oracle["padding"] = "'same'";
    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(editPart,MaxPooling2D)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;
    id = gm.addPart(PartType::MaxPooling2D);
    gm.editPart(id,"padding","'same'");
    gm.editPart(id,"pool_size","(2,2)");
    gm.editPart(id,"strides","(2,2)");


    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";
    oracle["pool_size"] = "(2,2)";
    oracle["strides"] = "(2,2)";
    oracle["padding"] = "'same'";
    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(editPart,Dense)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;
    id = gm.addPart(PartType::Dense);
    gm.editPart(id,"units","32");

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "None,32,";
    oracle["units"] = "32";
    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}


TEST(editPart,Dropout)
{
    GraphModel gm(Backend::Keras);
    map<string,string> oracle;
    int id;
    id = gm.addPart(PartType::Dropout);
    gm.editPart(id,"rate","0.3");
    oracle["rate"] = "0.3";
    compare_map(oracle,gm.getPartInfo(id));
    oracle.clear();
}

TEST(addConnection,Conv2D)
{
    GraphModel gm(Backend::Keras);
    int id1,id2;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::Conv2D);
    gm.addConnection(id1,id2,1,0);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,256,256,3,";
    oracle["shape_output_port_0"] = "None,254,254,32,";

    compare_map(oracle,gm.getPartInfo(id2));
    oracle.clear();
}

TEST(addConnection,MaxPooling2D)
{
    GraphModel gm(Backend::Keras);
    int id1,id2;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::MaxPooling2D);
    gm.addConnection(id1,id2,1,0);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,256,256,3,";
    oracle["shape_output_port_0"] = "None,128,128,3,";

    compare_map(oracle,gm.getPartInfo(id2));
    oracle.clear();
}

TEST(addConnection,Activation)
{
    GraphModel gm(Backend::Keras);
    int id1,id2;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::Activation);
    gm.addConnection(id1,id2,1,0);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,256,256,3,";
    oracle["shape_output_port_0"] = "None,256,256,3,";

    compare_map(oracle,gm.getPartInfo(id2));
    oracle.clear();
}


TEST(addConnection,Dropout)
{
    GraphModel gm(Backend::Keras);
    int id1,id2;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::Dropout);
    gm.addConnection(id1,id2,1,0);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,256,256,3,";
    oracle["shape_output_port_0"] = "None,256,256,3,";

    compare_map(oracle,gm.getPartInfo(id2));
    oracle.clear();
}

TEST(addConnection,Flatten)
{
    GraphModel gm(Backend::Keras);
    int id1,id2;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::Flatten);
    gm.addConnection(id1,id2,1,0);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,256,256,3,";
    oracle["shape_output_port_0"] = "None,196608,";

    compare_map(oracle,gm.getPartInfo(id2));
    oracle.clear();
}

TEST(addConnection,Dense)
{
    GraphModel gm(Backend::Keras);
    int id1,id2,id3;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::Flatten);
    id3 = gm.addPart(PartType::Dense);
    gm.addConnection(id1,id2,1,0);
    gm.addConnection(id2,id3,1,0);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,196608,";
    oracle["shape_output_port_0"] = "None,64,";

    compare_map(oracle,gm.getPartInfo(id3));
    oracle.clear();
}

TEST(deleteConnection,Flatten)
{
    GraphModel gm(Backend::Keras);
    int id1,id2,idc;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::Flatten);
    idc = gm.addConnection(id1,id2,1,0);
    gm.deleteConnection(idc);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

   compare_map(oracle,gm.getPartInfo(id2));
   oracle.clear();
}


TEST(deleteConnection,Conv2D)
{
    GraphModel gm(Backend::Keras);
    int id1,id2,idc;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::Conv2D);
    idc = gm.addConnection(id1,id2,1,0);
    gm.deleteConnection(idc);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

   compare_map(oracle,gm.getPartInfo(id2));
   oracle.clear();
}

TEST(deletePart,Flatten)
{
    GraphModel gm(Backend::Keras);
    int id1,id2,idc;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::Flatten);
    idc = gm.addConnection(id1,id2,1,0);
    gm.deletePart(id1);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

   compare_map(oracle,gm.getPartInfo(id2));
   oracle.clear();
}

TEST(deletePart,Conv2D)
{
    GraphModel gm(Backend::Keras);
    int id1,id2,idc;
    map<string,string> oracle;

    id1 = gm.addPart(PartType::InputLayer);
    id2 = gm.addPart(PartType::Conv2D);
    idc = gm.addConnection(id1,id2,1,0);
    gm.deletePart(id1);

    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

   compare_map(oracle,gm.getPartInfo(id2));
   oracle.clear();
}



void compare_map(map<string,string> m1, map<string,string> m2)
{
    map<string, string>::iterator iter_m1;
    for(map<string, string>::iterator iter=m2.begin(); iter!=m2.end(); iter++){
        iter_m1 = m1.find(iter->first);
        if (iter_m1 != m1.end())
        {
            //std::cout<<"here"<<endl;
            EXPECT_TRUE(iter_m1->second==iter->second) << "Differ at  " <<m2["name"]<<": "<< '<'+iter->first+','+iter->second+'>';
        }
     }
}


#endif // TST_CASE_H
