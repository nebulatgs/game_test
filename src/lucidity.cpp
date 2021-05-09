#include <iostream>

#include "headers/gl.hpp"
#include "headers/globals.hpp"
#include "headers/renderer.hpp"

void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main()
{
	renderer = new Renderer(640, 480, "Lucidity");
	glfwSetErrorCallback(error_callback);
	
	while (!renderer->closed())
	{
		renderer->tick();
	}
	glfwTerminate();
	exit(EXIT_SUCCESS);
}