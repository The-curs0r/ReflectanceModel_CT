#include <glm/glm.hpp>
#include "light.hpp"
#include "object.hpp"
#include "ray.hpp"
#include <algorithm>

void lightObject(light lightDetails, glm::dvec3 int_point, glm::dvec3 int_normal, object* int_object,ray& rayIn, glm::dvec3& outColor,int modelType) {
	
	if( modelType == 1 ) { 
		glm::dvec3 source = lightDetails.source;

		glm::dvec3 L = source - int_point;

		double lightDis = glm::dot(L, L);
		double intensity = lightDetails.power;// Dont divide by area, consider constant intensity (4 * pi * pow(lightDis, 2));

		L = glm::normalize(L);
		glm::dvec3 H = glm::normalize(-rayIn.direction + L);

		if (glm::dot(int_normal, L) > 0)
		{
			outColor += int_object->diffuse * intensity * glm::dot(int_normal, L) * lightDetails.solidAngle * (int_object->rd) * (int_object->d) * 1.0;
		}
		if (glm::dot(int_normal, H))
		{
			double dMul = 0;
			for (int i = 0;i < int_object->dVal.size();i++)
			{
				if (int_object->funcType == 1)
					dMul += (int_object->dVal[i][1] * (exp(-pow((glm::tan(glm::acos(glm::dot(int_normal, H)))) / int_object->dVal[i][0], 2)) / (pow(int_object->dVal[i][0], 2) * pow(glm::dot(int_normal, H), 4))));
				if (int_object->funcType == 2)
					dMul += 10 * int_object->dVal[i][1] * exp(-pow(glm::acos(glm::dot(int_normal, H)) / int_object->dVal[i][0], 2));
			}
			//std::cout << "\n";
			double G0 = std::min(1.0, (2 * glm::dot(int_normal, H) * glm::dot(int_normal, -rayIn.direction) / glm::dot(-rayIn.direction, H)));
			double G = std::min(G0, (2 * glm::dot(int_normal, H) * glm::dot(int_normal, L) / glm::dot(-rayIn.direction, H)));

			double c = glm::dot(H, L);
			double g = glm::sqrt(pow(int_object->n, 2) + c * c - 1);

			double R1 = pow((g - c) / (g + c), 2);
			double R2 = 1 + pow((c * (g + c) - 1) / (c * (g - c) + 1), 2);
			double F = (R1 * R2) / 2.0;
			//std::cout << R1 << " " << R2 << " " << F << "\n";
			double rs = F * dMul * G / ((3.14159) * (glm::dot(int_normal, L)) * glm::dot(int_normal, -rayIn.direction));

			outColor += int_object->specular * lightDetails.solidAngle * intensity * glm::dot(int_normal, L) * rs * int_object->s * 1.0;
		}
	}
	if (modelType == 2) {
		//Write code for phong model
	}
}