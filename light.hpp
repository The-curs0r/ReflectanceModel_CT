/*
	* File:    light.hpp
	*
	* Author1:  Akshay Tiwari (2018A7PS0201H)
	*
	* Author2:  Mushkan Surekha  (2018B5A70477H)
	*
	* Author3:  Mahesh Swaminathan  (2018A4PS0982H)
	*
	* Date:     10-05-2020
	*
	* Course:   Computer Graphics (IS F311)
	*
	* Summary of File:
	*
	*   File containing light class.
*/
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

class light {
public:
	glm::dvec3 source;///<Source point of light
	double solidAngle;///<Solid angle of light source
	double power;///<Power of light source
};

#endif // !LIGHT_HPP
