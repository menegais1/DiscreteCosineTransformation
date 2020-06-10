
#include "Scene.h"

void Scene::mouse(int button, int state, int wheel, int direction, int x, int y) {
    CanvasObject::mouse(button, state, wheel, direction, x, y);
}

void Scene::keyboardUp(int key) {
    CanvasObject::keyboardUp(key);
}

void Scene::keyboard(int key) {
    CanvasObject::keyboard(key);
}

void Scene::render() {
    CanvasObject::render();
}

bool Scene::pointIntersectsObject(Float3 point) {
    return false;
}

Scene::Scene() {

}
