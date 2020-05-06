#ifndef SCENE_HPP
#define SCENE_HPP

#include "object.hpp"
#include "ray.hpp"
#include "light.hpp"
#include <algorithm>
#include <vector>


#define epsilon pow(10,-12)

class Scene {
public:
	std::vector<object*> objects;
	std::vector<light*> lights;

	void add(object* object) {
		objects.push_back(object);
	}

	void add(light* light) {
		lights.push_back(light);
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
			std::vector<light*>::iterator lightIterator = lights.begin();

			outColor = glm::dvec3(0, 0, 0);

			for (lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++)
			{
				glm::dvec3 source = (*lightIterator)->source;
				if ((*lightIterator)->type == 0) source = int_point - source;        //Directional light

				if (checkvis(int_point, source)) {
					//COLOR OBJECT AS IT IS VISIBLE
					glm::dvec3 L = source - int_point;

					int count = 0;

					if ((*lightIterator)->type == 0) L = (*lightIterator)->source;        //Directional light
					L = glm::normalize(L);
					glm::dvec3 H = glm::normalize(-rayIn.direction + L);
					
					if (outColor == glm::dvec3(0, 0, 0))
						outColor += int_object->rd * (int_object->diffuse) * ((*lightIterator)->intensityAmb) * (3.1415) * (0.045);
					//if (glm::dot(int_normal, L) > 0)
					{
						outColor += (((int_object)->diffuse ) * (*lightIterator)->intensity) * (((*lightIterator)->solidAngle)) * glm::dot(normal, L) * (int_object->rd) * (int_object->d) *(25.0);
						
					}
					//if (glm::dot(int_normal, H))
					{
						double dMul = 0;//Wrtie specular component
						for (int i = 0;i < int_object->dVal.size();i++)
						{
							dMul += (int_object->dVal[i][1] * (exp (-pow((glm::tan(glm::acos(glm::dot(int_normal, H))))/ int_object->dVal[i][0], 2)) / (pow(int_object->dVal[i][0],2)*pow(glm::dot(int_normal,H),4))));
						}
						//std::cout << "\n";
						double G0 = std::min(1.0, (2 * glm::dot(int_normal, H) * glm::dot(int_normal, -rayIn.direction) / glm::dot(-rayIn.direction, H)));
						double G = std::min(G0, (2 * glm::dot(int_normal, H) * glm::dot(int_normal, L) / glm::dot(-rayIn.direction, H)));
						double costheta = glm::dot(H, L);
						double sintheta2 = 1 - costheta * costheta;
						double R1 = pow((int_object->n * costheta - glm::sqrt(1 - int_object->n * int_object->n * sintheta2) ) / (int_object->n * costheta + glm::sqrt(1 - int_object->n * int_object->n * sintheta2)), 2);
						double R2 = pow((int_object->n * glm::sqrt(1 - int_object->n * int_object->n * sintheta2) - costheta ) / (int_object->n * glm::sqrt(1 - int_object->n * int_object->n * sintheta2) + costheta ),2);
						double F = (R1 + R2) / 2.0;
						//std::cout << R1 << " " << R2 << " " << F << "\n";
						double rs = F * dMul * G / ((3.14159) * (glm::dot(int_normal, L)) * glm::dot(int_normal, -rayIn.direction));
						
						outColor += (((int_object)->specular) * (((*lightIterator)->solidAngle)*((*lightIterator)->intensity)) * glm::dot(int_normal, L) * (rs) * (int_object->s));
					}
				//std::cout << outColor[0] << " " << outColor[1] << " " << outColor[2] << "\n";
				}
			}

			rayIn.direction = glm::normalize(rayIn.direction);
			int_normal = glm::normalize(int_normal);

			/*ray* reflected = new ray();
			reflected->direction = rayIn.direction - (2 * glm::dot(rayIn.direction, int_normal)) * int_normal;
			reflected->origin = int_point;
			outColor += ((int_object->reflectivity) * intersectray(*reflected, depth - 1));
			delete reflected;*/

		}
		return outColor;
	}

};

#endif // !SCENE_HPP
