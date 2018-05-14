//
// Created by James Ridey on 12/05/2018.
//

#ifndef COMP330_SPACE_ASSIGNMENT_SATURN_HPP
#define COMP330_SPACE_ASSIGNMENT_SATURN_HPP

#include "planet.hpp"

class Saturn : public Planet {
    public:
        Saturn();

        void draw(DrawMode mode);
    private:
        GLuint ring_texture_id;
};


#endif //COMP330_SPACE_ASSIGNMENT_SATURN_HPP
