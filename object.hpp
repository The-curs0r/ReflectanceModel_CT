#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "ray.hpp"
#include <glm/glm.hpp>
#include <vector>

#define epsilon pow(10,-12)

class object {
public:
	glm::dvec3 diffuse;
	glm::dvec3 specular;
	double s;
	double d;
	double rd;
	double n;
	double r_a;
	int funcType;
	std::vector<std::vector<double> > dVal;
	virtual double intersect(ray& ray, glm::dvec3& normal) = 0;
};

class sphere : public object {
public:
	glm::dvec3 center;
	double radius;

	double intersect(ray& ray, glm::dvec3& normal) {

		double c = glm::dot(ray.origin - center, ray.origin - center) - radius * radius;
		double b = 2 * glm::dot(ray.direction, ray.origin - center);
		double a = glm::dot(ray.direction, ray.direction);

		if (b * b - 4 * a * c < 0)
			return -1;

		double s1 = (-b + glm::sqrt(b * b - 4 * a * c)) / 2 * a;
		double s2 = (-b - glm::sqrt(b * b - 4 * a * c)) / 2 * a;

		double t;

		if (s1 < 0 && s2 < 0)
			return -1;
		else if (s1 < 0)
			t = s2;
		else if (s2 < 0)
			t = s1;
		else
			t = s1 > s2 ? s2 : s1;
		normal = glm::normalize(ray.origin + t * ray.direction - center);
		return t;
	}
};

#endif // !OBJECT_HPP
