///Utilities file, has some common structs and functions used in the program

#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include "Vectors/Float2.h"
#include "Vectors/Float3.h"
#include "Vectors/Float4.h"

#define stringify(name) # name

enum Channel {
    Red = 0,
    Green = 1,
    Blue = 2,
    Alpha = 3
};

enum MouseButton {
    Left = 0,
    ScrollClick = 1,
    Right = 2,
    ScrollUp = 3,
    ScrollDown = 4
};

enum MouseState {
    Down = 0,
    Up = 1,
    None = -2
};

bool isPointInsideBounds(Float2 point, Float2 position, Float2 scale);

bool isPointInsideCircle(Float2 point, Float2 center, float radius);

int isLeft(Float3 P0, Float3 P1, Float3 P2);

bool isPointInsidePolygon(Float2 P, std::vector<Float3> vertices, int n);

std::vector<Float3> generateSquare(Float3 center, Float3 scale);

std::vector<Float3> generateCircle(Float3 center, Float3 scale, float sides);

std::vector<Float3> generateTriangle(Float3 center, Float3 scale);

std::vector<Float3> generatePentagon(Float3 center, Float3 scale);

std::vector<Float3> generateHexagon(Float3 center, Float3 scale);

bool leftMouseDown(int button, int state);

bool leftMouseUp(int button, int state);

Float3 lerp(Float3 x0, Float3 x1, float t);

Float3 RandomColorGenerator(float saturation, float brightness);

Float3 HSVtoRGB(Float3 hsv);


#endif
