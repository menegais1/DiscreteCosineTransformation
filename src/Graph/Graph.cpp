//
// Created by menegais1 on 02/05/2020.
//

#include "../Canvas/gl_canvas2d.h"

#include <iostream>
#include "Graph.h"


void Graph::mouse(int button, int state, int wheel, int direction, int x, int y) {
    bool pointInside = isMouseInsideObject();
    currentMousePosition = Float2(x, y);
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

void Graph::render() {
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);

}

bool Graph::pointIntersectsObject(Float3 point) {
    return isPointInsideBounds({point.x, point.y}, {position.x, position.y}, {scale.x, scale.y});
}

Graph::Graph(Float3 position, Float3 scale, Float3 backgroundColor,
             std::vector<Float2> values) {
    this->mouseDragging = false;
    this->mouseInside = false;
    this->values = std::move(values);

//    closeButton = new Button(position + scale - Float3(scale.x / 3, scale.y - 10, 0),
//                             Float3(scale.x / 4, scale.y / 6, 0), Float3(0, 0, 0), "Close", Float3(1, 1, 1));
//    closeButton->addListener([this] {
//        this->setActive(false);
//        this->notifyOnActivateListeners();
//    });
//    //this->setZIndex(100);
//    children.push_back(closeButton);
//    this->setActive(false);
}