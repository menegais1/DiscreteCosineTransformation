
#include "../Button/Button.h"
#include "../DataLoader.h"
#include "../DiscreteCosineTransformation.h"
#include "../Slider/HorizontalSlider.h"
#include "../Graph/Graph.h"
#include "../BaseFunctionsPanel.h"
#include "../Managers/GlobalManager.h"
#include "Scene.h"

#include <cmath>
#include <iostream>

void Scene::mouse(int button, int state, int wheel, int direction, int x, int y) {
    CanvasObject::mouse(button, state, wheel, direction, x, y);
}

void Scene::keyboardUp(int key) {
    CanvasObject::keyboardUp(key);
}

void Scene::keyboard(int key) {
    CanvasObject::keyboard(key);
}

void Scene::render() {
    CanvasObject::render();
}

bool Scene::pointIntersectsObject(Float3 point) {
    return false;
}


void Scene::deleteBaseFunctionsPanel() {
    GlobalManager::getInstance()->deleteObject(
            discreteBaseFunctionsPanel);
    GlobalManager::getInstance()->deleteObject(
            continuousBaseFunctionsPanel);
    for (int i = 0; i < discreteBaseFunctions.size(); ++i) {
        GlobalManager::getInstance()->deleteObject(discreteBaseFunctions[i]);
    }
    for (int i = 0; i < continuosBaseFunctions.size(); ++i) {
        GlobalManager::getInstance()->deleteObject(continuosBaseFunctions[i]);
    }
    discreteBaseFunctions.clear();
    continuosBaseFunctions.clear();
}

void Scene::instantiateBaseFunctionsGraphs(int valuesCount) {
    Float3 padding(5, 5, 0);
    Float3 baseFunctionsScale(175, 125, 0);
    Float3 panelPosition(0, 80, 0);
    int colNumber = ceil(sqrt(valuesCount));
    Float3 panelScale(baseFunctionsScale.x * colNumber + padding.x * 2,
                      baseFunctionsScale.y * colNumber + padding.y * 2, 0);
    for (int i = 0; i < valuesCount; i++) {
        Graph *g = new Graph(panelPosition + padding +
                             Float3((i % colNumber) * baseFunctionsScale.x, (i / colNumber) * baseFunctionsScale.y, 0),
                             baseFunctionsScale, Float4(1, 1, 1, 1),
                             DiscreteCosineTransformation::baseFunctions(i, valuesCount, 1));
        std::string label("DCT BASE ");
        g->label = label + std::to_string(i);
        g->type = GraphType::Bar;
        g->draggable = false;
        g->padding = Float2(10, 30);
        g->labelColor = Float4(0.8, 0, 0, 1);
        discreteBaseFunctions.push_back(g);
    }
    discreteBaseFunctionsPanel = new BaseFunctionsPanel(panelPosition, panelScale,
                                                        Float4(0, 0, 0, 0.7),
                                                        discreteBaseFunctions);

    discreteBaseFunctionsPanel->setZIndex(10);
    discreteBaseFunctionsPanel->setActive(false);
    for (int i = 0; i < valuesCount; i++) {
        Graph *g = new Graph(panelPosition + padding +
                             Float3((i % colNumber) * baseFunctionsScale.x, (i / colNumber) * baseFunctionsScale.y, 0),
                             baseFunctionsScale, Float4(1, 1, 1, 1),
                             DiscreteCosineTransformation::baseFunctions(i, valuesCount, 0.1));
        std::string label("DCT BASE ");
        g->label = label + std::to_string(i);
        g->type = GraphType::Line;
        g->draggable = false;
        g->padding = Float2(10, 30);
        g->labelColor = Float4(0.8, 0, 0, 1);
        continuosBaseFunctions.push_back(g);

    }

    continuousBaseFunctionsPanel = new BaseFunctionsPanel(panelPosition, panelScale,
                                                          Float4(0, 0, 0, 0.7),
                                                          continuosBaseFunctions);

    continuousBaseFunctionsPanel->setZIndex(10);
    continuousBaseFunctionsPanel->setActive(false);
}

void Scene::updateDctValues(float quantizationValue = 0) {
    inputGraph->setValues(DiscreteCosineTransformation::convertToValueTuple(curValues));
    auto dctValues = DiscreteCosineTransformation::forwardDCT(curValues);
    auto quantizationVector = DiscreteCosineTransformation::generateQuantizationVector(curValues.size(),
                                                                                       quantizationValue);
    auto quantizedValues = DiscreteCosineTransformation::applyQuantization(
            DiscreteCosineTransformation::forwardDCT(curValues), quantizationVector, quantizationValue);
    auto reconstructedValues = DiscreteCosineTransformation::inverseDCT(
            DiscreteCosineTransformation::applyInverseQuantization(quantizedValues, quantizationVector,
                                                                   quantizationValue));
    dctGraph->setValues(DiscreteCosineTransformation::convertToValueTuple(quantizedValues));
    idctGraph->setValues(DiscreteCosineTransformation::convertToValueTuple(reconstructedValues));
    diffGraph->setValues(DiscreteCosineTransformation::convertToValueTuple(
            DiscreteCosineTransformation::difference(curValues, reconstructedValues)));
}

void Scene::instantiateQuantizationSlider() {

    quantizationSlider = new HorizontalSlider(Float3(380, 60, 0), Float3(100, 10, 0), Float4(0, 0, 0, 0.4),
                                              Float4(0, 0, 0, 1));
    quantizationSlider->setValues(0, 100, 100);
    quantizationSlider->addOnValueChangedListener(
            [this](float value) -> void {
                updateDctValues(value);
            });

}

void Scene::instantiateSampleButtons() {

    sampleNumberSlider = new HorizontalSlider(Float3(550 + 165 + 180, 60, 0), Float3(100, 10, 0),
                                              Float4(0, 0, 0, 0.4),
                                              Float4(0, 0, 0, 1));
    sampleNumberSlider->setValues(8, 64, 64 - 8);
    sampleNumberSlider->addOnValueChangedListener([this](float value) {
        auto data = DiscreteCosineTransformation::generateRandomValues(value);
        std::vector<float> values(data.size());
        for (int i = 0; i < data.size(); ++i) {
            values[i] = data[i];
        }
        curValues = values;
        updateDctValues(quantizationSlider->currentValue);
    });
    Button *loadSamplesButton = new Button(Float3(550, 40, 40), Float3(160, 40, 40), Float4(0, 0, 0, 0.3),
                                           "Load Data", Float4(1, 1, 1, 1));
    loadSamplesButton->addListener([this]() {
        auto data = DataLoader::readData("input.dct");
        std::vector<float> values(data.size());
        for (int i = 0; i < data.size(); ++i) {
            values[i] = data[i];
        }
        curValues = values;
        updateDctValues(quantizationSlider->currentValue);
        sampleNumberSlider->setCurValue(curValues.size());
    });

    Button *saveSamplesButton = new Button(Float3(550 + 165, 40, 40), Float3(160, 40, 40), Float4(0, 0, 0, 0.3),
                                           "Save Data", Float4(1, 1, 1, 1));
    saveSamplesButton->addListener([this]() {
        std::vector<int> values(curValues.size());
        for (int i = 0; i < curValues.size(); ++i) {
            values[i] = curValues[i];
        }
        DataLoader::saveData("input.dct", values);
    });


}

Scene::Scene() {
    auto data = DataLoader::readData("input.dct");
    std::vector<float> values(data.size());
    for (int i = 0; i < data.size(); ++i) {
        values[i] = data[i];
    }
    curValues = values;
    inputGraph = new Graph(Float3(40 + 40, 40 + 80, 0), Float3(400, 300, 0), Float4(1, 1, 1, 0.2),
                           DiscreteCosineTransformation::convertToValueTuple(values));
    inputGraph->label = "Input";
    auto convertedValues = DiscreteCosineTransformation::forwardDCT(values);
    dctGraph = new Graph(Float3(40 + 40, 360 + 80, 0), Float3(400, 300, 0), Float4(1, 1, 1, 0.2),
                         DiscreteCosineTransformation::convertToValueTuple(convertedValues));
    dctGraph->label = "DCT";

    auto inverseDCT = DiscreteCosineTransformation::inverseDCT(convertedValues);
    idctGraph = new Graph(Float3(460 + 40, 360 + 80, 0), Float3(400, 300, 0), Float4(1, 1, 1, 0.2),
                          DiscreteCosineTransformation::convertToValueTuple(inverseDCT));
    idctGraph->label = "IDCT";


    auto diff = DiscreteCosineTransformation::difference(values, inverseDCT);
    diffGraph = new Graph(Float3(460 + 40, 40 + 80, 0), Float3(400, 300, 0), Float4(1, 1, 1, 0.2),
                          DiscreteCosineTransformation::convertToValueTuple(diff));
    diffGraph->label = "DIFF";

    instantiateBaseFunctionsGraphs(values.size());
    instantiateQuantizationSlider();
    instantiateSampleButtons();
    discreteBaseFunctionsPanel->setActive(false);
    continuousBaseFunctionsPanel->setActive(false);

    Button *discreteBaseFunctionsButton = new Button(Float3(40, 40, 40), Float3(160, 40, 40), Float4(0, 0, 0, 0.3),
                                                     "Base Discrete", Float4(1, 1, 1, 1));
    discreteBaseFunctionsButton->addListener([this]() {
        if (!discreteBaseFunctionsPanel->getActive()) {
            deleteBaseFunctionsPanel();
            instantiateBaseFunctionsGraphs(curValues.size());
        }
        discreteBaseFunctionsPanel->setActive(!discreteBaseFunctionsPanel->getActive());
    });
    Button *continuosBaseFunctionsButton = new Button(Float3(210, 40, 40), Float3(160, 40, 40), Float4(0, 0, 0, 0.3),
                                                      "Base Continuous", Float4(1, 1, 1, 1));
    continuosBaseFunctionsButton->addListener([this]() {
        if (!continuousBaseFunctionsPanel->getActive()) {
            deleteBaseFunctionsPanel();
            instantiateBaseFunctionsGraphs(curValues.size());
        }
        continuousBaseFunctionsPanel->setActive(!continuousBaseFunctionsPanel->getActive());
    });
}
