//
// Created by James Ridey on 10/05/2018.
//

#include "utils.hpp"

// Returns a random float between 0 and 1
float Utils::randFloat() {
    int r = rand();
    return (float) r / (float) RAND_MAX;
}

void Utils::draw_string(std::string s) {
    glRasterPos2f(0, 0);
    for (unsigned int i = 0; i < s.size(); i += 1) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s.at(i));
    }
}

// All parameters are 0 to 1 except for shininess which is 0 to 128
void Utils::setMaterial(
        float diffuseR, float diffuseG, float diffuseB,
        float specularR, float specularG, float specularB,
        float shininess,
        float emissionR, float emissionG, float emissionB
) {
    const float materialColour[4] = {diffuseR, diffuseG, diffuseB, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColour);

    const float materialSpecular[4] = {specularR, specularG, specularB, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);

    const float materialShininess[1] = {shininess};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    const float materialEmission[4] = {emissionR, emissionG, emissionB, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
}