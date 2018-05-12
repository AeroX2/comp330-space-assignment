//
// Created by James Ridey on 12/05/2018.
//

#include <utility>
#include <GL/gl.h>
#include <helpers/utils.hpp>
#include <helpers/shapes.hpp>
#include "planet.hpp"

Planet::Planet(Texture texture, float radius, float orbit_radius, float orbit_speed, std::string name) {
    this->texture_id = Textures::get_texture_id(texture);
    this->radius = radius;
    this->orbit_radius = orbit_radius;
    this->orbit_speed = orbit_speed;
    this->name = std::move(name);

    rotation = 0; //Utils::random_range_float(0, 2*PI);
    distance = 2*PI*orbit_radius;

    position.x = std::cos(rotation) * orbit_radius;
    position.y = 0;
    position.z = std::sin(rotation) * orbit_radius;
}

void Planet::update() {
    if (orbit_speed <= 0 && distance <= 0) return;

    rotation += orbit_speed / distance;

    position.x = std::cos(rotation) * orbit_radius;
    position.y = 0;
    position.z = std::sin(rotation) * orbit_radius;
}

void Planet::draw(DrawMode mode) {
    switch (mode) {
        case REALISTIC:
            glTranslatef(position.x, position.y, position.z);
            glScalef(radius, radius, radius);
            glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(texture_id));
            Utils::set_material(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
            Shapes::drawSphere();
            break;
        case ORBIT:
            glTranslatef(position.x, position.z, 0.0f);
            glScalef(radius, radius, radius);
            Shapes::draw_circle();
            Utils::draw_string(name);
            break;
        case ZOOMED_IN:
            break;
        case SURFACE:
            glColor3f(1,1,1);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id);

            glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
            glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
            glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
            glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
            glEnd();

            glDisable(GL_TEXTURE_2D);
            break;
    }
}
