#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include <GLFW/glfw3.h>
#include "Object.h"



using namespace std;
const string PROJECT_NAME = "GravSim";
const float SCREEN_WIDTH = 16000.0f;
const float SCREEN_HEIGHT = 9000.0f;
#define M_PI 3.14159265358979323846f
#define G 0.000000000066742f
GLFWwindow* startGLFW();


int main(void)
{
	GLFWwindow* window = startGLFW();

	if (!window) {
		cerr << "Failed to create GLFW window." << endl;
		return -1;
	}
	

	// Setup orthographic 2D projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1); // (0,0) is top-left
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float centerX = SCREEN_WIDTH / 2.0f;
	float centerY = SCREEN_HEIGHT / 2.0f;
	float radius = 50.0f;
	int res = 100;

	vector<Object> objects = {
		Object(vector<float>{4000.0f, 4000.0f}, vector<float>{0.0f, 50.0f},150.0f, 7.35 * pow(10,22)),
		Object(vector<float>{3000.0f, 3000.0f}, vector<float>{0.0f,-50.0f},150.0f, 7.35 * pow(10,22))

	};


	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);




		for (auto& object : objects) {


			for (auto& otherObject : objects) {
				if (&object == &otherObject) {continue;};
				float dx = otherObject.position[0] - object.position[0];
				float dy = otherObject.position[1] - object.position[1];
				float distance = sqrt(dx * dx + dy * dy);
				vector<float> direction = { dx / distance, dy / distance };
				distance *= 1000;
				float Gforce = (G * object.mass * otherObject.mass) / (distance * distance);
				float acc1 = Gforce / object.mass;
				vector<float> acc{ acc1 * direction[0],acc1 * direction[1] };
				object.accelerate(acc[0], acc[1]);
			}
			object.updatePos();
			object.DrawCircle();

			if (object.position[1]<radius || object.position[1] > SCREEN_HEIGHT - radius) {
				object.velocity[1] *= -0.95;
			}
			if (object.position[0]<radius || object.position[0] > SCREEN_WIDTH - radius) {
				object.velocity[0] *= -0.95;
			}
		}


		glfwSwapBuffers(window);
		this_thread::sleep_for(std::chrono::milliseconds(16));
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

GLFWwindow* startGLFW() {
	if (!glfwInit()) {
		cerr << "Failed to initialize GLFW" << endl;
		return nullptr;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, PROJECT_NAME.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window); // ÎÁßÇÀÒÅËÜÍÎ
	return window;
}


