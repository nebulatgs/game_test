#pragma once

#include <string>
#include <vector>
#include <memory>

#include "gl.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "sceneobject.hpp"
// typedef glm::mat4 Camera;


class Game
{

public:
	Game(int width, int height, std::string title);

public:
	void init(int width, int height, std::string title);
	void tick();

	void draw();
	void update();
	void input();

	bool closed();

public:
	int width;
	int height;

	GLuint spriteSheet;
	Camera camera;

private:
	GLFWwindow *window;
	double lastTime = 0.0;
	std::vector<std::shared_ptr<SceneObject>> renderObjects;
};