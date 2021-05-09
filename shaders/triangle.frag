#version 300 es
precision mediump float;
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type) 
in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
    // FragColor = vec4(gl_FragCoord.xy, 1.0f, 1.0f) / vec4(500.0f);
	// FragColor = vec4(TexCoord, 1.0f, 1.0f);// / vec4(500.0f);
	FragColor = texture(tex, TexCoord) * vec4(2.0f);
} 