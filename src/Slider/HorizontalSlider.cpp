
#include "HorizontalSlider.h"
#include "../Vectors/Float3.h"
#include "../Canvas/gl_canvas2d.h"
#include "../Utilities.h"
#include <iostream>

void HorizontalSlider::mouse(int button, int state, int wheel, int direction, int x, int y) {
    bool pointInside = isMouseInsideObject();
    if (leftMouseDown(button, state) && pointInside) {
        mouseDragging = true;
    } else if (leftMouseUp(button, state)) {
        mouseDragging = false;
    }

    if (mouseDragging) {
        currentMousePosition = Float2(x, y);
        if (x > position.x + scale.x)
            currentMousePosition.x = position.x + scale.x;
        if (y > position.y + scale.y)
            currentMousePosition.y = position.y + scale.y;
        if (x < position.x)
            currentMousePosition.x = position.x;
        if (y < position.y)
            currentMousePosition.y = position.y;

        float t = getCurrentValueT(currentMousePosition);
        float value = lerp(minValue, maxValue, t);
        if (value != currentValue && t >= 0 && t <= 1) {
            currentValue = value;
            currentMousePosition = Float2(lerp(position.x, position.x + scale.x, t), y);
            notifyOnValueChangedListeners();
        } else {
            currentMousePosition = lastMousePosition;
        }

        lastMousePosition = currentMousePosition;
    }

}

void HorizontalSlider::render() {
    color(lineColor);
    rect(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(backgroundColor);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(handleColor);
    circleFill(currentMousePosition.x, position.y + scale.y / 2, scale.y / 2, 30);
}


void HorizontalSlider::addOnValueChangedListener(std::function<void(float value)> listener) {
    this->onValueChangedListeners.push_back(listener);
}

void HorizontalSlider::notifyOnValueChangedListeners() {
    for (int i = 0; i < onValueChangedListeners.size(); i++) {
        this->onValueChangedListeners[i](currentValue);
    }
}

HorizontalSlider::HorizontalSlider(Float3 position, Float3 scale, Float4 backgroundColor, Float4 handleColor)
        : CanvasObject() {
    this->position = position;
    this->scale = scale;
    this->backgroundColor = backgroundColor;
    this->handleColor = handleColor;
    this->lineColor = backgroundColor;
    this->mouseDragging = false;
    this->currentMousePosition = {position.x, position.y};
}

bool HorizontalSlider::pointIntersectsObject(Float3 point) {
    return isPointInsideBounds({point.x, point.y}, {position.x, position.y}, {scale.x, scale.y}) ||
           isPointInsideCircle(point, Float2(currentMousePosition.x, position.y + scale.y / 2), scale.y / 2);
}

void HorizontalSlider::translate(Float3 translationAmount) {
    CanvasObject::translate(translationAmount);
    currentMousePosition = currentMousePosition + Float2(translationAmount.x, translationAmount.y);
}

float HorizontalSlider::getCurrentValueT(Float2 mousePosition) {
    float x = mousePosition.x - position.x;
    float screenSteps = scale.x / steps;
    float t = x / screenSteps / steps;

    float tIncrement = 1 / steps;
    for (int i = 0; i <= steps; i++) {
        float value = i * tIncrement;
        if (value >= t) {
            t = round(value - tIncrement, value, t);
            break;
        }
    }
    return t;
}
