#include "headers/sprite.hpp"

Sprite::Sprite(int mapIndex, Shader shader) : mapIndex(mapIndex), shader(shader)
{
	initBuffers();
}

Sprite::Sprite(int mapIndex, const char *vertexPath, const char *fragmentPath) : mapIndex(mapIndex)
{
	initBuffers();
	shader.Compile(vertexPath, fragmentPath);
}

void Sprite::initBuffers()
{
	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f};

	GLuint VBO;
	GLuint VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
}

void Sprite::setTransform(glm::mat4 transform)
{
	this->transform = transform;
}

void Sprite::setTextureAtlas(GLuint atlasID)
{
	textureAtlas = atlasID;
}

void Sprite::update()
{
	shader.SetMatrix4("transform", transform, true);
	shader.SetInteger("tex", textureAtlas);
}

void Sprite::render()
{
	glBindVertexArray(VAO);
	shader.Use();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}