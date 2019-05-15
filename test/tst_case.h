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

TEST(case, set)
{
    EXPECT_EQ(0, 0);
    ASSERT_THAT(0, Eq(0));
}

TEST(test_model_gen, set)
{

    GraphModel gm(Keras);
    Part *pa;
    Connection *cn;
    int s1, s2;

    // pa = new Part(PartType::InputLayer);
    // pa->AddOutputPort("256,256,3");
    // gm.add(pa);
    // s1 = pa->id;

    gm.addPart(PartType::InputLayer);

    map<string,string> oracle;
    oracle["id"] = "0";
    oracle["input_shape"] = "(256,256,3)";
    oracle["name"] = "'InputLayer'";
    oracle["num_input_port"] = "0";
    oracle["num_output_port"] = "1";
    oracle["shape_output_port_0"] = "None,256,256,3,";

    map<string,string> m1,m2;
    compare_map(oracle,gm.getPartInfo(0));
}

void compare_map(map<string,string> m1, map<string,string> m2)
{
    for(map<string, string>::iterator iter=m1.begin(); iter!=m2.end(); iter++){
        EXPECT_TRUE(m2[iter->first]==iter->second) << "Differ at  " << '<'+iter->first+','+iter->second+'>';
    }
}


#endif // TST_CASE_H
