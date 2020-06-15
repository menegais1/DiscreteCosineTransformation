//Roberto Menegais 201810233
/// Main class of the program, used for registering the callbacks
/// in GLUT, initialize the window, call the GlobalManager functions
/// and instantiate the program main manager
//
//Instruções para o uso do programa:
//




#include <iostream>
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
    Graph *input = new Graph(Float3(40, 40, 0), Float3(250, 300, 0), Float4(1, 1, 1, 0.2),
                             dct.convertToValueTuple(values));
    auto convertedValues = dct.forwardDCT(values);
    Graph *dctValues = new Graph(Float3(400, 400, 0), Float3(250, 300, 0), Float4(1, 1, 1, 0.2),
                                 dct.convertToValueTuple(convertedValues));
//    auto inverseDCT = dct.inverseDCT(convertedValues);
//    std::cout << "" << std::endl;
//    for (int i = 0; i < convertedValues.size(); ++i) {
//        std::cout << convertedValues[i] << std::endl;
//    }
//    std::cout << "" << std::endl;
//    for (int i = 0; i < inverseDCT.size(); ++i) {
//        std::cout << inverseDCT[i] << std::endl;
//    }
//
//    auto diff = dct.difference(values, inverseDCT);
//    std::cout << "" << std::endl;
//    for (int i = 0; i < diff.size(); ++i) {
//        std::cout << diff[i] << std::endl;
//    }
    Scene *scene = new Scene();
    runCanvas();
}
