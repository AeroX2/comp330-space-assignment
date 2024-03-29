//
// Created by James Ridey on 16/05/2018.
//

#ifndef COMP330_SPACE_ASSIGNMENT_PROBE_H
#define COMP330_SPACE_ASSIGNMENT_PROBE_H

#include <vector>
#include "planets/planet.hpp"
#include "../helpers/shapes.hpp"
#include "../helpers/utils.hpp"

class Probe {
    public:
        Probe();

        void update();
        void draw(DrawMode mode);
        void set_orbiting_planet(Planet* planet);

        Vector3 position;
    private:
        int current_tick;

        float size;
        float orbit_rotation;

        Planet* planet;
        std::vector<Vector3> past_positions;
};


#endif
