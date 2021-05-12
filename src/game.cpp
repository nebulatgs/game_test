#include "headers/sprite.hpp"
#include "headers/map.hpp"
#include "headers/game.hpp"
#include "headers/stb_image.h"
#include "headers/globals.hpp"
bool left = 0, right = 0, up = 0;
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT)
	{
		left = action;
	}
	if (key == GLFW_KEY_RIGHT)
	{
		right = action;
	}
	if (key == GLFW_KEY_UP)
	{
		up = action;
	}
}

Game::Game(int width, int height, std::string title) : camera()
{
	init(width, height, title);
	glfwSetKeyCallback(window, key_callback);
	scale = 16.0f;
	camera = Camera(this);
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
	// glViewport(0, 0, this->width, this->height);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	// glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClearColor(0.176, 0.204, 0.212, 1.0);

	stbi_set_flip_vertically_on_load(true);

	int imgWidth, imgHeight, tilesetWidth, tilesetHeight, nrChannels;
	GLubyte *data;

	data = stbi_load("../src/images/basic_tiles_big.png", &imgWidth, &imgHeight, &nrChannels, 0);
	tileset = loadTexture(data, imgWidth, imgHeight);
	stbi_image_free(data);
	tilesetWidth = imgWidth;
	tilesetHeight = imgHeight;

	data = stbi_load("../src/images/another_map4.png", &imgWidth, &imgHeight, &nrChannels, 0);
	spriteSheet = loadTexture(data, imgWidth, imgHeight);
	stbi_image_free(data);

	collision_map = CollisionMap(data, imgWidth, imgHeight);
	std::shared_ptr map = std::make_shared<Map>(imgWidth, imgHeight, tilesetWidth, tilesetHeight, 0, this, "../shaders/tilemap.vert", "../shaders/tilemap.frag");
	renderObjects.push_back(map);

	data = stbi_load("../src/images/Blob.png", &imgWidth, &imgHeight, &nrChannels, 0);
	playerImg = loadTexture(data, imgWidth, imgHeight);
	stbi_image_free(data);

	std::shared_ptr sprite = std::make_shared<Sprite>(imgWidth, imgHeight, 0, this, "../shaders/sprite.vert", "../shaders/sprite.frag");
	renderObjects.push_back(sprite);
	player = sprite;

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
	glGenerateMipmap(GL_TEXTURE_2D);
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
		// glm::mat4 scaleTrans = glm::scale(camera.getTransform(), glm::vec3(width / 35, width / 35, 1));
		i->setTransform(camera.getTransform());
		// i->setTextureAtlas(0);
		// i->update();
		i->render();
	}

	glfwSwapBuffers(window);
}

void Game::update()
{
	// if (player->pos.x + camera.pos.x > 0.0f)
	// {
	// 	printf("%f, %f\n", camera.pos.x, player->pos.x);
	// 	camera.move({-0.004f, 0.0f});
	// }
	// if (abs(player->pos.x + (camera.pos.x * 6.0f)) > 5.0f || abs(player->pos.y + (camera.pos.y * 6.0f)) > 5.0f)
	// {
	// 	// printf("%f, %f; %f\n", camera.pos.x, player->pos.x, abs(player->pos.x + (camera.pos.x * 6.0f)));
	// 	camera.move({-1.0f * (glm::normalize(player->pos + (camera.pos * 6.0f)) / 8000.0f)});
	// }
	if(player->pos.x + (camera.pos.x) < 2.0f)
	{
		camera.move({0.1f, 0.0});
	}
	else if(abs(player->pos.x + (camera.pos.x)) > (360.0f / scale) - 2.0f)
	{
		camera.move({-0.1f, 0.0});
	}

	printf("%f, %f\n", player->pos.x, camera.pos.x);
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
	if (left)
	{
		game->player->move(-0.093);
	}
	if (right)
	{
		game->player->move(0.093);
	}
	if (up)
	{
		game->player->jump(0.5);
	}
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

std::tuple<bool, bool, bool, bool> Game::checkCollision(glm::vec2 position, float radius)
{
	auto intPos = glm::ivec2(position);
	bool down = collision_map.checkCollision(position);
	return {0, down, 0, 0};
}
glm::ivec2 Game::getMapDims()
{
	return {collision_map.width, collision_map.height};
}