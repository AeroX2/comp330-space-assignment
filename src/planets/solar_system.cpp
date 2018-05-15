//
// Created by James Ridey on 10/05/2018.
//

#include <GL/freeglut.h>
#include <GL/glext.h>

#include "helpers/shapes.hpp"
#include "helpers/textures.hpp"
#include "solar_system.hpp"
#include "saturn.hpp"

void SolarSystem::init() {
   	planets.push_back(new Saturn());
    planets.push_back(new Planet(Texture::MIMAS,     0.20f / 3.0f,  1.9,  0.009, "Mimas"));
    planets.push_back(new Planet(Texture::ENCELADUS, 0.25f / 3.0f, 3.0,   0.014, "Enceladus"));
    planets.push_back(new Planet(Texture::TETHYS,    0.50f / 3.0f,  4.4,  0.019, "Tethys"));
    planets.push_back(new Planet(Texture::DIONE,     0.55f / 3.0f, 5.5,   0.027, "Dione"));
    planets.push_back(new Planet(Texture::RHEA,      0.70f / 3.0f,  6.5,  0.045, "Rhea"));
    planets.push_back(new Planet(Texture::TITAN,     0.80f / 3.0f,  8.0,  0.16,  "Titan"));
    planets.push_back(new Planet(Texture::IAPETUS,   0.50f / 3.0f,  21.0, 0.79,  "Iapetus"));

    selected_planet = planets[1];
    selected_planet->selected = true;
}

void SolarSystem::update() {
    for (Planet* planet : planets) {
        planet->update();
    }
}

void SolarSystem::draw_realistic_view() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	// Sunlight
	glEnable(GL_LIGHT0);
	const float sun_position[4] = { 0.0f, 2.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
	const float sun_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
	const float sun_diffuse[4] = { 1.0f, 1.0f, 0.9f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);

    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glScalef(10,10,10);

        glBindTexture(GL_TEXTURE_2D, Textures::get_texture_id(Texture::STARMAP));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFrontFace(GL_CW);
        Utils::set_material(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f);
        Shapes::draw_cube();
        glFrontFace(GL_CCW);
    glPopMatrix();

	// Planets
    for (Planet* planet : planets) {
        glPushMatrix();
            planet->draw(DrawMode::REALISTIC);
        glPopMatrix();
    }

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void SolarSystem::draw_orbit_view() {
    //Vertical flip mapping XZ plane to xy screen coordinates.
    glScalef(1.0f, -1.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    for (Planet* planet : planets) {
        glPushMatrix();
            planet->draw(DrawMode::ORBIT);
        glPopMatrix();
    }
}

void SolarSystem::draw_zoomed_in_view() {
    draw_realistic_view();
}

Planet* SolarSystem::get_selected_planet() {
    return selected_planet;
}

void SolarSystem::set_selected_planet(unsigned char i) {
    selected_planet->selected = false;
    selected_planet = planets[i];
    selected_planet->selected = true;
}
