#include <iostream>
#include "../app/graphmodel/graphmodel.h"
#include "../app/converter/converter.h"
#include "../test/modelcontrol/modelcontrol_d.h"

using namespace std;

void set_basic_model(GraphModel &gm);
void test_train();

int main(int argc, char *argv[])
{
    test_train();
    return 0;
}

void test_train(){
    GraphModel gm(Backend::Keras);
    set_basic_model(gm);
    // return;
    cout << "model set"; getchar();

    QTPython qt_py;
    qt_py.setPythonPath("D:/Anaconda3/python.exe");

    cout << "python set"; getchar();

    ModelControl model_ctr(&qt_py, &gm);

//    CompileCFG compile_cfg = {
//        "test_model",
//        "D:/my_cnn/test_model.json"
//    };

//    cout << "compile set"; getchar();

//    model_ctr.configureCompilation(compile_cfg);

//    cout << "compile complete"; getchar();

    TrainCFG train_cfg;
    train_cfg.save_weight_dir = "D:/my_cnn/";
    train_cfg.model_name = "test_model";
    train_cfg.metrics.push_back("accuracy");
    train_cfg.tb_cfg.log_dir = "D:/my_cnn/logs";

    ModelCFG model_cfg;
    model_cfg.archi_path = "D:/my_cnn/test_model.json";
    model_ctr.setModelPath(model_cfg);

    DataCFG data_cfg;
    data_cfg.dataset = "cifar10";
    model_ctr.setDataConfiguration(data_cfg);

    cout << "training set"; getchar();

    model_ctr.configureTraining(train_cfg);

    cout << "train complete"; getchar();
}

void set_basic_model(GraphModel &gm){
    int idx;

    idx = gm.addPart(PartType::InputLayer);

    idx = gm.addPart(PartType::Conv2D);
    gm.editPart(idx, "padding", "'same'");
    gm.editPart(idx, "filters", "8");
    idx = gm.addPart(PartType::Activation);
    gm.editPart(idx, "activation", "'sigmoid'");
    idx = gm.addPart(PartType::MaxPooling2D);
    gm.editPart(idx, "padding", "'same'");

    idx = gm.addPart(PartType::Conv2D);
    gm.editPart(idx, "padding", "'same'");
    gm.editPart(idx, "filters", "16");
    idx = gm.addPart(PartType::Activation);
    gm.editPart(idx, "activation", "'sigmoid'");
    idx = gm.addPart(PartType::MaxPooling2D);
    gm.editPart(idx, "padding", "'same'");

    gm.addPart(PartType::Flatten);
    idx = gm.addPart(PartType::Dense);
    gm.editPart(idx, "units", "10");
    idx = gm.addPart(PartType::Activation);

    gm.addConnection(0, 1, 1, 0);
    gm.addConnection(1, 2, 1, 0);
    gm.addConnection(2, 3, 1, 0);
    gm.addConnection(3, 4, 1, 0);
    gm.addConnection(4, 5, 1, 0);
    gm.addConnection(5, 6, 1, 0);
    gm.addConnection(6, 7, 1, 0);
    gm.addConnection(7, 8, 1, 0);
    gm.addConnection(8, 9, 1, 0);
    gm.editPart(0, "input_shape", "(32,32,3)");
}
