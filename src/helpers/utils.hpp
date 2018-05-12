/*
 * File: utilities.h
 * Author: Peter Reeves
 * Date 27 April 2018
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "SOIL.h"
#include <GL/freeglut.h>
#include <string>

struct Rect {
    int bottomLeftX;
    int bottomLeftY;
    int topRightX;
    int topRightY;
};

struct Vector2 {
    float x;
    float y;
};

struct Vector3 {
    float x;
    float y;
    float z;
};

class Utils {
        float randFloat();
    public:
        static void setMaterial(float diffuseR, float diffuseG, float diffuseB, float specularR, float specularG, float specularB,
                                float shininess, float emissionR, float emissionG, float emissionB);
        static void draw_string(std::string s);
};

#endif