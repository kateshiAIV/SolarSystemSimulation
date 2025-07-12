#include <iostream>
#include <vector>
#include <string>
#include <cmath>
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

	vector<float> position = { centerX, 0.0f};


	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLE_FAN);
		DrawCircle(position[0],position[1], radius, res);
		position[1] += 1.0f;
		glEnd();

		glfwSwapBuffers(window);
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
