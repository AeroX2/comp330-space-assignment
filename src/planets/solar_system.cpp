//
// Created by James Ridey on 10/05/2018.
//

#include <helpers/shapes.hpp>
#include <helpers/textures.hpp>
#include "solar_system.hpp"

void SolarSystem::update() {

}

void SolarSystem::setupRealisticView(Rect windowCoordinates) {
	const int viewportWidth = windowCoordinates.topRightX - windowCoordinates.bottomLeftX;
	const int viewportHeight = windowCoordinates.topRightY - windowCoordinates.bottomLeftY;
	glViewport(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glScissor(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glClearColor(0.1f, 0.0f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float) viewportWidth / (float) viewportHeight, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.0f, 1.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void SolarSystem::setupOrbitView(Rect windowCoordinates) {
	const int viewportWidth = windowCoordinates.topRightX - windowCoordinates.bottomLeftX;
	const int viewportHeight = windowCoordinates.topRightY - windowCoordinates.bottomLeftY;
	glViewport(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glScissor(windowCoordinates.bottomLeftX, windowCoordinates.bottomLeftY, viewportWidth, viewportHeight);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const float worldWindowHalfWidth = 4.0f;
	const float aspectRatio = (float) viewportHeight / (float) viewportWidth;
	glOrtho(-worldWindowHalfWidth, worldWindowHalfWidth, -worldWindowHalfWidth * aspectRatio, worldWindowHalfWidth * aspectRatio, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SolarSystem::redraw() {
	const int dividerHeight = WINDOW_HEIGHT * HORIZONTAL_DIVISION;
	const int firstThird = (int) (WINDOW_WIDTH * (1.0f / 3.0f));
	const int secondThird = (int) (WINDOW_WIDTH * (2.0f / 3.0f));

	Rect bottomRightViewport;
	bottomRightViewport.bottomLeftX = secondThird;
	bottomRightViewport.bottomLeftY = 0;
	bottomRightViewport.topRightX = WINDOW_WIDTH;
	bottomRightViewport.topRightY = dividerHeight;

	Rect topViewport;
	topViewport.bottomLeftX = 0;
	topViewport.bottomLeftY = dividerHeight;
	topViewport.topRightX = WINDOW_WIDTH;
	topViewport.topRightY = WINDOW_HEIGHT;

	// Realistic
	{
		setupRealisticView(topViewport);

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

		// Saturn
		glPushMatrix();
			glScalef(SATURN_RADIUS, SATURN_RADIUS, SATURN_RADIUS);
			glBindTexture(GL_TEXTURE_2D, Textures::get_texture(SATURN_TEXTURE));
			Utils::setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
			Shapes::drawSphere();
		glPopMatrix();
//
//		// Iapetus
//		glPushMatrix();
//			glTranslatef(iapetusPosition.x, iapetusPosition.y, iapetusPosition.z);
//			glScalef(IAPETUS_RADIUS, IAPETUS_RADIUS, IAPETUS_RADIUS);
//			glBindTexture(GL_TEXTURE_2D, iapetusTexture);
//			setMaterial(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f);
//			drawSphere();
//		glPopMatrix();
	}

	// Orbit
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		setupOrbitView(bottomRightViewport);

		glPushMatrix();
			// Vertical flip mapping XZ plane to xy screen coordinates.
			glScalef(1.0f, -1.0f, 1.0f);

			glColor3f(1.0f, 1.0f, 1.0f);

//			// Saturn Planet
//			glPushMatrix();
//				glScalef(SATURN_RADIUS, SATURN_RADIUS, SATURN_RADIUS);
//				drawCircle();
//				drawString("Saturn");
//			glPopMatrix();
//
//			glPushMatrix();
//				glTranslatef(iapetusPosition.x, iapetusPosition.z, 0.0f);
//				glScalef(IAPETUS_RADIUS, IAPETUS_RADIUS, IAPETUS_RADIUS);
//				drawCircle();
//				drawString("Iapetus");
//			glPopMatrix();
		glPopMatrix();
	}
}
