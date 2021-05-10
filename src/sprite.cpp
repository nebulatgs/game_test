#include "headers/sprite.hpp"
#include "headers/game.hpp"

Sprite::Sprite(int width, int height, int mapIndex, Game *game, Shader shader) : mapIndex(mapIndex), shader(shader), width(width), height(height)
{
	initBuffers();
	this->game = game;
	textureAtlas = 21;
}

Sprite::Sprite(int width, int height, int mapIndex, Game *game, const char *vertexPath, const char *fragmentPath) : mapIndex(mapIndex), width(width), height(height)
{
	initBuffers();
	this->game = game;
	shader.Compile(vertexPath, fragmentPath);
	textureAtlas = 2;
}

void Sprite::initBuffers()
{
	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f};

	GLuint VBO;
	// GLuint VAO;

	glGenBuffers(1, &VBO);

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
	// transform = this->transform * transform;
	transform = glm::scale(transform, glm::vec3((static_cast<float>(width) / static_cast<float>(game->width)), (static_cast<float>(height) / static_cast<float>(game->height)), 1));
	transform = glm::scale(transform, glm::vec3(0.05, 0.05, 1));
	transform = glm::translate(transform, {pos, 0});
	this->transform = transform;
}

void Sprite::setTextureAtlas(GLuint atlasID)
{
	textureAtlas = atlasID;
}

void Sprite::update()
{
	vel += acc;
	pos += vel;
	vel *= 0.8;
	acc *= 0.6;
	// vel.y -= 0.001;
	facing = vel;
	shader.SetMatrix4("transform", transform, true);
	shader.SetInteger("tex", textureAtlas);
	if(facing.x > 0)
		shader.SetVector2f("tile", {0, 1.0});
	else if (facing.x < 0)
		shader.SetVector2f("tile", {2.0, 1.0});
	else
		shader.SetVector2f("tile", {1.0, 1.0});
}

void Sprite::render()
{
	// glActiveTexture(GL_TEXTURE0 + textureAtlas);
	glBindVertexArray(VAO);
	shader.Use();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Sprite::move(glm::vec2 motion)
{
	// transform = glm::translate(transform, {motion, 0.0f});
	acc += motion;
}