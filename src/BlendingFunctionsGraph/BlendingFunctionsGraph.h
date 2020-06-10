//
// Created by menegais1 on 02/05/2020.
//

#ifndef BEZIERCURVES_BLENDINGFUNCTIONSGRAPH_H
#define BEZIERCURVES_BLENDINGFUNCTIONSGRAPH_H


#include "../Vectors/Float2.h"
#include <vector>
#include <functional>
#include "../Button/Button.h"
#include "../Panel/Panel.h"

class BlendingFunctionsGraph : public Panel {
public:
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    bool pointIntersectsObject(Float3 point) override;

    BlendingFunctionsGraph(Float3 position, Float3 scale, Float3 backgroundColor,
                           std::vector<std::function<float(float)>> blendingFunctions);

private:
    std::vector<std::function<float(float)>> blendingFunctions;
    Float3 backgroundColor;
    bool mouseDragging;
    bool mouseInside;
    Float2 currentMousePosition;
    Float2 lastMousePosition;
    Button *closeButton;
};


#endif //BEZIERCURVES_BLENDINGFUNCTIONSGRAPH_H
