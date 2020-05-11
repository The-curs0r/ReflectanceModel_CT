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
	*  File containing some predefined scenes.
*/
#include <iostream>
#include <stdio.h>
#include <vector>
#include "light.hpp"
#include "scene.hpp"
#include "object.hpp"
#include "lightingModel.hpp"
/**
	*   void init(Scene* scene, int sceneId)
	*
	*   Summary of init() function:
	*
	*       Initializes the scene to one of the predefined scenes.
	*
	*   Parameters  :
	*
	*       Scene* scene: Pointer to scene variable
	*		int sceneId: Variable to identify which scene to load
	*
	*   Return Value :
	*
	*       None
	*
	*   Description :
	*
	*       Loads the scene corresponding to given sceneId.
	*/
void init(Scene* scene, int sceneId) {
	
	double f0;///<Temporary variable
	std::vector<double> v1;///<Temporary variable

	if (sceneId == 1) {
		sphere* copperBall = new sphere();
		copperBall->center = glm::dvec3(1.5, 0, 0);
		copperBall->radius = 2;
		copperBall->diffuse = glm::dvec3(0.721, 0.450, 0.2);
		copperBall->specular = glm::dvec3(0.721, 0.450, 0.2);
		copperBall->n = 0.63660;
		copperBall->s = 1.0;
		copperBall->d = 0.0;
		copperBall->shininess = 27.0;
		v1.clear();
		v1.push_back(0.4);
		v1.push_back(0.4);
		copperBall->dVal.push_back(v1);
		v1[0] = 0.2;
		v1[1] = 0.6;
		copperBall->dVal.push_back(v1);
		copperBall->funcType = 2;
		f0 = pow((copperBall->n - 1) / (copperBall->n + 1), 2);
		copperBall->rd = f0 / 3.14159;
		copperBall->r_a = 3.14159 * copperBall->rd;
		std::cout << copperBall->rd << "\n";
		scene->add(copperBall);

		light* light1 = new light();
		light1->source = glm::dvec3(-4, 0, 0);
		light1->power = 3000.0;
		light1->solidAngle = 0.001;
		scene->add(light1);

		light* light2 = new light();
		light2->source = glm::dvec3(-1, -1, -1);
		light2->power = 3000.0;
		light2->solidAngle = 0.001;
		scene->add(light2);

		scene->calcAmbientIntensity();
		scene->ambientIntensity *= 2.0;
	}
	else if (sceneId == 2) {
		std::cout << "hewheha";
		sphere* redRubberBall = new sphere();
		redRubberBall->center = glm::dvec3(1.5, 0, 0);
		redRubberBall->radius = 2;
		redRubberBall->diffuse = glm::dvec3(1.0, 0, 0);
		redRubberBall->specular = glm::dvec3(1.0, 0, 0);
		redRubberBall->n = 2.42;
		redRubberBall->s = 0.4;
		redRubberBall->d = 0.6;
		redRubberBall->shininess = 5.0;

		v1.clear();
		v1.push_back(0.30);
		v1.push_back(1.0);
		redRubberBall->dVal.push_back(v1);

		redRubberBall->funcType = 1;
		f0 = pow((redRubberBall->n - 1) / (redRubberBall->n + 1), 2);
		redRubberBall->rd = f0 / 3.14159;
		redRubberBall->r_a = 3.14159 * redRubberBall->rd;
		std::cout << redRubberBall->rd << "\n";
		scene->add(redRubberBall);

		light* light1 = new light();
		light1->source = glm::dvec3(-4, 0, 0);
		light1->power = 3000.0;
		light1->solidAngle = 0.001;
		scene->add(light1);

		light* light2 = new light();
		light2->source = glm::dvec3(-1, -1, -1);
		light2->power = 3000.0;
		light2->solidAngle = 0.001;
		scene->add(light2);

		scene->calcAmbientIntensity();
	}
	else if(sceneId==3){
		sphere* rustBall = new sphere();
		rustBall->center = glm::dvec3(1.5, 0, 0);
		rustBall->radius = 2;
		rustBall->diffuse = glm::dvec3(0.717, 0.254, 0.054);
		rustBall->specular = glm::dvec3(0.717, 0.254, 0.054);
		rustBall->n = 2.42;
		rustBall->s = 0.2;
		rustBall->d = 0.8;
		rustBall->shininess = 5.0;

		v1.clear();
		v1.push_back(0.35);
		v1.push_back(1.0);
		rustBall->dVal.push_back(v1);

		rustBall->funcType = 1;
		f0 = pow((rustBall->n - 1) / (rustBall->n + 1), 2);
		rustBall->rd = f0 / 3.14159;
		rustBall->r_a = 3.14159 * rustBall->rd;
		std::cout << rustBall->rd << "\n";
		scene->add(rustBall);

		light* light1 = new light();
		light1->source = glm::dvec3(-4, 0, 0);
		light1->power = 3000.0;
		light1->solidAngle = 0.001;
		scene->add(light1);

		light* light2 = new light();
		light2->source = glm::dvec3(-1, -1, -1);
		light2->power = 3000.0;
		light2->solidAngle = 0.001;
		scene->add(light2);

		scene->calcAmbientIntensity();
	}
	else if (sceneId == 4) {
		sphere* obsidianBall = new sphere();
		obsidianBall->center = glm::dvec3(1.5, 0, 0);
		obsidianBall->radius = 2;
		obsidianBall->diffuse = glm::dvec3(0.180, 0.160, 0.227);
		obsidianBall->specular = glm::dvec3(0.180, 0.160, 0.227);
		obsidianBall->n = 1.45;
		obsidianBall->s = 0.8;
		obsidianBall->d = 0.2;
		obsidianBall->shininess = 5.0;

		v1.clear();
		v1.push_back(0.15);
		v1.push_back(1.0);
		obsidianBall->dVal.push_back(v1);

		obsidianBall->funcType = 1;
		f0 = pow((obsidianBall->n - 1) / (obsidianBall->n + 1), 2);
		obsidianBall->rd = f0 / 3.14159;
		obsidianBall->r_a = 3.14159 * obsidianBall->rd;
		std::cout << obsidianBall->rd << "\n";
		scene->add(obsidianBall);

		light* light1 = new light();
		light1->source = glm::dvec3(-4, 0, 0);
		light1->power = 3000.0;
		light1->solidAngle = 0.001;
		scene->add(light1);

		light* light2 = new light();
		light2->source = glm::dvec3(-1, -1, -1);
		light2->power = 3000.0;
		light2->solidAngle = 0.001;
		scene->add(light2);

		scene->calcAmbientIntensity();
	}
}