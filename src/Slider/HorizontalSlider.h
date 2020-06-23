//Color picker secondary window, used to select colors variance between black and the color selected at
//the color picker main window

#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include "../Base/CanvasObject.h"
#include "../Vectors/Float3.h"
#include <vector>
#include <functional>

class HorizontalSlider : public CanvasObject {
public:

    float currentValue;

    float textSpace = 10;
    Float4 backgroundColor;
    Float4 handleColor;
    Float4 lineColor;

    HorizontalSlider(Float3 position, Float3 scale, Float4 backgroundColor, Float4 handleColor);

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    bool pointIntersectsObject(Float3 point) override;

    void translate(Float3 translationAmount);

    void addOnValueChangedListener(std::function<void(float value)> listener);

    void notifyOnValueChangedListeners();

    void setValues(float minValue, float maxValues, float steps);

    void setCurValue(float curValue);

private:
    float maxValue;
    float minValue;
    float steps;

    bool mouseDragging;
    bool mouseInside;
    Float2 currentMousePosition;
    Float2 lastMousePosition;

    float getCurrentValueT(Float2 mousePosition);

    std::vector<std::function<void(float value)>> onValueChangedListeners;

};

#endif