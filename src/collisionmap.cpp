#include "headers/collisionmap.hpp"

CollisionMap::CollisionMap(GLubyte *imageData, int imgWidth, int imgHeight)
{
	width = imgWidth;
	height = imgHeight;
    for (int i = 3; i < imgWidth * imgHeight * 4; i+=4)
	{
		colliders.insert({{i % imgWidth, i / imgWidth}, imageData[i]});
		// printf("%ul\n", colliders.size());
	}
	int a = 1;
}

bool CollisionMap::checkCollision(glm::ivec2 position)
{
    return colliders[{position.x, position.y}];
}