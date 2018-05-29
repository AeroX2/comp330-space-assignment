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
    this->size = radius;
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

    //TODO This should be configurable
    rotation_speed = 0.01f;
}

void Planet::update() {
    if (selected) scan_amount += SCAN_SPEED; //scan_amount < 1 ? 0.001 : 0;

    rotation += rotation_speed;

    if (orbit_speed <= 0 && distance <= 0) return;
    orbit_rotation += orbit_speed / distance;

    position.x = std::cos(orbit_rotation) * orbit_radius;
    position.y = 0;
    position.z = std::sin(orbit_rotation) * orbit_radius;
}

void Planet::draw(DrawMode mode) {
    switch (mode) {
        //TODO Create the scanning mode
        case REALISTIC:
            glTranslatef(position.x, position.y, position.z);
            glRotatef(rotation, 0, 1, 0);
            glScalef(size, size, size);

            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            Utils::set_material(PLANET_MATERIAL_CONFIG);
            Shapes::draw_sphere();
            break;
        case ORBIT:
            glLineWidth(1);
            glColor3ub(255,255,255);

            if (selected) {
                glPushMatrix();
                    //Draw the orbit
                    glScalef(orbit_radius, orbit_radius, 1);
                    Shapes::draw_circle();
                glPopMatrix();
            }

            //Draw the planet and name
            glTranslatef(position.x, position.z, 0);
            glScalef(size, size, 1);
            Shapes::draw_circle();
            Utils::draw_string(name);
            break;
        case SCANNING:
            glLineWidth(1);
            glTranslatef(position.x, position.y, position.z);
            glRotatef(rotation, 0, 1, 0);
            glScalef(size, size, size);

            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            if (selected) {
                Utils::set_material(PLANET_MATERIAL_SCANNING_CONFIG);
                Shapes::draw_sphere();

                //Draw the wireframe
                glBindTexture(GL_TEXTURE_2D, 0);
                Utils::set_material(PLANET_MATERIAL_CONFIG);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    //TODO Isolate these to constants.hpp
                    float scale = scan_amount <= 1.0 ? 1.035f-scan_amount*0.035f : 1.001f;
                    glScalef(scale, scale, scale);
                    int cuts = scan_amount*110+10 <= 120 ? (int)(scan_amount*110+10) : 120;
                    Shapes::draw_sphere_custom(cuts, cuts);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            } else {
                Utils::set_material(PLANET_MATERIAL_CONFIG);
                Shapes::draw_sphere();
            }

            break;
        case SURFACE:
            glColor3f(1,1,1);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id);

            //Draw part of the texture
            float x = scan_amount*2-1;
            glBegin(GL_QUADS);
                glTexCoord2f(scan_amount, 0); glVertex3f(x, -1, 0);
                glTexCoord2f(scan_amount, 1); glVertex3f(x, 1, 0);
                glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
                glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
            glEnd();

            //Draw the grid lines
            glColor3ub(255,128,0);
            glLineWidth(3);

            float lines = 8.0f;
            auto lines_int = (int)lines;
            glBegin(GL_LINES);
                for (int y = -lines_int; y <= lines_int; y++) {
                    glVertex2d(-1, y/lines);
                    glVertex2d(x, y/lines);
                }
                for (int x2 = -lines_int; x2 <= x*lines_int; x2++) {
                    glVertex2d(x2/lines, -1);
                    glVertex2d(x2/lines, 1);
                }
            glEnd();

            glEnable(GL_BLEND);
            glColor3f(0,0,1);

            //TODO I don't really like this scanning system, replace it?
            x = fmodf(x+1,2)-1;
            glBegin(GL_QUADS);
                glColor4f(SCAN_LINE_COLOR, SCAN_LINE_OUTER_TRANSPARENCY); glVertex3f(x+0.1f, -1, 0);
                glColor4f(SCAN_LINE_COLOR, SCAN_LINE_OUTER_TRANSPARENCY); glVertex3f(x+0.1f, 1, 0);
                glColor4f(SCAN_LINE_COLOR, SCAN_LINE_INNER_TRANSPARENCY); glVertex3f(x, 1, 0);
                glColor4f(SCAN_LINE_COLOR, SCAN_LINE_INNER_TRANSPARENCY); glVertex3f(x, -1, 0);

                glColor4f(SCAN_LINE_COLOR, SCAN_LINE_INNER_TRANSPARENCY); glVertex3f(x, 1, 0);
                glColor4f(SCAN_LINE_COLOR, SCAN_LINE_INNER_TRANSPARENCY); glVertex3f(x, -1, 0);
                glColor4f(SCAN_LINE_COLOR, SCAN_LINE_OUTER_TRANSPARENCY); glVertex3f(x-0.1f, -1, 0);
                glColor4f(SCAN_LINE_COLOR, SCAN_LINE_OUTER_TRANSPARENCY); glVertex3f(x-0.1f, 1, 0);
            glEnd();

            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);

            break;
    }
}
