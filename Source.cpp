#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <glm/glm.hpp>

#include "ray.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "light.hpp"
#include "progressbar.hpp"
//#include "objImporter.hpp"

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;
const int MAXDEPTH = 1;
double CAMERA[] = { -4, 0, 0, 0, 0, 0, 0, 1, 0, 45 };
//glm::dvec3 Color[HEIGHT][WIDTH];

int main()
{

	Scene* scene = new Scene();
	//loadOBJ("./Models/Monkey.obj", scene);

	double f0;
	std::vector<double> v1;

	sphere* copperBall = new sphere();
	copperBall->center = glm::dvec3(1.5, 0,0);	
	copperBall->radius = 2;
	copperBall->diffuse = glm::dvec3(0.721, 0.450, 0.2);
	copperBall->specular = glm::dvec3(0.721, 0.450, 0.2);
	copperBall->n = 0.63660;
	copperBall->s = 1.0;
	copperBall->d = 0.0;

	v1.clear();
	v1.push_back(0.4);
	v1.push_back(0.4);
	copperBall->dVal.push_back(v1);
	v1[0] = 0.2;
	v1[1] = 0.6;
	copperBall->dVal.push_back(v1);

	copperBall->funcType = 2;
	f0=pow((copperBall->n-1)/(copperBall->n+1),2);
	copperBall->rd = f0 / 3.14159;
	copperBall->r_a = 3.14159*copperBall->rd;
	std::cout << copperBall->rd << "\n";
	scene->add(copperBall);

	sphere* obsidianBall = new sphere();
	obsidianBall->center = glm::dvec3(1.5, 0, 0);
	obsidianBall->radius = 2;
	obsidianBall->diffuse = glm::dvec3(0.180, 0.160, 0.227);
	obsidianBall->specular = glm::dvec3(0.180, 0.160, 0.227);
	obsidianBall->n = 1.45;
	obsidianBall->s = 0.8;
	obsidianBall->d = 0.2;

	v1.clear();
	v1.push_back(0.15);
	v1.push_back(1.0);
	obsidianBall->dVal.push_back(v1);

	obsidianBall->funcType = 1;
	f0 = pow((obsidianBall->n - 1) / (obsidianBall->n + 1), 2);
	obsidianBall->rd = f0 / 3.14159;
	obsidianBall->r_a = 3.14159 * obsidianBall->rd;
	std::cout << obsidianBall->rd << "\n";
	//scene->add(obsidianBall);

	sphere* rustBall = new sphere();
	rustBall->center = glm::dvec3(1.5, 0, 0);
	rustBall->radius = 2;
	rustBall->diffuse = glm::dvec3(0.717, 0.254, 0.054);
	rustBall->specular = glm::dvec3(0.717, 0.254, 0.054);
	rustBall->n = 2.42;
	rustBall->s = 0.2;
	rustBall->d = 0.8;

	v1.clear();
	v1.push_back(0.35);
	v1.push_back(1.0);
	rustBall->dVal.push_back(v1);

	rustBall->funcType = 1;
	f0 = pow((rustBall->n - 1) / (rustBall->n + 1), 2);
	rustBall->rd = f0 / 3.14159;
	rustBall->r_a = 3.14159 * rustBall->rd;
	std::cout << rustBall->rd << "\n";
	//scene->add(rustBall);

	sphere* redRubberBall = new sphere();
	redRubberBall->center = glm::dvec3(1.5, 0, 0);
	redRubberBall->radius = 2;
	redRubberBall->diffuse = glm::dvec3(1.0, 0, 0);
	redRubberBall->specular = glm::dvec3(1.0, 0, 0);
	redRubberBall->n = 2.42;
	redRubberBall->s = 0.4;
	redRubberBall->d = 0.6;

	v1.clear();
	v1.push_back(0.30);
	v1.push_back(1.0);
	redRubberBall->dVal.push_back(v1);

	redRubberBall->funcType = 1;
	f0 = pow((redRubberBall->n - 1) / (redRubberBall->n + 1), 2);
	redRubberBall->rd = f0 / 3.14159;
	redRubberBall->r_a = 3.14159 * redRubberBall->rd;
	std::cout << redRubberBall->rd << "\n";
	//scene->add(redRubberBall);

	light* light1 = new light();
	light1->attenuation = glm::dvec3(1, 0, 0);
	light1->source = glm::dvec3(-4, 0, 0);
	light1->type = 1;
	light1->color = glm::dvec3(1, 1, 0.9843);
	light1->power = 3000.0;
	light1->solidAngle = 0.001;
	scene->add(light1);

	light* light2 = new light();
	light2->attenuation = glm::dvec3(1, 0, 0);
	light2->source = glm::dvec3(-1, -1, -1);
	light2->type = 1;
	light2->color = glm::dvec3(1, 1, 0.9843);
	light2->power = 3000.0;
	light2->solidAngle = 0.001;
	scene->add(light2);

	scene->calcAmbientIntensity();
	//scene->add(light2);

	/*sphere* obsidianBall = new sphere();
	obsidianBall->center = glm::dvec3(2, -0.25, 0.75);
	obsidianBall->ambient = glm::dvec3(0.121, 0.278, 0.956);
	obsidianBall->radius = .2;
	obsidianBall->diffuse = glm::dvec3(.6, .3, .9);
	obsidianBall->emission = glm::dvec3(0, 0, 0);
	obsidianBall->shininess = .2;
	obsidianBall->specular = glm::dvec3(.3, .3, .3);
	obsidianBall->reflectivity = 0;
	//scene->add(obsidianBall);

	sphere* rustBall = new sphere();
	rustBall->center = glm::dvec3(7, .5, -2.75);
	rustBall->ambient = glm::dvec3(.54, .75, .69);
	rustBall->radius = 2;
	rustBall->diffuse = glm::dvec3(.2, .7, .3);
	rustBall->emission = glm::dvec3(0, 0, 0);
	rustBall->shininess = .2;
	rustBall->specular = glm::dvec3(.43, .13, .32);
	rustBall->reflectivity = 0.7;
	//scene->add(rustBall);

	sphere* redRubberBall = new sphere();
	redRubberBall->center = glm::dvec3(0, 0, -1);
	redRubberBall->ambient = glm::dvec3(0, 0, 0);
	redRubberBall->radius = 0.5;
	redRubberBall->diffuse = glm::dvec3(.54, .75, .69);
	redRubberBall->emission = glm::dvec3(0, 0, 0);
	redRubberBall->shininess = .5;
	redRubberBall->specular = glm::dvec3(.23, .43, .13);
	redRubberBall->reflectivity = 0;
	//scene->add(redRubberBall);

	/*triangle* tri1 = new triangle();
	tri1->ambient = glm::dvec3(0.321, 0.898, 0.368);
	tri1->diffuse = glm::dvec3(0.298, 0.941, 0.784);
	tri1->emission = glm::dvec3(0,0,0);
	tri1->shininess = .2;
	tri1->specular = glm::dvec3(.3, .3, .3);
	tri1->reflectivity = 0;
	tri1->v1 = glm::dvec3(25, -1,5 );
	tri1->v2 = glm::dvec3(25, -1,-5 );
	tri1->v3 = glm::dvec3(-5, -1,5 );
	tri1->normal = glm::normalize((glm::cross(tri1->v2 - tri1->v1, tri1->v3 - tri1->v1)));

	triangle* tri2 = new triangle();
	tri2->ambient = glm::dvec3(0.321, 0.898, 0.368);
	tri2->diffuse = glm::dvec3(.6, .3, .9);
	tri2->emission = glm::dvec3(0.321, 0.898, 0.368);
	tri2->shininess = .2;
	tri2->specular = glm::dvec3(.3, .3, .3);
	tri2->reflectivity = 0;
	tri2->v1 = glm::dvec3(-5, -1,-5 );
	tri2->v2 = glm::dvec3(-5, -1,5 );
	tri2->v3 = glm::dvec3(25 ,-1,-5 );
	tri2->normal = glm::normalize((glm::cross(tri2->v2 - tri2->v1, tri2->v3 - tri2->v1)));



	

	light* light3 = new light();
	light3->attenuation = glm::dvec3(1, .05, .005);
	light3->source = glm::dvec3(10, 0,-4);
	light3->type = 1;
	light3->color = glm::dvec3(0.321, 0.898, 0.368);
	light3->intensity = 1.0;

	light* light4 = new light();
	light4->attenuation = glm::dvec3(1, .05, .005);
	light4->source = glm::dvec3(10, 0, 4);
	light4->type = 1;
	light4->color = glm::dvec3(0.321, 0.898, 0.368);
	light4->intensity = 1.0;

	//scene->add(obsidianBall);
	//scene->add(redRubberBall);
	//scene->add(rustBall);


	//scene->add(tri1);
	//scene->add(tri2);

	//scene->add(light2);
	//scene->add(light3);
	//scene->add(light4);*/

	//SSAA Setup
	double jitterMatrix[5 * 2] = {
	0, 0,
	-1.0 / 4.0,  3.0 / 4.0,
	 3.0 / 4.0,  1.0 / 3.0,
	-3.0 / 4.0, -1.0 / 4.0,
	 1.0 / 4.0, -3.0 / 4.0,
	};
	const int samples = 1;

	double focallength = 6.0;
	double aperture = 0.05;
	double planedis = glm::length(glm::dvec3(CAMERA[0], CAMERA[1], CAMERA[2]) - glm::dvec3(CAMERA[3], CAMERA[4], CAMERA[5]));

	//ProgressBar
	progresscpp::ProgressBar progressBar(HEIGHT, 70, '#', '-');

	ofstream Output_Image("Output.ppm");
	if (Output_Image.is_open())
	{
		Output_Image << "P3\n" << WIDTH << " " << HEIGHT << " 255\n";

		for (int i = HEIGHT - 1; i >= 0; i--)
		{
			++progressBar;
			progressBar.display();

			for (int j = 0; j < WIDTH; j++)
			{
				glm::dvec3 pixColor = glm::dvec3(0, 0, 0);

				//Simple
				ray* temp = new ray();
				temp->raythrough(CAMERA, i , j , WIDTH, HEIGHT);
				pixColor = scene->intersectray(*temp, MAXDEPTH);
				delete temp;

				/*
				//Implemeted (Fixed) SSAA (Super Sampling Anti Aliasing)       //Randomize Later
				for (int sample = 0; sample < 5; ++sample) {

					ray* temp = new ray();
					temp->raythrough(CAMERA, i + jitterMatrix[2 * sample], j + jitterMatrix[2 * sample + 1], WIDTH, HEIGHT);
					//pixColor += scene->intersectray(*temp, 2);
					//std::cout << &temp<<"\n";
					glm::dvec3 focalPt = temp->origin + (focallength)*temp->direction;

					//Depth Of Field
					for (int divs = 0;divs < samples;divs++) {

						ray* rayInt = new ray();
						glm::dvec3 shift = glm::dvec3(((double)rand() / (RAND_MAX)) - 0.5, ((double)rand() / (RAND_MAX)) - 0.5, ((double)rand() / (RAND_MAX)) - 0.5);
						rayInt->origin = temp->origin + aperture * shift;
						rayInt->direction = glm::normalize(focalPt - rayInt->origin);
						//std::cout << &rayInt << "\n";
						//return 0;
						pixColor += scene->intersectray(*rayInt, MAXDEPTH);
						delete rayInt;
					}
					delete temp;
				}
				pixColor /= 5;*/
				//Color[i][j] = pixColor;
				Output_Image << (int)(255 * pixColor[0] / samples) << ' ' << (int)(255 * pixColor[1] / samples) << ' ' << (int)(255 * pixColor[2] / samples) << "\n";
			}
		}
		/*for (int i =HEIGHT-1;i >=0;i--)
		{
			for (int j = 0;j < WIDTH;j++)
			{
				Output_Image << (int)(255 * Color[i][j][0] / samples) << ' ' << (int)(255 * Color[i][j][1] / samples) << ' ' << (int)(255 * Color[i][j][2] / samples) << "\n";
			}
		}*/
		progressBar.done();
	}
	Output_Image.close();
	WinExec("cd ..", 1);
	WinExec("magick \"./Output.ppm\" \"./Output.png\"", 1);
	return 0;
}
