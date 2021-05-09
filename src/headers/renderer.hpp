#pragma once

#include <string>
#include <vector>

#include "gl.hpp"
#include "shader.hpp"



class Renderer
{

public:
	Renderer(int width, int height, std::string title);

public:
	GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);
	void init(int width, int height, std::string title);
	void tick();

	void draw();
	void update();
	void input();
	// double time();
	bool closed();

public:
	int width;
	int height;
	Shader tileShader;
	Shader spriteShader;
	std::vector<GLuint> VAOs;

private:
	GLFWwindow *window;
	double lastTime = 0.0;
};