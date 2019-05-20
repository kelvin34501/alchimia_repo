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

TEST(addPart, set)
{

    GraphModel gm(Backend::Keras);
    Part *pa;
    Connection *cn;

    // pa = new Part(PartType::InputLayer);
    // pa->AddOutputPort("256,256,3");
    // gm.add(pa);
    // s1 = pa->id;

    gm.addPart(PartType::InputLayer);

    map<string,string> oracle;
    oracle["input_shape"] = "(256,256,3)";
    oracle["num_input_port"] = "0";
    oracle["num_output_port"] = "1";
    oracle["shape_output_port_0"] = "None,256,256,3,";

    compare_map(oracle,gm.getPartInfo(0));
    oracle.clear();

    gm.addPart(PartType::Dense);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "None,64,";
    //Confirm it later.

    compare_map(oracle,gm.getPartInfo(1));
    oracle.clear();

    gm.addPart(PartType::Conv2D);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(2));
    oracle.clear();

    gm.addPart(PartType::MaxPooling2D);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(3));
    oracle.clear();

    gm.addPart(PartType::Activation);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(4));
    oracle.clear();

    gm.addPart(PartType::Dropout);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(5));
    oracle.clear();

    gm.addPart(PartType::Flatten);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(6));
    oracle.clear();

    gm.addPart(PartType::Reshape);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";

    compare_map(oracle,gm.getPartInfo(7));
    oracle.clear();
}

TEST(addConnection,set)
{
    GraphModel gm(Backend::Keras);
    Part *pa;
    Connection *cn;
    map<string,string> oracle;

    gm.addPart(PartType::InputLayer);
    gm.addPart(PartType::Conv2D);
    gm.addPart(PartType::Activation);
    gm.addPart(PartType::Dropout);
    gm.addPart(PartType::Flatten);
    gm.addPart(PartType::Reshape);
    gm.addPart(PartType::Dense);
    //Tested except Dense

    gm.addConnection(0,1,1,0);
    oracle["num_input_port"] = "0";
    oracle["num_output_port"] = "1";
    //oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "None,256,256,3,";

    compare_map(oracle,gm.getPartInfo(0));
    oracle.clear();

    gm.addConnection(1,2,1,0);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,256,256,3,";
    oracle["shape_output_port_0"] = "None,254,254,32,";

    compare_map(oracle,gm.getPartInfo(1));
    oracle.clear();

    gm.addConnection(2,3,1,0);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,254,254,32,";
    oracle["shape_output_port_0"] = "None,254,254,32,";

    compare_map(oracle,gm.getPartInfo(2));
    oracle.clear();

    gm.addConnection(4,3,0,1);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,254,254,32,";
    oracle["shape_output_port_0"] = "None,254,254,32,";

    compare_map(oracle,gm.getPartInfo(3));
    oracle.clear();

    gm.addConnection(4,5,1,0);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,254,254,32,";
    oracle["shape_output_port_0"] = "None,2064512,";

    compare_map(oracle,gm.getPartInfo(4));
    oracle.clear();

//    gm.addConnection(3,5,1,0);
//    oracle["num_input_port"] = "1";
//    oracle["num_output_port"] = "1";
//    oracle["shape_input_port_0"] = "None,254,254,32,";
//    oracle["shape_output_port_0"] = "None,2064512,";

//    compare_map(oracle,gm.getPartInfo(5));
//    oracle.clear();

//    gm.addConnection(0,6,1,0);
//    oracle["num_input_port"] = "1";
//    oracle["num_output_port"] = "1";
//    oracle["shape_input_port_0"] = "None,256,256,3,";
//    oracle["shape_output_port_0"] = "None,64,";

//    compare_map(oracle,gm.getPartInfo(6));
//    oracle.clear();
}

TEST(editPart,set)
{
    GraphModel gm(Backend::Keras);
    Part *pa;
    Connection *cn;
    map<string,string> oracle;

    gm.addPart(PartType::InputLayer);
    gm.addPart(PartType::Conv2D);
    gm.addPart(PartType::Activation);
    gm.addPart(PartType::Dropout);
    gm.addPart(PartType::Reshape);
    gm.addPart(PartType::Dense);

//    gm.editPart(0,"input_shape","(128,128,3)");
//    oracle["num_input_port"] = "0";
//    oracle["num_output_port"] = "1";
//    oracle["shape_output_port_0"] = "None,128,128,3,";
//    compare_map(oracle,gm.getPartInfo(0));
//    oracle.clear();

    gm.editPart(1,"filters","64");
    gm.editPart(1,"kernel_size","(2,2)");
    gm.editPart(1,"strides","(2,2)");


    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "";
    oracle["filters"] = "64";
    oracle["kernel_size"] = "(2,2)";
    oracle["strides"] = "(2,2)";
    compare_map(oracle,gm.getPartInfo(1));
    oracle.clear();

    gm.editPart(3,"rate","0.3");
    oracle["rate"] = "0.3";
    compare_map(oracle,gm.getPartInfo(3));
    oracle.clear();

    gm.editPart(4,"target_shape","(2,-1)");
    oracle["target_shape"] = "(2,-1)";
    compare_map(oracle,gm.getPartInfo(4));
    oracle.clear();

    gm.addConnection(0,1,1,0);
    oracle["num_input_port"] = "0";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "";
    oracle["shape_output_port_0"] = "None,256,256,3,";

    compare_map(oracle,gm.getPartInfo(0));
    oracle.clear();

    gm.addConnection(1,2,1,0);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,256,256,3,";
    oracle["shape_output_port_0"] = "None,255,255,64,";

    compare_map(oracle,gm.getPartInfo(1));
    oracle.clear();

    gm.addConnection(2,3,1,0);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,255,255,64,";
    oracle["shape_output_port_0"] = "None,255,255,64,";

    compare_map(oracle,gm.getPartInfo(2));
    oracle.clear();

    gm.addConnection(4,3,0,1);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,255,255,64,";
    oracle["shape_output_port_0"] = "None,255,255,64,";

    compare_map(oracle,gm.getPartInfo(3));
    oracle.clear();

    gm.addConnection(4,5,1,0);
    oracle["num_input_port"] = "1";
    oracle["num_output_port"] = "1";
    oracle["shape_input_port_0"] = "None,255,255,64,";
    oracle["shape_output_port_0"] = "None,2,2080800,";

    compare_map(oracle,gm.getPartInfo(4));
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
