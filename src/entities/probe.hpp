//
// Created by James Ridey on 16/05/2018.
//

#ifndef COMP330_SPACE_ASSIGNMENT_ENTITY_H
#define COMP330_SPACE_ASSIGNMENT_ENTITY_H

#include "helpers/utils.hpp"

class Probe {
    public:
    Probe();

    void update();
        void draw(DrawMode mode);

        Vector3 position;
    private:
        int a;
};


#endif //COMP330_SPACE_ASSIGNMENT_ENTITY_H
