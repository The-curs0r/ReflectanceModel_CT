/*
	* File:    Source.cpp
	*
	* Author1:  Akshay Tiwari (2018A7PS0201H)
	* Author2:  Mushkan Surekha  (2018B5A70477H)
	* Author3:  Mahesh Swaminathan  (2018A4PS0982H)
	* Date:     10-05-2020
	* Course:   Computer Graphics (IS F311)
	*
	* Summary of File:
	*
	*   Program to display a pleasant bedroom scene using GLFW and GLAD.
	*	Also has movement with either mouse or keyboard inputs as desired by the user.
*/
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <glm/glm.hpp>
#include <omp.h>
#include <cmath>

#include "ray.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "light.hpp"
#include "progressbar.hpp"
#include "initScene.hpp"

using namespace std;

const int WIDTH = 1920;///<Width of the output image
const int HEIGHT = 1080;///<Height of the output image
const int MAXDEPTH = 1;///<Maximum number of times a ray can strike an object
double CAMERA[] = { -4, 0, 0, 0, 0, 0, 0, 1, 0, 45 };///<Camera co-ordinates as [look_from_x,look_from_y,look_from_z,look_at_x,look_at_y,look_at_z,up_x,up_y,up_z,fovy]
glm::dvec3 Color[HEIGHT][WIDTH];///<Temporary array to store color of each pixel
Scene* scene = new Scene();///<New scene object which holds all objects and lights
double jitterMatrix[5 * 2] = {
	0, 0,
	-1.0 / 4.0,  3.0 / 4.0,
	 3.0 / 4.0,  1.0 / 3.0,
	-3.0 / 4.0, -1.0 / 4.0,
	 1.0 / 4.0, -3.0 / 4.0,
};///<Jitter Matrix for supersampling anti-aliasing
const int samples = 16;///<Number of samples for Depth-of-field calculations
double focallength = 6.0;///<Focal length of imaginary lens at camera for Depth-of-field calculations
double aperture = 0.05;///<Aperture size of imaginary lens at camera for Depth-of-field calculations
progresscpp::ProgressBar progressBar(HEIGHT, 70, '#', '-'); ///<Variable that handles the progress bar being displayed

/**
	*   int main()
	*
	*   Summary of main() function:
	*
	*       main function of our program
	*
	*   Parameters  :
	*
	*       None
	*
	*   Return Value :
	*
	*       int - exit code
	*
	*   Description :
	*
	*       main function of our program. Always the first to run.
	*       Calls the other functions and writes pixel data to ouyput .ppm file.
*/
int main()
{
	init(scene, 1);
	ofstream Output_Image("Output.ppm");
	if (Output_Image.is_open())
	{
		Output_Image << "P3\n" << WIDTH << " " << HEIGHT << " 255\n";

		for (int i = HEIGHT - 1; i >= 0; i--)
		{
			++progressBar;
			progressBar.display();
#pragma omp parallel for
			for (int j = 0; j < WIDTH; j++)
			{
				glm::dvec3 pixColor = glm::dvec3(0, 0, 0);

				//Simple
				/*
				ray* temp = new ray();
				temp->raythrough(CAMERA, i , j , WIDTH, HEIGHT);
				pixColor = scene->intersectray(*temp, MAXDEPTH);
				delete temp;
				*/

				//With Anti-aliasing and DOF 
				for (int sample = 0; sample < 5; ++sample) {

					ray* temp = new ray();
					temp->raythrough(CAMERA, i + jitterMatrix[2 * sample], j + jitterMatrix[2 * sample + 1], WIDTH, HEIGHT);
					glm::dvec3 focalPt = temp->origin + (focallength)*temp->direction;
					for (int divs = 0;divs < samples;divs++) {
						ray* rayInt = new ray();
						glm::dvec3 shift = glm::dvec3(((double)rand() / (RAND_MAX)) - 0.5, ((double)rand() / (RAND_MAX)) - 0.5, ((double)rand() / (RAND_MAX)) - 0.5);
						rayInt->origin = temp->origin + aperture * shift;
						rayInt->direction = glm::normalize(focalPt - rayInt->origin);
						pixColor += scene->intersectray(*rayInt, MAXDEPTH);
						delete rayInt;
					}
					delete temp;
				}
				pixColor /= 5;
				Color[i][j] = pixColor;
			}
		}
		for (int i =HEIGHT-1;i >=0;i--)
		{
			for (int j = 0;j < WIDTH;j++)
			{
				Output_Image << (int)(255 * Color[i][j][0] / samples) << ' ' << (int)(255 * Color[i][j][1] / samples) << ' ' << (int)(255 * Color[i][j][2] / samples) << "\n";
			}
		}
		progressBar.done();
	}
	Output_Image.close();
	WinExec("cd ..", 1);
	WinExec("magick \"./Output.ppm\" \"./Output.png\"", 1);
	return 0;
}
