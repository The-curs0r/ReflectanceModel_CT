#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

class light {
public:
	glm::dvec3 source;
	double solidAngle;
	double power;
};

#endif // !LIGHT_HPP
