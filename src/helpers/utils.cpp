//
// Created by James Ridey on 10/05/2018.
//

#include "utils.hpp"

std::mt19937 &Utils::random_engine() {
    static std::mt19937 engine{(unsigned int) 347};
    return engine;
}

/*
 * Generate a random float between min and max
 */
float Utils::random_range_float(float min, float max) {
    //Probably not such a great idea to recreate the distribution every time
    //But neither is using it incorrectly
    std::uniform_real_distribution<float> distribution{min, max};
    return distribution(random_engine());
}

/*
 * Generate a random int between min and max
 */
int Utils::random_range_int(int min, int max) {
    //Probably not such a great idea to recreate the distribution every time
    //But neither is using it incorrectly
    std::uniform_int_distribution<> distribution{min, max};
    return distribution(random_engine());
}

/*
 * Generate a random int between 0 and 1
 */
float Utils::random_normalised() {
    return random_range_float(0, 1);
}

/*
 * Generate a random int between -1 and 1
 */
float Utils::random_clamped() {
    return random_range_float(-1, 1);
}

void Utils::draw_string(std::string s) {
    glRasterPos2f(0, 0);
    for (unsigned int i = 0; i < s.size(); i += 1) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s.at(i));
    }
}

// All parameters are 0 to 1 except for shininess which is 0 to 128
void Utils::set_material(
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