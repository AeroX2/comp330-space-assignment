//
// Created by James Ridey on 12/05/2018.
//

#ifndef COMP330_SPACE_ASSIGNMENT_PLANET_HPP
#define COMP330_SPACE_ASSIGNMENT_PLANET_HPP


#include <GL/gl.h>
#include <helpers/textures.hpp>
#include <helpers/utils.hpp>

enum DrawMode {
    REALISTIC,
    ORBIT,
    ZOOMED_IN,
    SURFACE
};

class Planet {
    public:
        Planet(Texture texture,
               float radius,
               float orbit_radius,
               float orbit_speed,
               std::string name);

        virtual void update();
        virtual void draw(DrawMode mode);
        Vector3 position;
        float radius;
        float orbit_rotation;
        bool selected;
    private:
        float orbit_radius;
        float orbit_speed;

        float rotation;
        float distance;

        float scan_amount;

        int texture_id;
        std::string name;
};


#endif //COMP330_SPACE_ASSIGNMENT_PLANET_HPP
