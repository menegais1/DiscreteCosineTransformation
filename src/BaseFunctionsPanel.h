//
// Created by menegais1 on 18/06/2020.
//

#ifndef DISCRETECOSINETRANSFORMATION_BASEFUNCTIONSPANEL_H
#define DISCRETECOSINETRANSFORMATION_BASEFUNCTIONSPANEL_H


#include "Panel/Panel.h"

class BaseFunctionsPanel : public Panel {
public:
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    BaseFunctionsPanel(Float3 position, Float3 scale, Float4 backgroundColor, std::vector<CanvasObject *> &children);

    bool pointIntersectsObject(Float3 point) override;

private:
    Float2 currentMousePosition;
    bool mouseDragging;
    Float2 lastMousePosition;
};


#endif //DISCRETECOSINETRANSFORMATION_BASEFUNCTIONSPANEL_H
