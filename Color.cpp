/**
 * Color.cpp - encapsulates OpenGL color properties 
 */

#include "Color.h"

Color::Color() {
    r = g = b = 0.0f;
    a = 1.0f;
}

Color::Color( float red, float green, float blue, float alpha ) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void Color::set( float red, float green, float blue, float alpha ) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}
