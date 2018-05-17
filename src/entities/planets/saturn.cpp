//
// Created by James Ridey on 12/05/2018.
//

#include <helpers/shapes.hpp>
#include "saturn.hpp"

Saturn::Saturn() : Planet(SATURN_CONFIG) {
    this->rotation_speed = 0;
    this->orbit_speed = 0;

    ring_texture_id = Textures::get_texture_id(Texture::SATURN_RINGS);
}

void Saturn::draw(DrawMode mode) {
    Planet::draw(mode);

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, ring_texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glScalef(SATURN_RING_SCALE,0,SATURN_RING_SCALE);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(1, 0, 1);
            glTexCoord2f(0, 1); glVertex3f(1, 0, -1);
            glTexCoord2f(1, 1); glVertex3f(-1, 0, -1);
            glTexCoord2f(1, 0); glVertex3f(-1, 0, 1);
        glEnd();

        glDisable(GL_BLEND);
    glPopMatrix();
}
