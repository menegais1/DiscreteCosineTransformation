///Manager responsible for forwarding the GLUT callbacks
///To every CanvasObject instantiated, every object has a uniqueId given
///in the beggining of its lifetime

#ifndef GLOBAL_MANAGER_H
#define GLOBAL_MANAGER_H

#include <vector>
#include <chrono>

#include "../Base/CanvasObject.h"

class GlobalManager {
public:
    void keyboard(int key);

    void keyboardUp(int key);

    void mouse(int button, int state, int wheel, int direction, int x, int y);

    void render();

    int registerObject(CanvasObject *object);

    bool isMouseInsideObject(CanvasObject *object);

    CanvasObject *unregisterObject(CanvasObject *object);

    void changeObjectZIndex(CanvasObject *object);

    static GlobalManager *getInstance();

    CanvasObject *deleteObject(CanvasObject *object);

    int *screenWidth;
    int *screenHeight;
    Float2 mousePosition;
    float deltaTime;
    float time = 0;
    float fpsUpdateCycle = 0.25;
    float lastFpsUpdate = 0;
    int fps;
private:
    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>> lastTime = std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>> currentTime = std::chrono::high_resolution_clock::now();

    int objectIdCounter;
    static GlobalManager *instance;
    //The order of the objects is descending, so what will be rendered first is last
    std::vector<CanvasObject *> objects;

    GlobalManager();

    void addObjectToList(CanvasObject *object);


    CanvasObject *cleanUpObjects();
};

#endif
