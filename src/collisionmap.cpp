#include "headers/collisionmap.hpp"

CollisionMap::CollisionMap(GLubyte *imageData, int imgWidth, int imgHeight)
{
    for (int i = 3; i < imgWidth * imgHeight * 4; i+=4)
	{
		colliders.insert({{i % imgWidth, i / imgWidth}, imageData[i]});
	}
}

bool CollisionMap::checkCollision(glm::ivec2 position)
{
    return 0;
}