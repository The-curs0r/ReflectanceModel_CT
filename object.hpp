/*
	* File:    object.hpp
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
	*   File containing object class and all its respective methods.
	*	Has the main code for checking if a ray intersects and object or not.
*/
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "ray.hpp"
#include <glm/glm.hpp>
#include <vector>

#define epsilon pow(10,-12) ///<Epsilon set to 10^-12

class object {
public:
	glm::dvec3 diffuse;///<Diffuse color of the object
	glm::dvec3 specular;///<Specular color of the object
	double s;///<Fraction of reflectance that is specular
	double d;///<Fraction of reflectance that is diffuse
	double rd;///<Diffuse bidirectional reflectance
	double n;///<Index of refraction
	double r_a;///<Ambient reflectance
	double shininess;///<Object's shininess
	int funcType;///<Function type to calculate slope distribution
	std::vector<std::vector<double> > dVal;///<Microfacet details
	virtual double intersect(ray& ray, glm::dvec3& normal) = 0;///<Method to intersect object and ray
};

class sphere : public object {
public:
	glm::dvec3 center;///<Center of sphere
	double radius;///<Radius of sphere
	/**
	*   double intersect(ray& ray, glm::dvec3& normal)
	*
	*   Summary of intersect() function:
	*
	*       Function to find the intersection point if a ray intersects the object and set normal if needed
	*
	*   Parameters  :
	*
	*       ray& ray:	Ray details
	*		glm::dvec3& normal:	normal at point of intersection
	*
	*   Return Value :
	*
	*       Returns the distance variable in the parametric ray equation , -1 if no intersection
	*
	*   Description :
	*
	*       Checks if ray intersects object or not using standard ray sphere intersection routine.
	*		Sets normal at the point of intersection.
*/
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
