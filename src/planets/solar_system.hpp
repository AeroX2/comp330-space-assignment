//
// Created by James Ridey on 10/05/2018.
//

#ifndef COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP
#define COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

#include "constants.hpp"
#include "helpers/utils.hpp"
#include "planet.hpp"

class SolarSystem {
    public:
        void init();
        void update();
        void redraw();

        void setup_orbit_view(Rect windowCoordinates);
        void setup_realistic_view(Rect windowCoordinates);

        void draw_orbit_view();
        void draw_realistic_view();
    private:
        std::vector<Planet*> planets;
};


#endif //COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP
