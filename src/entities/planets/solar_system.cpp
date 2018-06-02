//
// Created by James Ridey on 10/05/2018.
//

#include <GL/freeglut.h>
#include <GL/glext.h>

#include "../../helpers/shapes.hpp"
#include "../../helpers/textures.hpp"
#include "solar_system.hpp"
#include "saturn.hpp"

void SolarSystem::init() {
    planets.push_back(new Planet(MIMAS_CONFIG));
    planets.push_back(new Planet(ENCELADUS_CONFIG));
    planets.push_back(new Planet(TETHYS_CONFIG));
    planets.push_back(new Planet(DIONE_CONFIG));
    planets.push_back(new Planet(RHEA_CONFIG));
    planets.push_back(new Planet(TITAN_CONFIG));
    planets.push_back(new Planet(IAPETUS_CONFIG));
    planets.push_back(new Saturn());

	for (int i = 0; i < STAR_AMOUNT; i++) {
		// uniform random cartesian stars inside cube
		float x = Utils::random_clamped();
		float y = Utils::random_clamped();
		float z = Utils::random_clamped();

		float d = sqrt((x*x)+(y*y)+(z*z));
		if (d < 1e-3) continue;

		d = STAR_DISTANCE/d;
		x *= d;
		y *= d;
		z *= d;

		stars.push_back({x,y,z});
	}

    set_selected_planet(0);
}

void SolarSystem::update() {
    probe.update();
    for (Planet* planet : planets) {
        planet->update();
    }
}

void SolarSystem::draw_realistic_view() {
    gluLookAt(3.0f, 3.0f, 3.0f,
              selected_planet->position.x, selected_planet->position.y, selected_planet->position.z,
              0.0f, 1.0f, 0.0f);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

	glPointSize(1.0);
	glBegin(GL_POINTS);
		for (Vector3 star : stars) {
			float brightness = Utils::random_range_float(0.5, 1);
			glColor3f(brightness,brightness,brightness);
			glVertex3f(star.x,star.y,star.z);
		}
	glEnd();

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

	// Planets and probe
    probe.draw(DrawMode::REALISTIC);
    for (Planet* planet : planets) {
        glPushMatrix();
            planet->draw(DrawMode::REALISTIC);
        glPopMatrix();
    }
}

void SolarSystem::draw_orbit_view() {
    glScalef(0.5,0.5,0);
    glTranslatef(-selected_planet->position.x, selected_planet->position.z, 0);

    //Vertical flip mapping XZ plane to xy screen coordinates.
    glScalef(1.0f, -1.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    probe.draw(DrawMode::ORBIT);
    for (Planet* planet : planets) {
        glPushMatrix();
            planet->draw(DrawMode::ORBIT);
        glPopMatrix();
    }
}

void SolarSystem::draw_scanning_view() {
    gluLookAt(probe.position.x, probe.position.y, probe.position.z,
              selected_planet->position.x, selected_planet->position.y, selected_planet->position.z,
              0.0f, 1.0f, 0.0f);

    // Sunlight
    glEnable(GL_LIGHT0);
    const float sun_position[4] = { 0.0f, 2.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
    const float sun_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
    const float sun_diffuse[4] = { 1.0f, 1.0f, 0.9f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);

    // Planets and probe
    probe.draw(DrawMode::SCANNING);
    for (Planet* planet : planets) {
        glPushMatrix();
            planet->draw(DrawMode::SCANNING);
        glPopMatrix();
    }
}

void SolarSystem::draw_surface_view() {
    selected_planet->draw(DrawMode::SURFACE);
}

void SolarSystem::set_selected_planet(unsigned char i) {
    if (selected_planet != nullptr) selected_planet->selected = false;

    selected_planet = planets[i];
    probe.set_orbiting_planet(selected_planet);

    selected_planet->selected = true;
}
