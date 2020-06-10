//Class responsible for listening to all mouse and keyboard input,
//dealing with current program state and redirecting functions using the curveListManager
//Basically it's the main file of the program

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Base/CanvasObject.h"
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
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void keyboardUp(int key) override;

    void keyboard(int key) override;

    void render() override;

    bool pointIntersectsObject(Float3 point) override;

    Scene();

};

#endif
