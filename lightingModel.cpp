/*
	* File:    lightingmodel.cpp
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
	*   Contains method to update the color of a pixel based on one of the two lighting models.
*/
#include <glm/glm.hpp>
#include "light.hpp"
#include "object.hpp"
#include "ray.hpp"
#include <algorithm>

/**
	*   void lightObject(light lightDetails, glm::dvec3 int_point, glm::dvec3 int_normal, object* int_object,ray& rayIn, glm::dvec3& outColor,int modelType)
	*
	*   Summary of lightObject() function:
	*
	*       Calculates the pixel color for the given details
	*
	*   Parameters  :
	*
	*		light lightDetails: Details of the light which lights up the pixel
	*		glm::dvec3 int_point: Intersection point of ray and object
	*		glm::dvec3 int_normal: Normal at intersection point
	*		object* int_object: Intersected object details
	*		ray& rayIn: Intersecting ray details
	*		glm::dvec3& outColor: Color of the pixel
	*		int modelType: Variable to identify lighting model to be used
	*
	*   Return Value :
	*
	*       None (Updates the outColor variable)
	*
	*   Description :
	*
	*       For the given details, appropriate lighting model is used to find color of the pixel.
	*		If modelType == 1, Torrance-Sparrow reflectance model is used for lighting calculations.
	*		If modelType == 2, Phong Reflection model is used for lighting calculations.
*/
void lightObject(light lightDetails, glm::dvec3 int_point, glm::dvec3 int_normal, object* int_object,ray& rayIn, glm::dvec3& outColor,int modelType) {
	
	if( modelType == 1 ) {  //Torrance-Cook Model

		glm::dvec3 source = lightDetails.source; //Source of light ray

		glm::dvec3 L = source - int_point; //Vector from source to intersection point

		double lightDis = glm::dot(L, L); //Distance from source to intersection point
		double intensity = lightDetails.power; //Dont divide by area, consider constant intensity or attenuate later in model

		L = glm::normalize(L); //Normalize L vector
		glm::dvec3 H = glm::normalize(-rayIn.direction + L); //Half Vector - Between L and Viewing Ray i.e. -rayIn

		//Compute the diffuse component and add it to the outColor vector
		if (glm::dot(int_normal, L) > 0)
		{
			outColor += int_object->diffuse * intensity * glm::dot(int_normal, L) * lightDetails.solidAngle * (int_object->rd) * (int_object->d);
		}
		//Compute the specular component and add it to the outColor vector
		if (glm::dot(int_normal, H))
		{
			//Calculate facet slope distribution function (dMul) from given root mean square slopes of facets (m) and relative weights of facet slopes (w)
			double dMul = 0;
			for (int i = 0;i < int_object->dVal.size();i++)
			{
				if (int_object->funcType == 1) //Beckmann Distribution
				{
					dMul += (int_object->dVal[i][1] * (exp(-pow((glm::tan(glm::acos(glm::dot(int_normal, H)))) / int_object->dVal[i][0], 2)) / (pow(int_object->dVal[i][0], 2) * pow(glm::dot(int_normal, H), 4))));
				}
				if (int_object->funcType == 2)  //Phong Distribution
				{
					dMul += 10 * int_object->dVal[i][1] * exp(-pow(glm::acos(glm::dot(int_normal, H)) / int_object->dVal[i][0], 2));
				}
			}
			
			//Calculate the geometrical attenuation factor (G)
			double G0 = std::min(1.0, (2 * glm::dot(int_normal, H) * glm::dot(int_normal, -rayIn.direction) / glm::dot(-rayIn.direction, H)));
			double G = std::min(G0, (2 * glm::dot(int_normal, H) * glm::dot(int_normal, L) / glm::dot(-rayIn.direction, H)));

			//Calculate F i.e. reflectance of the perfectly smooth surface (microfacet)
			double c = glm::dot(H, L); //Cosine of angle between H and L vectors
			double g = glm::sqrt(pow(int_object->n, 2) + c * c - 1);

			double R1 = pow((g - c) / (g + c), 2);
			double R2 = 1 + pow((c * (g + c) - 1) / (c * (g - c) + 1), 2);
			double F = (R1 * R2) / 2.0;

			//Finally calculate rpecular bidirectional reflectance Rs
			double rs = F * dMul * G / ((3.14159) * (glm::dot(int_normal, L)) * glm::dot(int_normal, -rayIn.direction));

			//Compute the specular color and update outColor
			outColor += int_object->specular * lightDetails.solidAngle * intensity * glm::dot(int_normal, L) * rs * int_object->s;
		}
	}
	if (modelType == 2) { //Blinn-Phong Model

		glm::dvec3 source = lightDetails.source; //Source of light ray

		glm::dvec3 L = source - int_point; //Vector from source to intersection point

		double lightDis = glm::dot(L, L);
		double intensity = lightDetails.power;// Dont divide by area, consider constant intensity and attenuate later

		L = glm::normalize(L); //Normalize L vector
		glm::dvec3 H = glm::normalize(-rayIn.direction + L); //Half Vector - Between L and Viewing Ray i.e. -rayIn

		double attenuation = 1 / (1+0.1*lightDis+0.05* lightDis* lightDis); //Calculate attenuation

		//Calculate diffuse lambertian component and update outColor
		if (glm::dot(int_normal, L) > 0)
		{
			outColor += int_object->diffuse * intensity * glm::dot(int_normal, L) * 0.45 * attenuation * lightDetails.solidAngle;
		}
		//Calculate specular phong component and update outColor
		if (glm::dot(int_normal, H) > 0)
		{
			outColor += int_object->specular * intensity * pow(glm::dot(int_normal, H),int_object->shininess) * 0.30 * attenuation * lightDetails.solidAngle;
		}
	}
}