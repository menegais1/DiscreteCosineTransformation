//
// Created by menegais1 on 02/05/2020.
//

#include "../Canvas/gl_canvas2d.h"

#include <utility>
#include <iostream>
#include "BlendingFunctionsGraph.h"


void BlendingFunctionsGraph::mouse(int button, int state, int wheel, int direction, int x, int y) {
    bool pointInside = isMouseInsideObject();
    currentMousePosition = {x, y};
    if (leftMouseDown(button, state) && pointInside) {
        mouseDragging = true;
    } else if (leftMouseUp(button, state)) {
        mouseDragging = false;
    }

    if (mouseDragging) {
        translate(Float3(currentMousePosition - lastMousePosition, 0));
    }
    lastMousePosition = currentMousePosition;
}

void BlendingFunctionsGraph::render() {
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);

    color(1, 1, 1);
    Float2 padding = Float2(20, 20);
    Float2 graphSize = Float2(100, 100);

    line(position.x + padding.x, position.y + padding.y, position.x + padding.x + graphSize.x + 3,
         position.y + padding.y);
    line(position.x + padding.x, position.y + padding.y, position.x + padding.x,
         position.y + padding.y + graphSize.y + 3);
    for (int i = 0; i < blendingFunctions.size(); ++i) {
        bool draw = false;
        Float2 p0;
        Float2 p;
        for (float t = 0; t <= 1.001; t += 0.1) {
            p = Float2(t, blendingFunctions[i](t));
            if (draw) {
                Float2 finalP0 = Float2(position.x + padding.x + p0.x * graphSize.x,
                                        position.y + padding.y + p0.y * graphSize.y);
                Float2 finalP = Float2(position.x + padding.x + p.x * graphSize.x,
                                       position.y + padding.y + p.y * graphSize.y);
                line(finalP0.x, finalP0.y, finalP.x, finalP.y);
            }
            p0 = p;
            draw = true;
        }
    }
}

bool BlendingFunctionsGraph::pointIntersectsObject(Float3 point) {
    return isPointInsideBounds({point.x, point.y}, {position.x, position.y}, {scale.x, scale.y});
}

BlendingFunctionsGraph::BlendingFunctionsGraph(Float3 position, Float3 scale, Float3 backgroundColor,
                                               std::vector<std::function<float(float)>> blendingFunctions)
        : Panel(position, scale, backgroundColor) {
    this->mouseDragging = false;
    this->mouseInside = false;
    this->blendingFunctions = std::move(blendingFunctions);
    closeButton = new Button(position + scale - Float3(scale.x / 3, scale.y - 10, 0),
                             Float3(scale.x / 4, scale.y / 6, 0), Float3(0, 0, 0), "Close", Float3(1, 1, 1));
    closeButton->addListener([this] {
        this->setActive(false);
        this->notifyOnActivateListeners();
    });
    //this->setZIndex(100);
    children.push_back(closeButton);
    this->setActive(false);
}
