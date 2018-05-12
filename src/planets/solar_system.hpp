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

        void draw_orbit_view();
        void draw_realistic_view();
        void draw_zoomed_in_view();

        Planet* get_selected_planet();
        void set_selected_planet(unsigned char i);
    private:
        std::vector<Planet*> planets;
        Planet* selected_planet;
};


#endif //COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP
