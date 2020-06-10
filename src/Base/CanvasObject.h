#ifndef CANVAS_OBJECT_H
#define CANVAS_OBJECT_H

#include "../Utilities.h"
#include "IMouse.h"
#include "ITransformable.h"
#include "IKeyboard.h"
#include "IRender.h"
#include "../Vectors/Float3.h"

class CanvasObject : public IRender, public IKeyboard, public IMouse, public ITransformable {
public:
    Float3 position;
    Float3 scale;
    Float3 rotation;
    bool isValid;
    void keyboard(int key) override;

    void keyboardUp(int key) override;

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    virtual void setZIndex(int zIndex);

    int getZIndex();

    CanvasObject();

    virtual ~CanvasObject();

    virtual void setActive(bool isActive);

    bool getActive();

    bool checkIfCanExecuteCallback();

    virtual bool pointIntersectsObject(Float3 point) = 0;

    bool isMouseInsideObject();

    void translate(Float3) override;

    void rotate(float, Float3) override;

    void rescale(Float3, Float3) override;

protected:
    bool isActive;
    int objectId;

private:
    int zIndex;
    bool lastActiveState;
};

#endif
