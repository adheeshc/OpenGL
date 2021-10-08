#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {

	// Initialize GLFW
	glfwInit();

	//Specify OpenGL Version (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#	//Use Core profile
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

	// Create Vertex Shader Object and get its reference, Attach Vertex Shader source to the Vertex Shader Object, Compile the Vertex Shader into machine code
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference, Attach Fragment Shader source to the Fragment Shader Object, Compile the Fragment Shader into machine code
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference, Attach Vertex and Fragment Shader source to the Shader Program, Wrap-up/Link all the shaders together into the Shader Program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Equilateral Triangle
	/*GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f,-0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f,0.5f * float(sqrt(3)) * 2 / 3,0.0f
	};*/

	// Square 
	/*GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};*/

	// Square 
	GLfloat vertices[] = {
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -
	};


	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO[1], VBO[1];
	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO[0]);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER, Introduce the vertices into the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO, Enable the Vertex Attribute so that OpenGL knows to use it
	
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Specify background color (RGBA)
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//Clear back buffer and assign color to it
	glClear(GL_COLOR_BUFFER_BIT);
	//Swap back and front buffers
	glfwSwapBuffers(window);

	//Main loop
	while (!glfwWindowShouldClose(window)) {
		
		
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO[0]);
		// Draw the triangle using the GL_TRIANGLES primitive
		
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 0, 4);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Take care of all events
		glfwPollEvents();
	}

	// Delete all the objects created
	glDeleteVertexArrays(1, VAO);
	glDeleteBuffers(1, VBO);
	glDeleteProgram(shaderProgram);

	// Delete window
	glfwDestroyWindow(window);
	

	//Terminate GLFW
	glfwTerminate();
	return 0;
}