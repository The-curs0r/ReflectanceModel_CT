/*
	* File:    lightingmodel.hpp
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
	*   Header file for the 2 lighting model that have been implemented.
*/
#ifndef LIGHTINGMODELHPP
#define LIGHTINGMODELHPP

void lightObject(light lightDetails,glm::dvec3 int_point,glm::dvec3 int_normal,object* int_object,ray& rayIn,glm::dvec3& outColor,int modelType);

#endif // !LIGHTINGMODELHPP
