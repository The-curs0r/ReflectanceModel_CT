#ifndef SCENE_HPP
#define SCENE_HPP

#include "object.hpp"
#include "ray.hpp"
#include "light.hpp"
#include <algorithm>
#include <vector>
#include "lightingModel.hpp"

#define epsilon pow(10,-12)
#define pi 3.14159

class Scene {
public:
	std::vector<object*> objects;
	std::vector<light*> lights;
	double ambientIntensity;

	void add(object* object) {
		objects.push_back(object);
	}

	void add(light* light) {
		lights.push_back(light);
	}

	void calcAmbientIntensity() {
		std::vector<light*>::iterator lightIterator = lights.begin();
		for (lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++) {
			ambientIntensity += (0.0005)*(*lightIterator)->power;
		}
		ambientIntensity /= lights.size();
	}

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

			outColor = (ambientIntensity) * ((int_object)->r_a) * (int_object->diffuse);

			std::vector<light*>::iterator lightIterator = lights.begin();

			for (lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++)
			{
				if (checkvis(int_point, (*lightIterator)->source)) {
					lightObject(**lightIterator,int_point,int_normal,int_object,rayIn,outColor,1);
				}
			}
		}
		return outColor;
	}

};

#endif // !SCENE_HPP
