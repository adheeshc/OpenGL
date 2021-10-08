#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	//Assign texture type to a texture object
	type = texType;
	
	// Store width, height and num color channels of image
	int widthImg, heightImg, numColch;

	//flips image so that Y-axis starts at top
	stbi_set_flip_vertically_on_load(true);

	//Read image from file
	unsigned char* myImage = stbi_load(image, &widthImg, &heightImg, &numColch, 0);

	//Generate OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns texture to texture object
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures type of algorithm used to make image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way texture repeats 
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Extra lines if GL_CLAMP_TO_BORDER used
	float flatColor[] = { 0.8f, 0.76f, 0.7f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	//Assigns image to OpenGL texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, myImage);
	// Generate MipMaps
	glGenerateMipmap(texType);

	//Deletes stored image data
	stbi_image_free(myImage);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
	//Activate shader before changing value of a uniform
	shader.Activate();
	glUniform1i(tex0Uni, unit);
}

void Texture::Bind(){
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}