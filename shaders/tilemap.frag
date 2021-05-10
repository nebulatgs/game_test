#version 300 es
precision mediump float;
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type) 
in vec2 TexCoord;

uniform sampler2D tiles;
uniform sampler2D tileset;
uniform vec2 imgDims;

void main()
{
	vec2 tileOffset = texture(tiles, TexCoord.xy).xy;
	tileOffset *= 2.0;
	// if(tileOffset.x > 0.48 && tileOffset.x < 0.5)
	// {
	// 	tileOffset = vec2(0.0, 2.0);
	// }
	// else if(tileOffset.x > 0.29 && tileOffset.x < 0.31)
	// {
	// 	tileOffset = vec2(1.0, 2.0);
	// }
	// else if(tileOffset.x > 0.44 && tileOffset.x < 0.46)
	// {
	// 	tileOffset = vec2(2.0, 1.0);
	// }
	// else if(tileOffset.x > 0.9)
	// {
	// 	tileOffset = vec2(1.0, 1.0);
	// }
	// else
	// {
	// 	tileOffset = vec2(0.0, 0.0);
	// }
	vec4 fractCoords = texture(tileset, (fract(TexCoord * imgDims) / 3.0) + tileOffset / 3.0);
	FragColor = fractCoords;// * 100.0) / 100.0);
	// FragColor = texture(tileset, (FragColor.xy)*10.0);
	// FragColor = vec4(TexCoord, 0.0, 1.0);
} 