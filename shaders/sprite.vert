#version 300 es
precision mediump float;
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

out vec2 TexCoord;

uniform mat4 transform;
uniform vec2 tile;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
	TexCoord = aPos.xy + 1.0 + (tile * 2.0);
}