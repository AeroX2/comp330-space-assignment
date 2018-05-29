//
// Created by James Ridey on 16/05/2018.
//

#include "probe.hpp"

Probe::Probe() {
    planet = nullptr;

    size = PROBE_SIZE;
    position = { 0,0,0 };
    current_tick = 0;
    orbit_rotation = 0;
}

void Probe::update() {
    orbit_rotation += PROBE_ORBIT_SPEED;
    position.x = planet->position.x + std::sin(orbit_rotation) * (planet->size * PROBE_ORBIT_DISTANCE);
    position.z = planet->position.z + std::cos(orbit_rotation) * (planet->size * PROBE_ORBIT_DISTANCE);

    if (current_tick++ > PROBE_RECORD_TICKOVER) {
        current_tick = 0;
        past_positions.push_back(position);
    }
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
            glLineWidth(1);

            glPushMatrix();
                glTranslatef(position.x, position.z, 0);
                glScalef(size, size, 1);
                Shapes::draw_circle();
            glPopMatrix();

            glColor3ub(255,128,0);
            glBegin(GL_LINE_STRIP);
                for (Vector3 position : past_positions) {
                    glVertex2d(position.x, position.z);
                }
            glEnd();

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
