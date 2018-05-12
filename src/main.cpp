/*
COMP330 - 2018
Author: Peter Reeves
Date: 27 April 2018
*/

#include <iostream>
#include <GL/freeglut.h>
#if defined(_WIN32) || defined(WIN32)
#else
#include <unistd.h>
#endif

#include "helpers/textures.hpp"
#include "constants.hpp"
#include "planets/solar_system.hpp"

int WINDOW_WIDTH = WINDOW_INITIAL_WIDTH;
int WINDOW_HEIGHT = WINDOW_INITIAL_HEIGHT;

SolarSystem solar_system;

double current_time = 0;
double accumulator = 0;
bool running = true;

void init() {
	Textures::load_gl_textures();
	solar_system.init();

	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_NORMALIZE);
}

void keyboard_callback(unsigned char key, int x, int y) {
	switch(key) {
        default:
            break;
	}
}

void special_input_callback(int key, int x, int y) {
	switch(key)	{
		case GLUT_KEY_UP:
            break;

		case GLUT_KEY_F1:
            break;

        case GLUT_KEY_F2:
            break;

        case GLUT_KEY_F3:
            break;

        case GLUT_KEY_F4:
            break;

        default:
            break;
	}
}

void resize_callback(int width, int height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
}

void update() {
    solar_system.update();
}

void setup_realistic_view(Rect windowCoordinates) {
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

void setup_orbit_view(Rect windowCoordinates) {
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

void redraw() {
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

	glClear(GL_COLOR_BUFFER_BIT);
    setup_realistic_view(topViewport);
    solar_system.draw_realistic_view();

	setup_orbit_view(bottomRightViewport);
	solar_system.draw_orbit_view();

    glutSwapBuffers();
}

/*
 * Main game loop
 * Based upon Fix Your Timestep by Gaffer on Games
 * https://gafferongames.com/post/fix_your_timestep/
 */
void gameloop() {
    double new_time = glutGet(GLUT_ELAPSED_TIME);
    double frameTime = ((new_time - current_time) * 1000) / CLOCK_PER_SEC;
    current_time = new_time;

    accumulator += frameTime;

    while (accumulator >= FRAME_RATE) {
        glutMainLoopEvent();
        update();
        glutPostRedisplay();
        accumulator -= FRAME_RATE;
    }

#if defined(_WIN32) || defined(WIN32)
    Sleep(1);
#else
    usleep(1);
#endif
}

int main(int argc, char** argv) {
    debug("Setting up OpenGL windows");
	glutInit(&argc, argv);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Mission Control");

    debug("Registering callbacks");
	glutDisplayFunc(redraw);
	glutSpecialFunc(special_input_callback);
	glutKeyboardFunc(keyboard_callback);
	glutReshapeFunc(resize_callback);

    debug("Starting gameloop");
    init();
    while (running) {
        gameloop();
    }

	return 0;
}
