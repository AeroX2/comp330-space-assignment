//
// Created by James Ridey on 16/05/2018.
//

#include "probe.hpp"

Probe::Probe() {
    planet = nullptr;

    size = PROBE_SIZE;
    position = { 0,0,0 };
    orbit_rotation = 0;
}

void Probe::update() {
    orbit_rotation += PROBE_ORBIT_SPEED;
    position.x = planet->position.x + std::sin(orbit_rotation) * (planet->size + PROBE_ORBIT_DISTANCE);
    position.z = planet->position.z + std::cos(orbit_rotation) * (planet->size + PROBE_ORBIT_DISTANCE);
}

void Probe::draw(DrawMode mode) {
    switch (mode) {
        case REALISTIC:
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(position.x, position.y, position.z);
                glScalef(size, size, size);
                Shapes::draw_cube();
            glPopMatrix();
            glEnable(GL_TEXTURE_2D);
            break;
        case ORBIT:
            glPushMatrix();
                glTranslatef(position.x, position.z, 0);
                glScalef(size, size, 1);
                Shapes::draw_circle();
            glPopMatrix();
            break;
        case SCANNING:
            break;
        default:
            break;
    }
}

void Probe::set_orbiting_planet(Planet* planet) {
    this->planet = planet;
}
