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
	Textures::load_gl_texture(SATURN_TEXTURE);
	Textures::load_gl_texture(DIONE_TEXTURE);
    Textures::load_gl_texture(ENCELADUS_TEXTURE);
    Textures::load_gl_texture(MIMAS_TEXTURE);
    Textures::load_gl_texture(IAPETUS_TEXTURE);
    Textures::load_gl_texture(RHEA_TEXTURE);
    Textures::load_gl_texture(TETHYS_TEXTURE);
    Textures::load_gl_texture(TITAN_TEXTURE);

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

void redraw() {
    glClear(GL_COLOR_BUFFER_BIT);
    solar_system.redraw();

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

int main (int argc, char** argv) {
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
