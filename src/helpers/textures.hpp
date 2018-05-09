//
// Created by James Ridey on 9/05/2018.
//

#ifndef COMP330_SPACE_ASSIGNMENT_TEXTURES_HPP
#define COMP330_SPACE_ASSIGNMENT_TEXTURES_HPP

#include "SOIL.h"
#include <iostream>
#include <unordered_map>

class Textures {
    public:
        static std::unordered_map<std::string, int> textures;
        static int load_gl_texture(const char* filename);
        static int get_texture(std::string filename);
};


#endif //COMP330_SPACE_ASSIGNMENT_TEXTURES_HPP
