//
// Created by James Ridey on 9/05/2018.
//

#include "textures.hpp"

std::map<Texture, std::string> enum_file_mapping { std::make_pair(Texture::DIONE, "textures/dione.jpg"),
                                                   std::make_pair(Texture::SATURN, "textures/saturn.jpg"),
                                                   std::make_pair(Texture::SATURN_RINGS, "textures/saturn_rings.png"),
                                                   std::make_pair(Texture::ENCELADUS, "textures/enceladus.jpg"),
                                                   std::make_pair(Texture::MIMAS, "textures/mimas.jpg"),
                                                   std::make_pair(Texture::IAPETUS, "textures/iapetus.jpg"),
                                                   std::make_pair(Texture::RHEA, "textures/rhea.jpg"),
                                                   std::make_pair(Texture::TETHYS, "textures/tethys.jpg"),
                                                   std::make_pair(Texture::TITAN, "textures/titan.jpg") };

std::unordered_map<Texture, unsigned int, TextureEnumHash> Textures::textures {};

void Textures::load_gl_textures() {
    for (std::pair<Texture, std::string> pair : enum_file_mapping) {
        const unsigned int index = SOIL_load_OGL_texture(
                pair.second.c_str(),
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
        );

        if (index == 0) {
            std::cerr << pair.second << " : " << SOIL_last_result();
        }

        textures[pair.first] = index;
    }

    //TODO Load the stars
    unsigned int index = SOIL_load_OGL_texture(
            "textures/stars/cwd_bk.JPG",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);

    if (index == 0) {
        std::cerr << SOIL_last_result();
    } else {
        textures[Texture::STARMAP] = index;
    }
}

unsigned int Textures::get_texture_id(Texture texture) {
    return textures[texture];
}