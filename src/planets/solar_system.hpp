//
// Created by James Ridey on 10/05/2018.
//

#ifndef COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP
#define COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP

#include <GL/gl.h>
#include <GL/glu.h>

#include "constants.hpp"
#include "helpers/utils.hpp"

class SolarSystem {
    public:
        void update();
        void redraw();
        void setupOrbitView(Rect windowCoordinates);
        void setupRealisticView(Rect windowCoordinates);
};


#endif //COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP
