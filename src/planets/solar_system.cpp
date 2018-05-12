//
// Created by James Ridey on 10/05/2018.
//

#include <helpers/shapes.hpp>
#include <helpers/textures.hpp>
#include "solar_system.hpp"
#include "saturn.hpp"

void SolarSystem::init() {
   	planets.push_back(new Saturn());
    planets.push_back(new Planet(Texture::MIMAS_TEXTURE,     0.2 / 3.0f,  1.9,  0.009, "Mimas"));
    planets.push_back(new Planet(Texture::ENCELADUS_TEXTURE, 0.25/ 3.0f, 3.0,   0.014, "Enceladus"));
    planets.push_back(new Planet(Texture::TETHYS_TEXTURE,    0.5 / 3.0f,  4.4,  0.019, "Tethys"));
    planets.push_back(new Planet(Texture::DIONE_TEXTURE,     0.55/ 3.0f, 5.5,   0.027, "Dione"));
    planets.push_back(new Planet(Texture::RHEA_TEXTURE,      0.7 / 3.0f,  6.5,  0.045, "Rhea"));
    planets.push_back(new Planet(Texture::TITAN_TEXTURE,     0.8 / 3.0f,  8.0,  0.16, "Titan"));
    planets.push_back(new Planet(Texture::IAPETUS_TEXTURE,   0.5 / 3.0f,  21.0, 0.79, "Iapetus"));

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
	const float sunPosition [4] = { 0.0f, 2.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
	const float sunAmbient [4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
	const float sunDiffuse [4] = { 1.0f, 1.0f, 0.9f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);

	glColor3f(1.0f, 1.0f, 1.0f);

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
	glPushMatrix();
        //Vertical flip mapping XZ plane to xy screen coordinates.
        glScalef(1.0f, -1.0f, 1.0f);
        glColor3f(1.0f, 1.0f, 1.0f);

        for (Planet* planet : planets) {
            glPushMatrix();
                planet->draw(DrawMode::ORBIT);
            glPopMatrix();
        }
	glPopMatrix();
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
