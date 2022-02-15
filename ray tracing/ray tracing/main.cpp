#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/gtc/type_ptr.hpp>

#include "Header/shader.h"
#include "Header/camera.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

//Callback functions for viewport, mouse, and keyboard
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyboard_input_callback(GLFWwindow* window, int key, int scancode, int action, int mod);
void mouse_input_callback(GLFWwindow* window, double x_pos, double y_pos);
void process_input(GLFWwindow* window);

//Camera movement variables
camera main_camera(glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f));
bool first_mouse = true;
double last_x = WINDOW_WIDTH / 2.0f;
double last_y = WINDOW_HEIGHT / 2.0f;


//Variables for updating frames
float delta_time = 0.0f;
float last_frame = 0.0f;

int main() {
	glfwInit();

	std::cout << "OpenGL version supported: " << glfwGetVersionString() << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sphere", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyboard_input_callback);
	glfwSetCursorPosCallback(window, mouse_input_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void keyboard_input_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void mouse_input_callback(GLFWwindow* window, double x_pos, double y_pos) {
	if (first_mouse) {
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}

	double x_diff = x_pos - last_x;
	double y_diff = last_y - y_pos;

	last_x = x_pos;
	last_y = y_pos;

	main_camera.process_mouse(x_diff, y_diff);
}
void process_input(GLFWwindow* window) {

	//WASD movment
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		main_camera.process_keyboard(FORWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		main_camera.process_keyboard(LEFT, delta_time);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		main_camera.process_keyboard(BACKWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		main_camera.process_keyboard(RIGHT, delta_time);

}