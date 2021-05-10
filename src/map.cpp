#include "headers/map.hpp"
#include "headers/game.hpp"

Map::Map(int width, int height, int mapIndex, Game *game, Shader shader) : mapIndex(mapIndex), shader(shader), width(width), height(height)
{
	initBuffers();
	this->game = game;
	textureAtlas = 0;
}

Map::Map(int width, int height, int mapIndex, Game *game, const char *vertexPath, const char *fragmentPath) : mapIndex(mapIndex), width(width), height(height)
{
	initBuffers();
	this->game = game;
	shader.Compile(vertexPath, fragmentPath);
	textureAtlas = 0;
}

void Map::initBuffers()
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

void Map::setTransform(glm::mat4 transform)
{
	transform = glm::scale(transform, glm::vec3((static_cast<float>(width) / static_cast<float>(game->width)), (static_cast<float>(height) / static_cast<float>(game->height)), 1));
	// transform = glm::scale(transform, {static_cast<float>(height) / static_cast<float>(width), 1.0f, 1.0f});
	// this->position = transform;
	this->transform = transform;
}

void Map::setTextureAtlas(GLuint atlasID)
{
	textureAtlas = atlasID;
}

void Map::update()
{
	shader.SetMatrix4("transform", transform, true);
	shader.SetInteger("tileset", textureAtlas);
	shader.SetInteger("tiles", textureAtlas + 1);
}

void Map::render()
{
	glBindVertexArray(VAO);
	shader.Use();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}