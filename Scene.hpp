/*
	* File:    Scene.hpp
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
	*   File containing Scene class and all its respective methods.
	*	Has the main code for ray tracing.
*/
#ifndef SCENE_HPP
#define SCENE_HPP

#include "object.hpp"
#include "ray.hpp"
#include "light.hpp"
#include <algorithm>
#include <vector>
#include "lightingModel.hpp"

#define epsilon pow(10,-12)///<Epsilon set to 10^-12
#define pi 3.14159///<pi set to 3.13159

class Scene {
public:
	std::vector<object*> objects;///<Vector containing pointer to all objects in the scene
	std::vector<light*> lights;///<Vector containing pointer to all lights in the scene
	double ambientIntensity;///<Ambient intensity of the scene

	/**
	*   void add(object* object)
	*
	*   Summary of add() function:
	*
	*       Add object pointer passed to list of object pointers
	*
	*   Parameters  :
	*
	*       Pointer to object that has to be added
	*
	*   Return Value :
	*
	*       None
	*
	*   Description :
	*
	*       Adds the pointer to object using vector method push_back.
	*/
	void add(object* object) {
		objects.push_back(object);
	}
	/**
	*   void add(light* light)
	*
	*   Summary of add() function:
	*
	*       Add light pointer passed to list of light pointers
	*
	*   Parameters  :
	*
	*       Pointer to light that has to be added
	*
	*   Return Value :
	*
	*       None
	*
	*   Description :
	*
	*       Adds the pointer to light using vector method push_back.
	*/
	void add(light* light) {
		lights.push_back(light);
	}
	/**
	*   void calcAmbientIntensity()
	*
	*   Summary of calcAmbientIntensity() function:
	*
	*       Calculate the ambient intensity of the scene
	*
	*   Parameters  :
	*
	*       None
	*
	*   Return Value :
	*
	*       None
	*
	*   Description :
	*
	*       Calculate the ambient intensity of the scene as 0.0005 times the average light intensity of all lights.
	*/
	void calcAmbientIntensity() {
		std::vector<light*>::iterator lightIterator = lights.begin();
		for (lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++) {
			ambientIntensity += (0.0005)*(*lightIterator)->power;
		}
		ambientIntensity /= lights.size();
	}
	/**
	*   bool checkvis(glm::dvec3 target, glm::dvec3 source)
	*
	*   Summary of checkvis() function:
	*
	*       Check if a ray from sources reaches the target without hitting buy any object in its path
	*
	*   Parameters  :
	*
	*       glm::dvec3 target : Ray destination
	*		glm::dvec3 source : Ray source
	*
	*   Return Value :
	*
	*       Boolean: True if ray reaches light source ; False otherwise
	*
	*   Description :
	*
	*       Checks if ray form source to target is obstructed by any object in between.
	*/
	bool checkvis(glm::dvec3 target, glm::dvec3 source) {

		glm::dvec3 toSource = source - target;

		double t_light = glm::sqrt(glm::dot(toSource, toSource));

		ray* nray = new ray();
		nray->origin = target;
		nray->direction = toSource * (1 / t_light);
		double min_t = t_light;
		object* nearest_obj = nullptr;
		double t = FLT_MAX;
		glm::dvec3 normal = glm::dvec3(NULL, NULL, NULL);
		std::vector<object*>::iterator it = objects.begin();

		for (;it != objects.end();it++) {

			double t = (*it)->intersect(*nray, normal);
			if (t < min_t && t>0 && t > epsilon)
			{
				min_t = t;
				(nearest_obj) = *it;
				delete nray;
				return false;  //OBJECT IS NOT VISIBLE
			}
		}
		delete nray;
		return true;
	}
	/**
	*   glm::dvec3 intersectray(ray& rayIn, int depth)
	*
	*   Summary of intersectray() function:
	*
	*       Checks if a ray intersects any object in scene and colors it appropriatly
	*
	*   Parameters  :
	*
	*       ray& rayIn : Ray to be checked
	*		int depth : Number of maximum bounces for the ray
	*
	*   Return Value :
	*
	*       glm::dvec3 outColor: Returns the appropriate color after check intersections and lighting calculations
	*
	*   Description :
	*
	*       Checks if ray intersects any object of scene.
	*       If it does, checks how many lights contribute to the intersection point and colors the point.
	*/
	glm::dvec3 intersectray(ray& rayIn, int depth) {

		if (depth == 0)
			return glm::dvec3(0, 0, 0);

		double minDistance = FLT_MAX;

		glm::dvec3 outColor = glm::dvec3(0.360, 0.039, 0.039);

		std::vector<object*>::iterator objIterator = objects.begin();

		object* int_object = nullptr;
		glm::dvec3 int_point;
		glm::dvec3 int_normal;
		glm::dvec3 normal;
		for (objIterator = objects.begin();objIterator != objects.end(); objIterator++) {
			//Interesection with objects here
			double intersection = (*objIterator)->intersect(rayIn, normal);

			if (intersection < minDistance && intersection > epsilon)
			{
				int_normal = normal;
				minDistance = intersection;
				int_object = *objIterator;
				int_point = rayIn.origin + intersection * rayIn.direction + (epsilon * int_normal);
			}
		}
		if (int_object != nullptr)
		{

			int flag = 2;
			
			if(flag == 1) 
				outColor = (ambientIntensity) * ((int_object)->r_a) * (int_object->diffuse);
			else if (flag==2)
				outColor = (ambientIntensity) * (0.1) * (int_object->diffuse);

			std::vector<light*>::iterator lightIterator = lights.begin();

			for (lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++)
			{
				if (checkvis(int_point, (*lightIterator)->source)) {
					lightObject(**lightIterator,int_point,int_normal,int_object,rayIn,outColor,flag);
				}
			}
		}
		return outColor;
	}

};

#endif // !SCENE_HPP
