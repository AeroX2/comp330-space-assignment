//
// Created by James Ridey on 9/05/2018.
//

#include "textures.hpp"

std::unordered_map<std::string, int> Textures::textures = {};

int Textures::load_gl_texture(const char* filename) {
    const unsigned int index = SOIL_load_OGL_texture(
            filename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
    );

    if (index == 0) {
        std::cerr << filename << " : " << SOIL_last_result();
        return -1;
    }

    Textures::textures[filename] = index;
    return index;
}

int Textures::get_texture(std::string filename) {
    return Textures::textures[filename];
}