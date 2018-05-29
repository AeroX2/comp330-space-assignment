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
    planets.push_back(new Planet(MIMAS_CONFIG));
    planets.push_back(new Planet(ENCELADUS_CONFIG));
    planets.push_back(new Planet(TETHYS_CONFIG));
    planets.push_back(new Planet(DIONE_CONFIG));
    planets.push_back(new Planet(RHEA_CONFIG));
    planets.push_back(new Planet(TITAN_CONFIG));
    planets.push_back(new Planet(IAPETUS_CONFIG));
    planets.push_back(new Saturn());

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

	// Sunlight
	glEnable(GL_LIGHT0);
	const float sun_position[4] = { 0.0f, 2.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
	const float sun_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
	const float sun_diffuse[4] = { 1.0f, 1.0f, 0.9f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);

	//TODO Starmap still needs more work
//    glPushMatrix();
//        glColor3f(1.0f, 1.0f, 1.0f);
//        glScalef(100,100,100);
//
//        glBindTexture(GL_TEXTURE_2D, Textures::get_texture_id(Texture::STARMAP));
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//        glFrontFace(GL_CW);
//        glDisable(GL_LIGHTING);
//            Shapes::draw_cube();
//        glEnable(GL_LIGHTING);
//        glFrontFace(GL_CCW);
//    glPopMatrix();

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
