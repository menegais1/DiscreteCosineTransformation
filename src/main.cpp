//Roberto Menegais 201810233
/// Main class of the program, used for registering the callbacks
/// in GLUT, initialize the window, call the GlobalManager functions
/// and instantiate the program main manager
//
//Instruções para o uso do programa:
//




#include <iostream>
#include "Slider/HorizontalSlider.h"
#include "Graph/Graph.h"
#include "Canvas/gl_canvas2d.h"
#include "Utilities.h"
#include "Managers/GlobalManager.h"
#include "Scene/Scene.h"
#include "DiscreteCosineTransformation.h"
#include "DataLoader.h"

using namespace std;

void render() {
    GlobalManager::getInstance()->render();
}

void keyboard(int key) {
    GlobalManager::getInstance()->keyboard(key);
}

void keyboardUp(int key) {
    GlobalManager::getInstance()->keyboardUp(key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y) {
    GlobalManager::getInstance()->mouse(button, state, wheel, direction, x, y);
}

int main(void) {
    initCanvas(GlobalManager::getInstance()->screenWidth, GlobalManager::getInstance()->screenHeight,
               "DiscreteCosineTransformation");

    DiscreteCosineTransformation dct;
    DataLoader::saveData("input.dct", {8, 16, 24, 32, 40, 48, 56, 64});
    auto data = DataLoader::readData("input.dct");
    std::cout << "" << std::endl;
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << std::endl;
    }

    std::vector<float> values = {8, 16, 24, 32, 40, 48, 56, 64};
    Graph *input = new Graph(Float3(40, 40, 0), Float3(500, 300, 0), Float4(1, 1, 1, 0.2),
                             dct.convertToValueTuple(values));
    input->label = "Input";
    auto convertedValues = dct.forwardDCT(values);
    Graph *dctValues = new Graph(Float3(400, 400, 0), Float3(500, 300, 0), Float4(1, 1, 1, 0.2),
                                 dct.convertToValueTuple(convertedValues));
    dctValues->label = "DCT";

    auto inverseDCT = dct.inverseDCT(convertedValues);
    Graph *reconstructed = new Graph(Float3(400, 400, 0), Float3(500, 300, 0), Float4(1, 1, 1, 0.2),
                                     dct.convertToValueTuple(inverseDCT));
    reconstructed->label = "IDCT";

    auto diff = dct.difference(values, inverseDCT);
    Graph *diffGraph = new Graph(Float3(400, 400, 0), Float3(500, 300, 0), Float4(1, 1, 1, 0.2),
                                 dct.convertToValueTuple(diff));
    diffGraph->label = "DIFF";


    std::vector<Graph *> discreteBaseFunctions;
    for (int i = 0; i < values.size(); i++) {
        discreteBaseFunctions.push_back(new Graph(Float3(400, 400, 0), Float3(200, 200, 0), Float4(1, 1, 1, 0.2),
                                                  dct.baseFunctions(i, values.size(), 1)));
        std::string label("Discrete Base Function ");
        discreteBaseFunctions[i]->label = label + std::to_string(i);
        discreteBaseFunctions[i]->type = GraphType::Bar;

    }


    HorizontalSlider* slider=  new HorizontalSlider(Float3(200,200,0),Float3(100,10,0),Float4(0, 0, 0, 0.4),Float4(0,0,0,1));
    slider->minValue = 0;
    slider->maxValue = 10;
    slider->steps = 10;
    slider->addOnValueChangedListener([](float value)->void{
        std::cout << value << std::endl;
    });
//    std::cout << "" << std::endl;
//    for (int i = 0; i < convertedValues.size(); ++i) {
//        std::cout << convertedValues[i] << std::endl;
//    }
//    std::cout << "" << std::endl;
//    for (int i = 0; i < inverseDCT.size(); ++i) {
//        std::cout << inverseDCT[i] << std::endl;
//    }
//
//    std::cout << "" << std::endl;
//    for (int i = 0; i < diff.size(); ++i) {
//        std::cout << diff[i] << std::endl;
//    }
    Scene *scene = new Scene();
    runCanvas();
}
