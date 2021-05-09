#pragma once

class SceneObject
{
public:
	virtual void render(){}
	virtual void update(){}
	virtual void setTransform(glm::mat4 transform){}
	virtual void setTextureAtlas(GLuint atlasID){}

protected:
	glm::mat4 transform = glm::mat4(1.0f);
	GLuint textureAtlas;
};