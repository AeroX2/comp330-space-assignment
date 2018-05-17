/*
 * File: utilities.h
 * Author: Peter Reeves
 * Date 27 April 2018
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "SOIL.h"
#include <GL/freeglut.h>
#include <cmath>
#include <string>
#include <random>

enum DrawMode {
    REALISTIC,
    ORBIT,
    SCANNING,
    SURFACE
};

struct Rect {
    int bottom_left_x;
    int bottom_left_y;
    int top_right_x;
    int top_right_y;
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
    public:
        static std::mt19937 &random_engine();
        static float random_range_float(float min, float max);
        static int random_range_int(int min, int max);
        static float random_normalised();
        static float random_clamped();

        static void set_material(float diffuseR, float diffuseG, float diffuseB,
                                 float specularR, float specularG,float specularB,
                                 float shininess,
                                 float emissionR, float emissionG, float emissionB);
        static void draw_string(std::string s);
};

#endif