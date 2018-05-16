//
// Created by James Ridey on 16/05/2018.
//

#include "helpers/shapes.hpp"
#include "probe.hpp"

Probe::Probe() {
    position = { 1, 1, 1 };
}

void Probe::update() {

}

void Probe::draw(DrawMode mode) {
    switch (mode) {
        case REALISTIC:
            glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(position.x, position.y, position.z);
                glScalef(0.05, 0.05, 0.05);
                Shapes::draw_cube();
            glPopMatrix();
            break;
        case ORBIT:
            glPushMatrix();
                glTranslatef(position.x, position.z, 0);
                Shapes::draw_cube();
            glPopMatrix();
            break;
        case ZOOMED_IN:
            break;
        default:
            break;
    }
}
