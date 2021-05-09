#pragma once

#include "gl.hpp"
#include "shader.hpp"
#include "sceneobject.hpp"

class Sprite : public SceneObject
{
public:
	Sprite(int mapIndex, const char *vertexPath, const char *fragmentPath);
	Sprite(int mapIndex, Shader shader);
	void render() override;
	void update() override;
	void setTransform(glm::mat4 transform) override;
	void setTextureAtlas(GLuint atlasID) override;

private:
	void initBuffers();
	void initTextures();

private:
	int width;
	int height;
	int mapIndex;
	Shader shader;
	GLuint VAO;
};