#include <vector>
#include <functional>
#include <iostream>

#include "Button.h"
#include "../Base/CanvasObject.h"
#include "../Utilities.h"
#include "../Canvas/gl_canvas2d.h"
#include "../Vectors/Float3.h"

using namespace std;

Button::Button(Float3 position, Float3 scale, Float3 backgroundColor, string title, Float3 textColor) :
        backgroundColor(backgroundColor), title(title), textColor(textColor) {
    this->position = position;
    this->scale = scale;
}

void Button::mouse(int button, int state, int wheel, int direction, int x, int y) {
    if (leftMouseDown(button, state)) {
        if (isMouseInsideObject()) {
            notifyOnClickListeners();
        }
    }
}

void Button::render() {
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(textColor.x, textColor.y, textColor.z);
    text(position.x + 10, position.y + scale.y / 2, title.c_str());
}

void Button::notifyOnClickListeners() {
    for (int i = 0; i < onClickListeners.size(); i++) {
        onClickListeners[i]();
    }
}

void Button::addListener(std::function<void()> listener) {
    onClickListeners.push_back(listener);
}

bool Button::pointIntersectsObject(Float3 point) {
    return isPointInsideBounds({point.x, point.y}, {position.x, position.y}, {scale.x, scale.y});
}

void Button::translate(Float3 translationAmount) {
    this->position = this->position + translationAmount;
}
