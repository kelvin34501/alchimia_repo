#include "modelcontrol_d.h"

using namespace std;

void set_basic_model(GraphModel &gm);

int main(){
    GraphModel gm(Backend::Keras);
    set_basic_model(gm);

    cout << "model set"; getchar();

    WindowsPython win_py;
    win_py.setPythonPath("D:\\Anaconda3\\python.exe");
    
    cout << "python set"; getchar();

    ModelControl model_ctr(&win_py, &gm);

    TrainCFG train_cfg;
    train_cfg.save_weight_path = "D:/my_cnn/";
    train_cfg.model_name = "test_model";
    train_cfg.metrics.push_back("accuracy");
    
    ModelCFG model_cfg;
    model_cfg.archi_path = "D:/my_cnn/architecture/architecture.json";
    model_ctr.setModelPath(model_cfg);

    DataCFG data_cfg;
    data_cfg.dataset = "cifar10";
    model_ctr.setDataConfiguration(data_cfg);

    cout << "training set"; getchar();

    model_ctr.configureTraining(train_cfg);

    cout << "complete"; getchar();

    return 0;
}

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
