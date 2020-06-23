//Class responsible for listening to all mouse and keyboard input,
//dealing with current program state and redirecting functions using the curveListManager
//Basically it's the main file of the program

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../Base/CanvasObject.h"
#include "../BaseFunctionsPanel.h"
#include "../Vectors/Float3.h"
#include "../Vectors/Float4.h"

enum Operator {
    InsertPolygon = 13,
    SendToBack = 200,
    SendToFront = 202,
    MultipleSelect = 214,
    FixX = 'x',
    FixY = 'y',
    ConvexHull = 'b',
    ControlGraph = 'g',
    DrawAnimation = 'h',
    ShowControlPoints = 'c',
    ShowBlendingFunctions = 'q',
    DeleteSelected = 127,
};

enum SceneMode {
    Insert = 'i',
    Translate = 't',
    Scale = 's',
    Rotate = 'r',
    Default = 0
};

class Scene : public CanvasObject {
public:

    Graph *inputGraph;
    Graph *dctGraph;
    Graph *idctGraph;
    Graph *diffGraph;
    std::vector<float> curValues;
    HorizontalSlider* sampleNumberSlider;
    HorizontalSlider* quantizationSlider;
    std::vector<CanvasObject *> discreteBaseFunctions;
    std::vector<CanvasObject *> continuosBaseFunctions;
    BaseFunctionsPanel *discreteBaseFunctionsPanel;
    BaseFunctionsPanel *continuousBaseFunctionsPanel;
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void keyboardUp(int key) override;

    void keyboard(int key) override;

    void render() override;

    bool pointIntersectsObject(Float3 point) override;

    Scene();

    void instantiateBaseFunctionsGraphs(int valuesCount);

    void instantiateSampleButtons();

    void instantiateQuantizationSlider();

    void updateDctValues(float quantizationValue);

    void deleteBaseFunctionsPanel();
};

#endif
