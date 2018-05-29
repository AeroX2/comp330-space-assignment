//
// Created by James Ridey on 10/05/2018.
//

#include "shapes.hpp"

void Shapes::draw_sphere() {
	const float radius = 1.0f;
	const int slices = 64;
	const int stacks = 32;

	static bool compiled = false;
	static unsigned int sphereList = glGenLists(1);

	static GLUquadric* sphereQuadric = gluNewQuadric();

	if (!compiled) {
		gluQuadricTexture(sphereQuadric, true);
		glNewList(sphereList, GL_COMPILE);
			glPushMatrix();
				glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
				gluSphere(sphereQuadric, radius, slices, stacks);
			glPopMatrix();
		glEndList();
		compiled = true;
	}

	glCallList(sphereList);
}

void Shapes::draw_sphere_custom(int slices, int stacks) {
	const float radius = 1.0f;

//	static bool compiled = false;
//	static unsigned int sphereList = glGenLists(1);
//
	static GLUquadric* sphereQuadric = gluNewQuadric();
//
//	if (!compiled) {
//		gluQuadricTexture(sphereQuadric, true);
//		glNewList(sphereList, GL_COMPILE);
//		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
//		glPopMatrix();
//		glEndList();
//		compiled = true;
//	}

    gluSphere(sphereQuadric, radius, slices, stacks);
}

void Shapes::draw_circle() {
	const float sides = 128.0f;
	const float step = (2.0f * PI) / sides;

	static bool compiled = false;
	static unsigned int circleList = glGenLists(1);

	if (!compiled) {
		glNewList(circleList, GL_COMPILE);
			glBegin(GL_LINE_LOOP);
				for (float theta = 0; theta < 2 * PI; theta += step) {
					float x = std::cos(theta);
					float y = std::sin(theta);
					glVertex2f(x, y);
				}
			glEnd();
		glEndList();
		compiled = true;
	}

	glCallList(circleList);
}

void Shapes::draw_cube() {
	static bool compiled = false;
	static unsigned int cubeList = glGenLists(1);

	if (!compiled) {
		glNewList(cubeList, GL_COMPILE);
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f( 0.5f,  0.5f, -0.5f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f( -0.5f, 0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f( -0.5f, 0.5f,  0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f( 0.5f,  0.5f,  0.5f);

				glNormal3f(0.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f( 0.5f, -0.5f, -0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f( 0.5f, -0.5f,  0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f,  0.5f);

				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f( 0.5f,  0.5f,  0.5f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-0.5f,  0.5f,  0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f,  0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f( 0.5f, -0.5f,  0.5f);

				glNormal3f(0.0f, 0.0f, -1.0f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f( 0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f,  0.5f, -0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f( 0.5f,  0.5f, -0.5f);

				glNormal3f(-1.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-0.5f,  0.5f,  0.5f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-0.5f,  0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f,  0.5f);

				glNormal3f(1.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f( 0.5f,  0.5f, -0.5f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f( 0.5f,  0.5f,  0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f( 0.5f, -0.5f,  0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f( 0.5f, -0.5f, -0.5f);
			glEnd();
		glEndList();
		compiled = true;
	}

	glCallList(cubeList);
}