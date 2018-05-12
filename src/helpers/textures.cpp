//
// Created by James Ridey on 9/05/2018.
//

#include "textures.hpp"

std::map<Texture, std::string> enum_file_mapping { std::make_pair(Texture::DIONE_TEXTURE, "textures/dione.jpg"),
                                                   std::make_pair(Texture::SATURN_TEXTURE, "textures/saturn.jpg"),
                                                   std::make_pair(Texture::ENCELADUS_TEXTURE, "textures/enceladus.jpg"),
                                                   std::make_pair(Texture::MIMAS_TEXTURE, "textures/mimas.jpg"),
                                                   std::make_pair(Texture::IAPETUS_TEXTURE, "textures/iapetus.jpg"),
                                                   std::make_pair(Texture::RHEA_TEXTURE, "textures/rhea.jpg"),
                                                   std::make_pair(Texture::TETHYS_TEXTURE, "textures/tethys.jpg"),
                                                   std::make_pair(Texture::TITAN_TEXTURE, "textures/titan.jpg") };

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
}

unsigned int Textures::get_texture_id(Texture texture) {
    return textures[texture];
}