///The panel class is used for object agrupation and ease of
///Activating and deactivating objects groups with the function setActive.
///It contain a list of all registered objects.

#ifndef PANEL_H
#define PANEL_H

#include "../Base/CanvasObject.h"
#include "../Base/ITransformable.h"
#include "../Utilities.h"
#include <vector>
#include <functional>

class Panel : public CanvasObject {
public:
    Float4 backgroundColor;
    std::vector<CanvasObject *> children;

    Panel(Float3 position, Float3 scale, Float4 backgroundColor,std::vector<CanvasObject *> &children);

    Panel();

    ~Panel() override;

    Panel(Float3 position, Float3 scale, Float4 backgroundColor);

    void setActive(bool isActive) override;

    void setZIndex(int zIndex) override;

    bool pointIntersectsObject(Float3 point) override;

    void translate(Float3) override;

    void addOnActivateListener(std::function<void(bool isActive)> listener);

    void notifyOnActivateListeners();

private:
    std::vector<std::function<void(bool isActive)>> onActivateListeners;
};

#endif
