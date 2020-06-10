#ifndef IKeyboard_H
#define IKeyboard_H

class IKeyboard {
public:
    virtual void keyboard(int key) = 0;

    virtual void keyboardUp(int key) = 0;
};

#endif
