//
// Created by menegais1 on 18/06/2020.
//

#include "Canvas/gl_canvas2d.h"
#include "BaseFunctionsPanel.h"
#include "Panel/Panel.h"

void BaseFunctionsPanel::mouse(int button, int state, int wheel, int direction, int x, int y) {
    bool pointInside = pointIntersectsObject(Float3(x,y,0));
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

BaseFunctionsPanel::BaseFunctionsPanel(Float3 position, Float3 scale, Float4 backgroundColor,
                                       std::vector<CanvasObject *> &children) : Panel(position, scale, backgroundColor,
                                                                                      children) {

}

void BaseFunctionsPanel::render() {
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(0, 0, 0, 1);
    rect(position.x, position.y, position.x + scale.x, position.y + scale.y);
}

bool BaseFunctionsPanel::pointIntersectsObject(Float3 point) {
    bool inside = false;
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->pointIntersectsObject(point)) {
            inside = true;
        }
    }
    return Panel::pointIntersectsObject(point) || inside;
}
