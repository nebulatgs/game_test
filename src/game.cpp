#include "headers/sprite.hpp"
#include "headers/game.hpp"
#include "headers/stb_image.h"
#include "headers/globals.hpp"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		game->camera.move(glm::vec2(0.01, 0.0));
		
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		game->camera.move(glm::vec2(-0.01, 0.0));
}

Game::Game(int width, int height, std::string title) : camera()
{
	init(width, height, title);
	glfwSetKeyCallback(window, key_callback);
}

void Game::init(int width, int height, std::string title)
{
	// Try to initialize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// Try to create a window
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GL_MAJOR_VERSION, 3);
	glfwWindowHint(GL_MINOR_VERSION, 1);
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
		exit(EXIT_FAILURE);

	// Load GL
	glfwMakeContextCurrent(window);
	gladLoadGL();

	// Set viewport
	glfwGetFramebufferSize(window, &this->width, &this->height);
	glViewport(0, 0, this->width, this->height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, this->width, this->height, 0, 1, -1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	renderObjects.push_back(std::make_shared<Sprite>(0, "../shaders/triangle.vert", "../shaders/triangle.frag"));

	int imgWidth, imgHeight, nrChannels;
	GLubyte *data = stbi_load("../src/images/test.jpg", &imgWidth, &imgHeight, &nrChannels, 0);
	glGenTextures(1, &spriteSheet);
	glBindTexture(GL_TEXTURE_2D, spriteSheet);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	glfwSwapInterval(1);
}

bool Game::closed()
{
	return glfwWindowShouldClose(window);
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int const rotation = glfwGetTime() * 100;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, spriteSheet);

	for (auto &&i : renderObjects)
	{
		i->setTransform(camera.getTransform());
		i->setTextureAtlas(0);
		i->update();
		i->render();
	}

	glfwSwapBuffers(window);
}

void Game::update()
{
	camera.update();
	for (auto &&i : renderObjects)
	{
		i->update();
		i->render();
	}
}

void Game::input()
{
	glfwPollEvents();
}

void Game::tick()
{
	double time = glfwGetTime();
	double deltaTime = time - lastTime;
	if (deltaTime >= 1.0 / 60.0)
	{
		lastTime = time;
		draw();
		update();
		input();
	}
}