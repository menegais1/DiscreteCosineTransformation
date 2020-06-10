#ifndef IMOUSE_H
#define IMOUSE_H

class IMouse {
public:
    virtual void mouse(int button, int state, int wheel, int direction, int x, int y) = 0;
};

#endif
