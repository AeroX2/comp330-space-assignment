//
// Created by James Ridey on 10/05/2018.
//

#ifndef COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP
#define COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../../constants.hpp"
#include "../../helpers/utils.hpp"
#include "../probe.hpp"
#include "planet.hpp"

class SolarSystem {
    public:
        void init();
        void update();

        void draw_orbit_view();
        void draw_realistic_view();
        void draw_scanning_view();

        void set_selected_planet(unsigned char i);
        void draw_surface_view();
    private:
        std::vector<Planet*> planets;
        std::vector<Vector3> stars;

        Planet* selected_planet;
        Probe probe;
};


#endif //COMP330_SPACE_ASSIGNMENT_SOLAR_SYSTEM_HPP
