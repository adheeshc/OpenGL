#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Texture Program
in vec2 texCoord;

// uniform object to store texture
uniform sampler2D tex0;

void main()
{
	FragColor = texture(tex0, texCoord);
}