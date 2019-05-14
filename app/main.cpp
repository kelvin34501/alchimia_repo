#include "mainwindow.h"
#include <QApplication>

#include <project/project_object.h>
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>

void set_basic_model(GraphModel &gm){
    gm.addPart(PartType::InputLayer);
    gm.addPart(PartType::MaxPooling2D);
    gm.addConnection(0, 1, 1, 0);
    gm.addPart(PartType::Activation);
    gm.addConnection(2, 1, 0, 1);
    gm.deleteConnection(1);
    gm.deletePart(1);
    gm.addConnection(0, 2, 1, 0);
    gm.editPart(0, "input_shape", "(128,128,8)");
}

void test_model_gen(){
    GraphModel gm(Keras);
    set_basic_model(gm);
    ofstream outfile("model_gen.gen");
    CompileCFG cfg;
    cfg.archi_path = "./model.json";
    if(!outfile.is_open()){
        cout << "error saving files" << endl;
    }
    else{
        outfile << gm.getPythonFileModel(cfg);
    }
    outfile.close();

    ofstream serial("model.project");
    cereal::JSONOutputArchive ar(serial);
    ar(cereal::make_nvp("name",string("your name here.")),
       cereal::make_nvp("model",gm));
    serial.close();
}


int main(int argc, char *argv[])
{
    test_model_gen();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
