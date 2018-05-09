#ifndef SHAPES_HPP_
#define SHAPES_HPP_

#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>

#include "constants.hpp"

class Shapes {

        void drawCircle();
        void drawCube();
    public:
        static void drawSphere();
};

#endif
