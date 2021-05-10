#include <map>
#include "gl.hpp"
#include <glm/glm.hpp>

class CollisionMap
{
public:
    CollisionMap() = default;
    CollisionMap(GLubyte *imageData, int imgWidth, int imgHeight);
    bool checkCollision(glm::ivec2 position);

private:
    std::map<glm::ivec2, bool> colliders;
};