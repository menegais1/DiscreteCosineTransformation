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

    Float4 lineColor = {0, 0, 0, 1};
    Float4 labelColor = {0, 0, 0, 1};
    std::string label = "";
private:
    Float2 padding = {40, 40};
    Float2 normalizingValue;
    Float2 maxValue;
    Float2 minValue;
    std::vector<Float2> values;
    bool mouseDragging;
    bool mouseInside;
    Float2 currentMousePosition;
    Float2 lastMousePosition;
    Button *closeButton;

    Float2 normalize(Float2 value);

    void drawLabels();
};


#endif //BEZIERCURVES_BLENDINGFUNCTIONSGRAPH_H
