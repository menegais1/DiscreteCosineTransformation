///Button class, responsible for rendering a button and ofering a callback list
///That will call all registered functions when the button is clicked

#ifndef BUTTON_H
#define BUTTON_H

#include "../Base/CanvasObject.h"
#include "../Utilities.h"
#include "../Vectors/Float3.h"
#include <vector>
#include <functional>

class Button : public CanvasObject {
public:
    Float4 backgroundColor;
    Float4 textColor;
    std::string title;

    Button(Float3 position, Float3 scale, Float4 backgroundColor, std::string title, Float4 textColor);

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    void addListener(std::function<void()> listener);

    bool pointIntersectsObject(Float3 point);

    void translate(Float3 translationAmount) override;

private:
    std::vector<std::function<void()>> onClickListeners;

    void notifyOnClickListeners();
};

#endif
