//
// Created by menegais1 on 02/05/2020.
//

#ifndef DISCRETECOSINETRANSFORMATION_GRAPH_H
#define DISCRETECOSINETRANSFORMATION_GRAPH_H


#include "../Vectors/Float2.h"
#include <vector>
#include <functional>
#include "../Button/Button.h"
#include "../Panel/Panel.h"

class Graph : public Panel {
public:
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    bool pointIntersectsObject(Float3 point) override;

    Graph(Float3 position, Float3 scale, Float4 backgroundColor,
          std::vector<Float2> values);

private:
    Float2 maxValue;
    std::vector<Float2> values;
    bool mouseDragging;
    bool mouseInside;
    Float2 currentMousePosition;
    Float2 lastMousePosition;
    Button *closeButton;

    Float2 normalize(Float2 value);
};


#endif //BEZIERCURVES_BLENDINGFUNCTIONSGRAPH_H
