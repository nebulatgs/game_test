#include <iostream>
#include "headers/globals.hpp"

void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main()
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	GLFWwindow *window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!window)
	{
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	double time = glfwGetTime();
	glfwSwapBuffers(window);
	
	while (!glfwWindowShouldClose(window))
	{
		
	}
}