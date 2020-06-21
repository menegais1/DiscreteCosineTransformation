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
#include "BaseFunctionsPanel.h"

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

void instantiateBaseFunctionsGraphs() {

    std::vector<CanvasObject *> discreteBaseFunctions;
    Float3 padding(20, 20, 0);
    Float3 baseFunctionsScale(200, 200, 0);
    Float3 panelPosition(400, 400, 0);
    Float3 panelScale(baseFunctionsScale.x * 2 + padding.x * 2, baseFunctionsScale.y * 4 + padding.y * 2, 0);
    for (int i = 0; i < 8; i++) {
        Graph *g = new Graph(panelPosition + padding +
                             Float3((i % 2) * baseFunctionsScale.x, (i / 2) * baseFunctionsScale.y, 0),
                             baseFunctionsScale, Float4(1, 1, 1, 0.2),
                             DiscreteCosineTransformation::baseFunctions(i, 8, 1));
        std::string label("DCT BASE ");
        g->label = label + std::to_string(i);
        g->type = GraphType::Bar;
        g->draggable = false;
        discreteBaseFunctions.push_back(g);
    }
    BaseFunctionsPanel *discreteBaseFunctionsPanel = new BaseFunctionsPanel(panelPosition, panelScale,
                                                                            Float4(1, 1, 1, 0.2),
                                                                            discreteBaseFunctions);

    discreteBaseFunctionsPanel->setZIndex(10);
    discreteBaseFunctionsPanel->setActive(false);
    std::vector<CanvasObject *> continuosBaseFunctions;
    for (int i = 0; i < 8; i++) {
        Graph *g = new Graph(panelPosition + padding +
                             Float3((i % 2) * baseFunctionsScale.x, (i / 2) * baseFunctionsScale.y, 0),
                             baseFunctionsScale, Float4(1, 1, 1, 0.2),
                             DiscreteCosineTransformation::baseFunctions(i, 8, 0.1));
        std::string label("DCT BASE ");
        g->label = label + std::to_string(i);
        g->type = GraphType::Line;
        g->draggable = false;
        continuosBaseFunctions.push_back(g);

    }

    BaseFunctionsPanel *continuosBaseFunctionsPanel = new BaseFunctionsPanel(panelPosition, panelScale,
                                                                             Float4(1, 1, 1, 0.2),
                                                                             continuosBaseFunctions);

    continuosBaseFunctionsPanel->setZIndex(10);
    continuosBaseFunctionsPanel->setActive(false);

    Button *discreteBaseFunctionsButton = new Button(Float3(40, 40, 40), Float3(160, 40, 40), Float4(0, 0, 0, 0.3),
                                                     "Base Discrete", Float4(1, 1, 1, 1));
    discreteBaseFunctionsButton->addListener([discreteBaseFunctionsPanel]() {
        discreteBaseFunctionsPanel->setActive(!discreteBaseFunctionsPanel->getActive());
    });
    Button *continuosBaseFunctionsButton = new Button(Float3(210, 40, 40), Float3(160, 40, 40), Float4(0, 0, 0, 0.3),
                                                      "Base Continuous", Float4(1, 1, 1, 1));
    continuosBaseFunctionsButton->addListener([continuosBaseFunctionsPanel]() {
        continuosBaseFunctionsPanel->setActive(!continuosBaseFunctionsPanel->getActive());
    });
}

void instantiateQuantizationSlider(Graph *dctValuesGraph, Graph *reconstructedGraph, Graph *diffGraph,
                                   std::vector<float> values) {

    HorizontalSlider *slider = new HorizontalSlider(Float3(380, 60, 0), Float3(100, 10, 0), Float4(0, 0, 0, 0.4),
                                                    Float4(0, 0, 0, 1));
    slider->minValue = 0;
    slider->maxValue = 25;
    slider->steps = 25;
    slider->addOnValueChangedListener([dctValuesGraph, reconstructedGraph, diffGraph, values](float value) -> void {
        auto dctValues = DiscreteCosineTransformation::forwardDCT(values);
        std::cout <<"DCT VALUES"<< std::endl;
        for (int i = 0; i < dctValues.size(); ++i) {
            std::cout << dctValues[i] << std::endl;
        }
        auto quantizedValues = DiscreteCosineTransformation::applyQuantization(
                DiscreteCosineTransformation::forwardDCT(values),
                DiscreteCosineTransformation::generateQuantizationVector(values.size(), value), value);
        std::cout <<"Quantized Values"<< std::endl;
        for (int i = 0; i < quantizedValues.size(); ++i) {
            std::cout << quantizedValues[i] << std::endl;
        }
        auto reconstructedValues = DiscreteCosineTransformation::inverseDCT(quantizedValues);
        dctValuesGraph->setValues(DiscreteCosineTransformation::convertToValueTuple(quantizedValues));
        reconstructedGraph->setValues(DiscreteCosineTransformation::convertToValueTuple(reconstructedValues));
        diffGraph->setValues(DiscreteCosineTransformation::convertToValueTuple(
                DiscreteCosineTransformation::difference(values, reconstructedValues)));
    });

}

int main(void) {
    initCanvas(GlobalManager::getInstance()->screenWidth, GlobalManager::getInstance()->screenHeight,
               "DiscreteCosineTransformation");

    DiscreteCosineTransformation dct;
    //DataLoader::saveData("input.dct", {8, 16, 24, 32, 40, 48, 56, 64});
    auto data = DataLoader::readData("input.dct");
    std::vector<float> values(data.size());
    std::cout << "" << std::endl;
    for (int i = 0; i < data.size(); ++i) {
        values[i] = data[i];
        std::cout << data[i] << std::endl;
    }

  //  values = {-48, 126, -8, -4, 10, 73, 91, -70};
    Graph *input = new Graph(Float3(40 + 40, 40 + 80, 0), Float3(400, 300, 0), Float4(1, 1, 1, 0.2),
                             dct.convertToValueTuple(values));
    input->label = "Input";
    auto convertedValues = dct.forwardDCT(values);
    Graph *dctValues = new Graph(Float3(40 + 40, 360 + 80, 0), Float3(400, 300, 0), Float4(1, 1, 1, 0.2),
                                 dct.convertToValueTuple(convertedValues));
    dctValues->label = "DCT";

    auto inverseDCT = dct.inverseDCT(convertedValues);
    Graph *reconstructed = new Graph(Float3(460 + 40, 360 + 80, 0), Float3(400, 300, 0), Float4(1, 1, 1, 0.2),
                                     dct.convertToValueTuple(inverseDCT));
    reconstructed->label = "IDCT";


    auto diff = dct.difference(values, inverseDCT);
    Graph *diffGraph = new Graph(Float3(460 + 40, 40 + 80, 0), Float3(400, 300, 0), Float4(1, 1, 1, 0.2),
                                 dct.convertToValueTuple(diff));
    diffGraph->label = "DIFF";

    instantiateBaseFunctionsGraphs();
    instantiateQuantizationSlider(dctValues, reconstructed, diffGraph, values);

    Scene *scene = new Scene();
    runCanvas();
}
