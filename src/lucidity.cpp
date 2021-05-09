#include <iostream>

#include "headers/gl.hpp"
#include "headers/globals.hpp"
#include "headers/game.hpp"

void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main()
{
	game = new Game(640, 480, "Lucidity");
	glfwSetErrorCallback(error_callback);
	
	while (!game->closed())
	{
		game->tick();
	}
	glfwTerminate();
	exit(EXIT_SUCCESS);
}