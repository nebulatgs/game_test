#version 300 es
precision highp float;
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
// layout (location = 1) in vec2 aTexCoord;

out vec4 vertexColor; // specify a color output to the fragment shader
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
	// gl_Position.y += 0.25;
	// gl_Position.x += 1.0;
	TexCoord = aPos.xy;
	TexCoord /= 2.0;
	TexCoord -=  0.5;
	// TexCoord = fract(TexCoord);

    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}