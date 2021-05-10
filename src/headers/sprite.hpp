#pragma once

#include "gl.hpp"
#include "shader.hpp"
#include "sceneobject.hpp"
class Game;

class Sprite : public SceneObject
{
public:
	Sprite(int width, int height, int mapIndex, Game *game, const char *vertexPath, const char *fragmentPath);
	Sprite(int width, int height, int mapIndex, Game *game, Shader shader);
	void render() override;
	void update() override;
	void move(glm::vec2 motion);
	void setTransform(glm::mat4 transform) override;
	void setTextureAtlas(GLuint atlasID) override;

private:
	void initBuffers();
	void initTextures();

private:
	int width;
	int height;
	int mapIndex;
	glm::vec2 facing;
	Shader shader;
	GLuint VAO;
};