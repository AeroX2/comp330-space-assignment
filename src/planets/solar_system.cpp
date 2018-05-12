//
// Created by James Ridey on 10/05/2018.
//

#include <helpers/shapes.hpp>
#include <helpers/textures.hpp>
#include "solar_system.hpp"

void SolarSystem::init() {
   	planets.push_back(new Planet(Texture::SATURN_TEXTURE,    1.0,  0.0, 0.0, "Saturn"));
    planets.push_back(new Planet(Texture::DIONE_TEXTURE,     0.55, 1.5, 0.1, "Dione"));
    planets.push_back(new Planet(Texture::ENCELADUS_TEXTURE, 0.25, 1.0, 0.1, "Enceladus"));
    planets.push_back(new Planet(Texture::IAPETUS_TEXTURE,   0.5,  10.0, 0.1, "Iapetus"));
    planets.push_back(new Planet(Texture::MIMAS_TEXTURE,     0.2,  0.9, 0.1, "Mimas"));
    planets.push_back(new Planet(Texture::RHEA_TEXTURE,      0.7,  2.5, 0.1, "Rhea"));
    planets.push_back(new Planet(Texture::TETHYS_TEXTURE,    0.5,  1.4, 0.1, "Tethys"));
    planets.push_back(new Planet(Texture::TITAN_TEXTURE,     0.8,  5.0, 0.1, "Titan"));
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
	glPushMatrix();
	    for (Planet* planet : planets) {
	       planet->draw(DrawMode::REALISTIC);
	    }
	glPopMatrix();

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

        glPushMatrix();
            for (Planet* planet : planets) {
                planet->draw(DrawMode::ORBIT);
            }
        glPopMatrix();
	glPopMatrix();
}
