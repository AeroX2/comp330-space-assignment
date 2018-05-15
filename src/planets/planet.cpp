//
// Created by James Ridey on 12/05/2018.
//

#include <utility>
#include <GL/gl.h>
#include <GL/glext.h>

#include "helpers/utils.hpp"
#include "helpers/shapes.hpp"
#include "planet.hpp"

Planet::Planet(Texture texture, float radius, float orbit_radius, float orbit_speed, std::string name) {
    this->texture_id = Textures::get_texture_id(texture);
    this->radius = radius;
    this->orbit_radius = orbit_radius;
    this->orbit_speed = orbit_speed;
    this->name = std::move(name);

    selected = false;
    scan_amount = 0;

    rotation = Utils::random_range_float(0, 2*PI);
    orbit_rotation = Utils::random_range_float(0, 2*PI);
    distance = 2*PI*orbit_radius;

    position.x = std::cos(orbit_rotation) * orbit_radius;
    position.y = 0;
    position.z = std::sin(orbit_rotation) * orbit_radius;

    rotation_speed = 0.5f;
}

void Planet::update() {
    if (selected) scan_amount += scan_amount < 1 ? 0.001 : 0;

    rotation += rotation_speed;

    if (orbit_speed <= 0 && distance <= 0) return;
    orbit_rotation += orbit_speed / distance;

    position.x = std::cos(orbit_rotation) * orbit_radius;
    position.y = 0;
    position.z = std::sin(orbit_rotation) * orbit_radius;
}

void Planet::draw(DrawMode mode) {
    switch (mode) {
        case REALISTIC:
            glTranslatef(position.x, position.y, position.z);
            glRotatef(rotation, 0, 1, 0);
            glScalef(radius, radius, radius);

            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            Utils::set_material(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
            Shapes::draw_sphere();
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
                glTexCoord2f(scan_amount, 1); glVertex3f(scan_amount*2-1, 1, 0);
                glTexCoord2f(scan_amount, 0); glVertex3f(scan_amount*2-1, -1, 0);
            glEnd();

            glDisable(GL_TEXTURE_2D);
            break;
    }
}
