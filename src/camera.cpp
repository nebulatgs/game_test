#include "headers/camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
	transform = glm::mat4(1.0f);
	// pos = glm::vec2(0);
	vel = glm::vec2(0);
	acc = glm::vec2(0);
}

void Camera::update()
{
	vel += acc;
	// pos += vel;
	transform = glm::translate(transform, glm::vec3(vel, 0));
	vel *= 0.9;
	acc *= 0.3;
}

void Camera::move(glm::vec2 motion)
{
	acc += motion;
}

glm::mat4 Camera::getTransform()
{
	return glm::scale(transform, glm::vec3(1, 1, 0));
}