#include "headers/renderer.hpp"
#include "headers/stb_image.h"
#include "headers/globals.hpp"


float vertices[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		renderer->camera.move(glm::vec2(0.01, 0.0));
        // renderer->camera = glm::translate(renderer->camera, glm::vec3(0.01, 0.0, 0.0));
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		renderer->camera.move(glm::vec2(-0.01, 0.0));
        // renderer->camera = glm::translate(renderer->camera, glm::vec3(-0.01, 0.0, 0.0));
		// printf("OpenGL version: %s\n", glGetString(GL_VERSION));
}

Renderer::Renderer(int width, int height, std::string title) : camera()
{
	init(width, height, title);
	glfwSetKeyCallback(window, key_callback);
}

void Renderer::init(int width, int height, std::string title)
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

	VAOs.push_back(VAO);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	spriteShader.Compile("../shaders/triangle.vert", "../shaders/triangle.frag");
	
	int imgWidth, imgHeight, nrChannels;
	unsigned char *data = stbi_load("../src/images/test.jpg", &imgWidth, &imgHeight, &nrChannels, 0);
	// unsigned int texture;
	glGenTextures(1, &texture); 
	glBindTexture(GL_TEXTURE_2D, texture);  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	glfwSwapInterval(1);
}

bool Renderer::closed()
{
	return glfwWindowShouldClose(window);
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int const rotation = glfwGetTime() * 100;
	// camera = Camera(1.0f);
	// camera = glm::translate(camera, glm::vec3(0, static_cast<float>(rotation % 100) / 50.0f, 0.5));
	// camera = glm::rotate(camera, glm::radians(static_cast<float>(rotation)), glm::vec3(1.0, 0.5, 0.0));
	spriteShader.SetMatrix4("transform", camera.getTransform(), true);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	spriteShader.SetInteger("tex", 0);

	for (auto &&i : VAOs)
	{
		glBindVertexArray(i);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	glfwSwapBuffers(window);
}

void Renderer::update()
{
	glfwPollEvents();
	camera.update();
}

void Renderer::input()
{
}

void Renderer::tick()
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