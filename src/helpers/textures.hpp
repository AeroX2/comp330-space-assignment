//
// Created by James Ridey on 9/05/2018.
//

#ifndef COMP330_SPACE_ASSIGNMENT_TEXTURES_HPP
#define COMP330_SPACE_ASSIGNMENT_TEXTURES_HPP

#include "SOIL.h"

#include <map>
#include <iostream>
#include <utility>
#include <unordered_map>

struct TextureEnumHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

enum Texture {
    SATURN_TEXTURE,
    DIONE_TEXTURE,
    ENCELADUS_TEXTURE,
    MIMAS_TEXTURE,
    IAPETUS_TEXTURE,
    RHEA_TEXTURE,
    TETHYS_TEXTURE,
    TITAN_TEXTURE
};

class Textures {
    public:
        static std::unordered_map<Texture, unsigned int, TextureEnumHash> textures;

        static void load_gl_textures();
        static unsigned int get_texture_id(Texture texture);
};


#endif //COMP330_SPACE_ASSIGNMENT_TEXTURES_HPP
