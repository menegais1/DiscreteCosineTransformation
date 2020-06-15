//
// Created by menegais1 on 02/05/2020.
//

#include "../Canvas/gl_canvas2d.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
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


    drawLabels();
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(lineColor.x, lineColor.y, lineColor.z, lineColor.w);
    rect(position.x, position.y, position.x + scale.x, position.y + scale.y);
    line(position.x + padding.x, position.y + padding.y, position.x + padding.x, position.y + scale.y - padding.y);
    line(position.x + padding.x, position.y +padding.y + (scale.y - 2 * padding.y) / 2 , position.x + scale.x - padding.x,
         position.y +padding.y + (scale.y - 2 * padding.y) / 2 );


    Float2 init = Float2(position.x + padding.x,position.y +padding.y + (scale.y - 2 * padding.y) / 2 );
    Float2 displaceAmount = Float2((scale.x - padding.x) / 2, (scale.y - 2 * padding.y) / 2);
    for (int i = 0; i < values.size() - 1; ++i) {
        Float2 p0 = normalize(values[i]);
        Float2 p1 = normalize(values[i + 1]);
        line(p0.x * displaceAmount.x + init.x, p0.y * displaceAmount.y + init.y, p1.x * displaceAmount.x + init.x,
             p1.y * displaceAmount.y + init.y);
    }
}

void Graph::drawLabels() {
    color(labelColor.x, labelColor.y, labelColor.z, labelColor.w);
    std::stringstream label;
    label << std::fixed;
    label.precision(3);
    label << minValue.y;
    text(position.x + padding.x, position.y + padding.y, label.str().c_str());
    label.str(std::string());
    label << maxValue.y;
    text(position.x + padding.x, position.y + scale.y - padding.y, label.str().c_str());
    label.str(std::string());
    label << this->label;
    text(position.x + scale.x / 2, position.y + scale.y - padding.y /2, label.str().c_str());
}

bool Graph::pointIntersectsObject(Float3 point) {
    return isPointInsideBounds({point.x, point.y}, {position.x, position.y}, {scale.x, scale.y});
}

Float2 Graph::normalize(Float2 value) {
    float x = value.x / normalizingValue.x;
    float y = value.y / normalizingValue.y;
    if (x < 0) x = x + 1 / 2.f;
    return Float2(x, y);
}

Graph::Graph(Float3 position, Float3 scale, Float4 backgroundColor,
             std::vector<Float2> values) : Panel(position, scale, backgroundColor) {
    this->mouseDragging = false;
    this->mouseInside = false;
    this->values = std::move(values);
    std::sort(this->values.begin(), this->values.end(), [](Float2 f, Float2 s) -> bool {
        return f.x < s.x;
    });
    this->normalizingValue = getMaximumAbsValue(this->values);
    this->maxValue = getMaximumValue(this->values);
    this->minValue = getMinimumValue(this->values);
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