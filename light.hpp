#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

class light {
public:
	glm::dvec3 source;
	int type;
	glm::dvec3 attenuation;
	glm::dvec3 color;
	double solidAngle;
	double power;
	//HALOO
};

#endif // !LIGHT_HPP
