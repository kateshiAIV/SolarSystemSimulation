#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include <GLFW/glfw3.h>

using namespace std;
const string PROJECT_NAME = "GravSim";
const float SCREEN_WIDTH = 1280.0f;
const float SCREEN_HEIGHT = 720.0f;
#define M_PI 3.14159265358979323846
GLFWwindow* startGLFW();
void DrawCircle(float centerX, float centerY, float radius, int res);

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

	vector<float> position = { centerX, centerY};
	vector<float> velocity = { 0.0f, 0.0f };


	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLE_FAN);
		DrawCircle(position[0],position[1], radius, res);

		position[0] += velocity[0];
		position[1] += velocity[1];
		velocity[0] += +9.81f / 20.0f;
		velocity[1] += +9.81f / 20.0f;


		if (position[1]<radius || position[1] > SCREEN_HEIGHT-radius) {
			velocity[1] *= -0.95;
		}
		if (position[0]<radius || position[0] > SCREEN_WIDTH-radius) {
			velocity[0] *= -0.95;
		}



		glEnd();

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

void DrawCircle(float centerX, float centerY, float radius, int res) {
	glVertex2f(centerX, centerY);
	for (int i = 0; i <= res; i++) {
		float angle = 2.0f * M_PI * (static_cast<float>(i) / res);
		float x = centerX + cos(angle) * radius;
		float y = centerY + sin(angle) * radius;
		glVertex2f(x, y);
	}
}
