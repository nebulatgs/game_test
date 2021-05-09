#include "headers/sprite.hpp"
#include "headers/map.hpp"
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	stbi_set_flip_vertically_on_load(true);

	int imgWidth, imgHeight, nrChannels;
	GLubyte *data;

	data = stbi_load("../src/images/tilemap.png", &imgWidth, &imgHeight, &nrChannels, 0);
	spriteSheet = loadTexture(data, imgWidth, imgHeight);
	stbi_image_free(data);

	std::shared_ptr map = std::make_shared<Map>(imgWidth, imgHeight, 0, this, "../shaders/tilemap.vert", "../shaders/tilemap.frag");
	renderObjects.push_back(map);

	data = stbi_load("../src/images/Blob.png", &imgWidth, &imgHeight, &nrChannels, 0);
	player = loadTexture(data, imgWidth, imgHeight);
	stbi_image_free(data);

	std::shared_ptr sprite = std::make_shared<Sprite>(imgWidth, imgHeight, 0, this, "../shaders/sprite.vert", "../shaders/sprite.frag");
	renderObjects.push_back(sprite);

	// glm::mat4 scaleTrans = glm::scale(camera.getTransform(), glm::vec3(2));
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	glfwSwapInterval(1);
}

GLuint Game::loadTexture(GLubyte *data, int imgWidth, int imgHeight)
{
	GLuint texture;
	glActiveTexture(GL_TEXTURE0 + textureCount++);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	return texture;
}

bool Game::closed()
{
	return glfwWindowShouldClose(window);
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int const rotation = glfwGetTime() * 100;

	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, spriteSheet);

	for (auto &&i : renderObjects)
	{
		glm::mat4 scaleTrans = glm::scale(camera.getTransform(), glm::vec3(40, 40, 1));
		i->setTransform(scaleTrans);
		// i->setTextureAtlas(0);
		// i->update();
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
		// i->render();
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