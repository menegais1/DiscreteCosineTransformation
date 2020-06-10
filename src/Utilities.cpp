#include "Utilities.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "Canvas/gl_canvas2d.h"
#include "Vectors/Float2.h"
#include "Vectors/Float3.h"

bool isPointInsideBounds(Float2 point, Float2 position, Float2 scale) {
    return point.x < position.x + scale.x && point.x > position.x && point.y < position.y + scale.y &&
           point.y > position.y;
}

int isLeft(Float3 P0, Float3 P1, Float3 P2) {
    return ((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y));
}


//Crossing number point in polygon algorithm implementation
//This code is patterned after [Franklin, 2000]
//Taken from http://geomalgorithms.com/a03-_inclusion.html
bool isPointInsidePolygon(Float2 P, std::vector<Float3> vertices, int n) {
    int cn = 0; // the  crossing number counter

    // loop through all edges of the polygon
    for (int i = 0; i < n; i++) {
        // edge from V[i]  to V[i+1]
        if (((vertices[i].y <= P.y) && (vertices[i + 1].y > P.y)) // an upward crossing
            || ((vertices[i].y > P.y) && (vertices[i + 1].y <= P.y))) { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float) (P.y - vertices[i].y) / (vertices[i + 1].y - vertices[i].y);
            if (P.x < vertices[i].x + vt * (vertices[i + 1].x - vertices[i].x)) // P.x < intersect
                ++cn;                                                           // a valid crossing of y=P.y right of P.x
        }
    }
    return (cn & 1); // 0 if even (out), and 1 if  odd (in)
}

bool leftMouseDown(int button, int state) {
    return button == MouseButton::Left && state == MouseState::Down;
}

bool leftMouseUp(int button, int state) {
    return button == MouseButton::Left && state == MouseState::Up;
}

Float3 lerp(Float3 x0, Float3 x1, float t) {
    return x0 * (1 - t) + x1 * t;
}

std::vector<Float3> generateCircle(Float3 center, Float3 scale, float sides) {
    float ang, x1, y1;
    float inc = PI_2 / sides;
    std::vector<Float3> vertices;
    for (ang = 0; ang < PI_2; ang += inc) {
        float x = (cos(ang) * scale.x);
        float y = (sin(ang) * scale.y);
        vertices.push_back({center.x + x, center.y + y, center.z});
    }
    vertices.push_back(vertices[0]);
    return vertices;
}

bool isPointInsideCircle(Float2 point, Float2 center, float radius) {
    return std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2) <= std::pow(radius, 2);
}

Float3 HSVtoRGB(Float3 hsv) {

    double r = 0, g = 0, b = 0;

    if (hsv.y == 0) {
        r = hsv.z;
        g = hsv.z;
        b = hsv.z;
    } else {
        int i;
        double f, p, q, t;

        if (hsv.x == 360)
            hsv.x = 0;
        else
            hsv.x = hsv.x / 60;

        i = (int) hsv.x;
        f = hsv.x - i;

        p = hsv.z * (1.0 - hsv.x);
        q = hsv.z * (1.0 - (hsv.x * f));
        t = hsv.z * (1.0 - (hsv.x * (1.0 - f)));

        switch (i) {
            case 0:
                r = hsv.z;
                g = t;
                b = p;
                break;

            case 1:
                r = q;
                g = hsv.z;
                b = p;
                break;

            case 2:
                r = p;
                g = hsv.z;
                b = t;
                break;

            case 3:
                r = p;
                g = q;
                b = hsv.z;
                break;

            case 4:
                r = t;
                g = p;
                b = hsv.z;
                break;

            default:
                r = hsv.z;
                g = p;
                b = q;
                break;
        }

    }

    return Float3(r, g, b);
}

Float3 RandomColorGenerator(float saturation, float brightness) {
    double rand = (std::rand() % 1000) / 1000.0;
    rand = std::min(360.0, rand * 360);
    return HSVtoRGB(Float3(rand, saturation, brightness));
}