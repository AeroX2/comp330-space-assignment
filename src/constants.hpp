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

//Diffuse{RGB},Specular{RGB},Shininess,Reflection{RGB}
#define PLANET_MATERIAL_CONFIG 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f

//Texture,Size,Orbit Radius,Orbit Speed,Name
#define SATURN_CONFIG    Texture::SATURN,    0.65,          0,    0,     "Saturn"
#define MIMAS_CONFIG     Texture::MIMAS,     0.20f / 3.0f,  1.9,  0.009, "Mimas"
#define ENCELADUS_CONFIG Texture::ENCELADUS, 0.25f / 3.0f,  3.0,  0.014, "Enceladus"
#define TETHYS_CONFIG    Texture::TETHYS,    0.50f / 3.0f,  4.4,  0.019, "Tethys"
#define DIONE_CONFIG     Texture::DIONE,     0.55f / 3.0f,  5.5,  0.027, "Dione"
#define RHEA_CONFIG      Texture::RHEA,      0.70f / 3.0f,  6.5,  0.045, "Rhea"
#define TITAN_CONFIG     Texture::TITAN,     0.80f / 3.0f,  8.0,  0.080, "Titan"
#define IAPETUS_CONFIG   Texture::IAPETUS,   0.50f / 3.0f,  21.0, 0.070, "Iapetus"

const float STAR_DISTANCE = 50.0f;
const float SATURN_RING_SCALE = 2.5f;

const float PROBE_SIZE = 0.05f;
const float PROBE_ORBIT_DISTANCE = 0.1f;
const float PROBE_ORBIT_SPEED = 0.001f;

//TODO Scan speed should probably be based upon probe speed
const float SCAN_SPEED = 0.001f;
#define SCAN_LINE_COLOR 0,0.8,0
const float SCAN_LINE_INNER_TRANSPARENCY = 0.95f;
const float SCAN_LINE_OUTER_TRANSPARENCY = 0.3f;

#endif /* CONSTANTS_HPP_ */
