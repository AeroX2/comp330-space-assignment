/*
COMP330 - 2018
Author: Peter Reeves
Date: 27 April 2018
*/

#include <iostream>
#include <GL/freeglut.h>

#include "helpers/shapes.hpp"

#if defined(_WIN32) || defined(WIN32)
#else
#include <unistd.h>
#endif

#include "helpers/textures.hpp"
#include "constants.hpp"
#include "entities/planets/solar_system.hpp"

int WINDOW_WIDTH = WINDOW_INITIAL_WIDTH;
int WINDOW_HEIGHT = WINDOW_INITIAL_HEIGHT;

SolarSystem solar_system;

int fps;
int frame_counter;
int previous_fps_time;

Rect top;
Rect viewport1;
Rect viewport2;
Rect viewport3;
Rect viewport4;
Rect* current_top = &viewport1;

double current_time = 0;
double accumulator = 0;
bool running = true;

void keyboard_callback(unsigned char key, int x, int y) {
	switch(key) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            solar_system.set_selected_planet(key-'1');
            break;
        default:
            break;
	}
}

void swap_viewports(Rect& new_top) {
    *current_top = new_top;
    new_top = top;
    current_top = &new_top;
}

void special_input_callback(int key, int x, int y) {
	switch(key)	{
		case GLUT_KEY_UP:
            break;

		case GLUT_KEY_F1:
            swap_viewports(viewport1);
            break;

        case GLUT_KEY_F2:
            swap_viewports(viewport2);
            break;

        case GLUT_KEY_F3:
            swap_viewports(viewport3);
            break;

        case GLUT_KEY_F4:
            swap_viewports(viewport4);
            break;

        default:
            break;
	}
}

void reshape(int width, int height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;

	auto dividerHeight = (int) (WINDOW_HEIGHT * HORIZONTAL_DIVISION);
	auto firstThird = (int) (WINDOW_WIDTH * (1.0f / 3.0f));
	auto secondThird = (int) (WINDOW_WIDTH * (2.0f / 3.0f));

	//Top
    viewport1.bottom_left_x = 0;
    viewport1.bottom_left_y = dividerHeight;
    viewport1.top_right_x = WINDOW_WIDTH;
    viewport1.top_right_y = WINDOW_HEIGHT;

	//Bottom right
	viewport2.bottom_left_x = secondThird;
	viewport2.bottom_left_y = 0;
    viewport2.top_right_x = WINDOW_WIDTH;
    viewport2.top_right_y = dividerHeight;

    //Bottom middle
    viewport3.bottom_left_x = firstThird;
    viewport3.bottom_left_y = 0;
    viewport3.top_right_x = secondThird;
    viewport3.top_right_y = dividerHeight;

    //Bottom left
    viewport4.bottom_left_x = 0;
    viewport4.bottom_left_y = 0;
    viewport4.top_right_x = firstThird;
    viewport4.top_right_y = dividerHeight;

    top = viewport1;
}

void init() {
	Textures::load_gl_textures();
	solar_system.init();
	reshape(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);

	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_NORMALIZE);
}

void update() {
    solar_system.update();
}

void setup_realistic_view(Rect window_coordinates) {
	int viewport_width = window_coordinates.top_right_x - window_coordinates.bottom_left_x;
	int viewport_height = window_coordinates.top_right_y - window_coordinates.bottom_left_y;
	glViewport(window_coordinates.bottom_left_x, window_coordinates.bottom_left_y, viewport_width, viewport_height);
	glScissor(window_coordinates.bottom_left_x, window_coordinates.bottom_left_y, viewport_width, viewport_height);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float) viewport_width / (float) viewport_height, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	gluLookAt(3.0f, 3.0f, 3.0f,
//              planet.position.x, planet.position.y, planet.position.z,
//              0.0f, 1.0f, 0.0f);
}

void setup_orbit_view(Rect window_coordinates) {
	const int viewport_width = window_coordinates.top_right_x - window_coordinates.bottom_left_x;
	const int viewport_height = window_coordinates.top_right_y - window_coordinates.bottom_left_y;
	glViewport(window_coordinates.bottom_left_x, window_coordinates.bottom_left_y, viewport_width, viewport_height);
	glScissor(window_coordinates.bottom_left_x, window_coordinates.bottom_left_y, viewport_width, viewport_height);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const float world_window_half_height = 4.0f;
	const float aspect_ratio = (float) viewport_height / (float) viewport_width;
	glOrtho(-world_window_half_height,
            world_window_half_height,
            -world_window_half_height * aspect_ratio,
            world_window_half_height * aspect_ratio,
            -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//TODO Not correctly working for the orbit view
//    glScalef(0.5,0.5,0);
//	glTranslatef(-planet.position.x, planet.position.z, 0);
}

void setup_scanning_view(Rect window_coordinates) {
	const int viewport_width = window_coordinates.top_right_x - window_coordinates.bottom_left_x;
	const int viewport_height = window_coordinates.top_right_y - window_coordinates.bottom_left_y;
	glViewport(window_coordinates.bottom_left_x, window_coordinates.bottom_left_y, viewport_width, viewport_height);
	glScissor(window_coordinates.bottom_left_x, window_coordinates.bottom_left_y, viewport_width, viewport_height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f, (float) viewport_width / (float) viewport_height, 0.01f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setup_surface_view(Rect window_coordinates) {
	const int viewport_width = window_coordinates.top_right_x - window_coordinates.bottom_left_x;
	const int viewport_height = window_coordinates.top_right_y - window_coordinates.bottom_left_y;
	glViewport(window_coordinates.bottom_left_x, window_coordinates.bottom_left_y, viewport_width, viewport_height);
	glScissor(window_coordinates.bottom_left_x, window_coordinates.bottom_left_y, viewport_width, viewport_height);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void redraw() {
	glClear(GL_COLOR_BUFFER_BIT);

    //Calculate the current FPS
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    if ((currentTime - previous_fps_time) >= 1000) {
        fps = frame_counter;
        frame_counter = 0;
        previous_fps_time = currentTime;
        std::cout << "FPS: " << fps << std::endl;
    }
    frame_counter++;
    //char temp_string[50];
    //snprintf(temp_string, 50, "FPS: %d", fps);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    setup_realistic_view(viewport1);
    solar_system.draw_realistic_view();

    setup_scanning_view(viewport2);
    solar_system.draw_scanning_view();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);

    setup_orbit_view(viewport3);
    solar_system.draw_orbit_view();

	setup_surface_view(viewport4);
	solar_system.draw_surface_view();

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
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Mission Control");

    debug("Registering callbacks");
	glutDisplayFunc(redraw);
	glutSpecialFunc(special_input_callback);
	glutKeyboardFunc(keyboard_callback);
	glutReshapeFunc(reshape);

    debug("Starting gameloop");
    init();
    while (running) {
        gameloop();
    }

	return 0;
}
