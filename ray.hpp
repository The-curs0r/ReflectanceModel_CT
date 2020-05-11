/*
	* File:    ray.hpp
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
	*   File containing ray class and all its respective methods.
	*	Has the main code for passing a ray thorugh pixel i and j.
*/
#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

class ray {
public:
	glm::dvec3 origin;///<Ray origin
	glm::dvec3 direction;///<Ray Direction
	/**
	*   void raythrough(double cam[], double i, double j, double width, double height)
	*
	*   Summary of raythrough() function:
	*
	*       Passes a ray through pixel i and j, given the details about camera and aspect
	*
	*   Parameters  :
	*
	*       double cam[] : Camera 
	*		double i :	Row number
	*		double j :	Column number
	*		double width : Width of the image
	*		double height : Height of the image
	*
	*   Return Value :
	*
	*       None
	*
	*   Description :
	*
	*       Sets the ray origin and direction corresponding to the given details about camera and aspect.
	*/
	void raythrough(double cam[], double i, double j, double width, double height) {

		//Camera is vec3:looking_from vec3:looking_at vec3:up_vector double:fovy

		origin = glm::dvec3(cam[0], cam[1], cam[2]); //Ray origin

		glm::dvec3 a = glm::dvec3(cam[0], cam[1], cam[2]) - glm::dvec3(cam[3], cam[4], cam[5]);   //Where to look
		glm::dvec3 b = glm::dvec3(cam[6], cam[7], cam[8]);  //Up vector

		//Creating coordiante frame
		glm::dvec3 w = glm::normalize(a);
		glm::dvec3 u = glm::normalize(glm::cross(b, w));
		glm::dvec3 v = glm::cross(w, u);

		double fovx = 2 * glm::atan(tan(glm::radians(cam[9]) * 0.5) * (width / height));
		double fovy = glm::radians(cam[9]);


		double ang_alpha = glm::tan(fovx / 2) * (j - width / 2) / (width / 2);
		double ang_beta = glm::tan(fovy / 2) * (height / 2 - i) / (height / 2);

		direction = glm::normalize(glm::dvec3(ang_alpha * u + ang_beta * v - w)); //Ray direction
	}
};

#endif // !RAY_HPP
