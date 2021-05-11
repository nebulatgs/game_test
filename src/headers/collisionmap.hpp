#include <map>
#include <utility>
#include "gl.hpp"
#include <glm/glm.hpp>

class CollisionMap
{
public:
    CollisionMap() = default;
    CollisionMap(GLubyte *imageData, int imgWidth, int imgHeight);
    bool checkCollision(glm::ivec2 position);
	int width;
	int height;
private:
    std::map<std::pair<int, int>, bool> colliders;
};