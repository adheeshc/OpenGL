#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

//GLfloat vertices[] =
//{ //    COORDINATES      /     COLORS          / TexCoord
//	-0.5f, -0.5f, 0.0f,    1.0f, 0.0f,  0.0f,	0.0f, 0.0f,	// Lower left corner
//	-0.5f,  0.5f, 0.0f,    0.0f, 1.0f,  0.0f,	0.0f, 3.0f,	// Upper left corner
//	 0.5f,  0.5f, 0.0f,    0.0f, 0.0f,  1.0f,	3.0f, 3.0f,	// Upper right corner
//	 0.5f, -0.5f, 0.0f,    1.0f, 1.0f,  1.0f,	3.0f, 0.0f	// Lower right corner
//};
//
//
//GLuint indices[] = {
//	0, 2, 1, //Upper Triangle
//	0, 3, 2, //Lower Triangle
//};

GLfloat vertices[] =
{ //    COORDINATES      /     COLORS          / TexCoord
	-0.5f, -0.5f, 0.0f,    1.0f, 0.0f,  0.0f,	-1.0f, -1.0f,	// Lower left corner
	 0.0f,  0.5f, 0.0f,    0.0f, 1.0f,  0.0f,	 0.5f,  2.0f,	// Upper left corner
	 0.5f, -0.5f, 0.0f,    0.0f, 0.0f,  1.0f,	 2.0f, -1.0f	// Upper right corner
};

GLuint indices[] = {
	0, 2, 1, //Upper Triangle
};


int main() {
	// Initialize GLFW
	glfwInit();

	//Specify OpenGL Version (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Use Core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window of size 800 x 800 and name it MyWindow
	GLFWwindow* window = glfwCreateWindow(800, 800, "MyWindow", NULL, NULL);

	// Error Check if window creation fails
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce window into current context
	glfwMakeContextCurrent(window);

	// Load GLAD to configure OpenGL
	gladLoadGL();

	//Specify viewport of OpenGL in the window
	glViewport(0, 0, 800, 800); 

	// Create  reference container for Vertex Shader Object  
	Shader shaderProgram("default.vert", "default.frag");

	// Create reference containers for the Vartex Array Object, the Vertex Buffer Object and Element Buffer Object
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO	EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();	

	// Get ID of uniform called scale
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture
	
	//Texture popCat("Resources/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture awesomeFace("Resources/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture Lena("Resources/lena.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	Lena.texUnit(shaderProgram, "tex0", 0);

	//Main loop
	while (!glfwWindowShouldClose(window)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		glUniform1f(uniID, 0.5f);
		Lena.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Take care of all events
		glfwPollEvents();
	}

	// Delete all the objects created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	Lena.Delete();
	shaderProgram.Delete();

	// Delete window
	glfwDestroyWindow(window);
	
	//Terminate GLFW
	glfwTerminate();
	return 0;
}