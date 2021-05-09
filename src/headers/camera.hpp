#include "globals.hpp"

// typedef glm::mat4 Camera;
class Camera
{
public:
	Camera();
	void update();
	void move(glm::vec2 motion);
	glm::mat4 getTransform();
public:
	glm::mat4 transform = glm::mat4(1.0f);
	// glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;
};