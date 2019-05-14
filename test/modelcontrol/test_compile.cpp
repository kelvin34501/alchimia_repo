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
    CompileCFG compile_cfg = {
        "D:\\Bruce\\Courses\\Software Engineering\\alchimia_repo\\test\\test_model.json"
    };

    cout << "compile set"; getchar();

    model_ctr.configureCompilation(compile_cfg);

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
