#include "Panel.h"
#include <iostream>
#include "../Managers/GlobalManager.h"

Panel::Panel(std::vector<CanvasObject *> &children) {
    this->children = children;
}

Panel::Panel(Float3 position, Float3 scale, Float3 backgroundColor) {
    this->position = position;
    this->scale = scale;
    this->backgroundColor = backgroundColor;
}

void Panel::setActive(bool isActive) {
    for (int i = 0; i < children.size(); i++) {
        children[i]->setActive(isActive);
    }
    this->isActive = isActive;
    notifyOnActivateListeners();
};

Panel::Panel() {
}

bool Panel::pointIntersectsObject(Float3 point) {
    return isPointInsideBounds({point.x, point.y}, {position.x, position.y}, {scale.x, scale.y});
}

void Panel::translate(Float3 translationAmount) {
    this->position = position + translationAmount;
    for (int i = 0; i < children.size(); i++) {
        children[i]->translate(translationAmount);
    }
}

void Panel::addOnActivateListener(std::function<void(bool isActive)> listener) {
    this->onActivateListeners.push_back(listener);
}

void Panel::notifyOnActivateListeners() {
    for (int i = 0; i < onActivateListeners.size(); i++) {
        this->onActivateListeners[i](isActive);
    }
}

void Panel::setZIndex(int zIndex) {
    CanvasObject::setZIndex(zIndex);
    for (int i = 0; i < children.size(); i++) {
        children[i]->setZIndex(children[i]->getZIndex() + zIndex);
    }
}

Panel::~Panel() {
    for (int i = 0; i < children.size(); i++) {
        GlobalManager::getInstance()->deleteObject(children[i]);

    }
}
