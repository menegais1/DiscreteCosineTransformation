//
// Created by menegais1 on 02/05/2020.
//

#include "../Canvas/gl_canvas2d.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Graph.h"
#include "../Utilities.h"


void Graph::mouse(int button, int state, int wheel, int direction, int x, int y) {
    if (!draggable) return;
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
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(lineColor.x, lineColor.y, lineColor.z, lineColor.w);
    rect(position.x, position.y, position.x + scale.x, position.y + scale.y);
    line(position.x + padding.x, position.y + padding.y, position.x + padding.x, position.y + scale.y - padding.y);
    line(position.x + padding.x, position.y + padding.y + (scale.y - 2 * padding.y) / 2,
         position.x + scale.x - padding.x + dislocation,
         position.y + padding.y + (scale.y - 2 * padding.y) / 2);


    Float2 init = Float2(position.x + padding.x + dislocation, position.y + padding.y + (scale.y - 2 * padding.y) / 2);
    Float2 displaceAmount = Float2(scale.x - padding.x * 2, (scale.y - 2 * padding.y) / 2);

    if (type == GraphType::Line) {
        for (int i = 0; i < values.size() - 1; ++i) {
            Float2 p0 = normalize(values[i]);
            Float2 p1 = normalize(values[i + 1]);
            line(p0.x * displaceAmount.x + init.x, p0.y * displaceAmount.y + init.y, p1.x * displaceAmount.x + init.x,
                 p1.y * displaceAmount.y + init.y);
        }
    }
    if (type == GraphType::Bar) {
        for (int i = 0; i < values.size(); ++i) {
            Float2 p0 = normalize(values[i]);
            line(p0.x * displaceAmount.x + init.x, init.y, p0.x * displaceAmount.x + init.x,
                 p0.y * displaceAmount.y + init.y);
        }
    }

    drawLabels();

}

void Graph::drawLabels() {
    labelStream.str(std::string());
    Float2 init = Float2(position.x + padding.x, position.y + padding.y + (scale.y - 2 * padding.y) / 2);
    Float2 displaceAmount = Float2((scale.x - padding.x) / 2, (scale.y - 2 * padding.y) / 2);
    color(labelColor.x, labelColor.y, labelColor.z, labelColor.w);
    labelStream << minValue.y;
    Float2 point = normalize(minValue);
    text(position.x, point.y * displaceAmount.y + init.y, labelStream.str().c_str());
    labelStream.str(std::string());
    labelStream << maxValue.y;
    point = normalize(maxValue);
    text(position.x, point.y * displaceAmount.y + init.y, labelStream.str().c_str());
    labelStream.str(std::string());
    labelStream << 0.0;
    text(position.x, position.y + padding.y + (scale.y - 2 * padding.y) / 2, labelStream.str().c_str());
    labelStream.str(std::string());
    labelStream << this->label;
    text(position.x, position.y + scale.y - padding.y / 2, labelStream.str().c_str());
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
    setValues(values);
    labelStream << std::fixed;
    labelStream.precision(2);
}

void Graph::setValues(std::vector<Float2> values) {
    this->values = std::move(values);
    std::sort(this->values.begin(), this->values.end(), [](Float2 f, Float2 s) -> bool {
        return f.x < s.x;
    });
    this->normalizingValue = getMaximumAbsValue(this->values);
    this->maxValue = getMaximumValue(this->values);
    this->minValue = getMinimumValue(this->values);
}
