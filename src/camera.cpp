#include "headers/camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
	transform = glm::mat4(10000.0f);
	// transform = glm::translate(transform, {28, 0, 0});
	// pos = glm::vec2(0);
	vel = glm::vec2(0);
	acc = glm::vec2(0);
}

void Camera::update()
{
	vel += acc;
	// pos += vel;
	transform = glm::translate(transform, glm::vec3(vel, 0));
	pos += vel;
	vel *= 0.9;
	acc *= 0.3;
}

void Camera::move(glm::vec2 motion)
{
	vel += motion;
}

glm::mat4 Camera::getTransform()
{
	return glm::scale(transform, glm::vec3(39, 39, 1));
}