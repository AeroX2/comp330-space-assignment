/*
 * constants.hpp
 *
 *  Created on: 10 Mar. 2018
 *      Author: James Ridey (44805632)
 */

#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#define debug(x) std::cout << (x) << std::endl

const int WINDOW_INITIAL_WIDTH = 1024;
const int WINDOW_INITIAL_HEIGHT = 768;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

const float HORIZONTAL_DIVISION = 0.3f;

const float PI = 3.141592;
const float FRAME_RATE = 1/60.0f;
const long CLOCK_PER_SEC = 1000000;

const float SATURN_RADIUS = 1.0f;

#endif /* CONSTANTS_HPP_ */
