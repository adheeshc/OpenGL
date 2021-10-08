#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {

	// Initialize GLFW
	glfwInit();

	//Specify OpenGL Version (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#	//Use Core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window of size 800 x 800 and name it MyWindow
	GLFWwindow* window = glfwCreateWindow(400, 225, "MyWindow", NULL, NULL);

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
	glViewport(0, 0, 400, 225); 

	//Specify background color (RGBA)
	glClearColor(1.0f, 0.64f, 0.0f, 1.0f);
	//Clear back buffer and assign color to it
	glClear(GL_COLOR_BUFFER_BIT);
	//Swap back and front buffers
	glfwSwapBuffers(window);

	//Main loop
	float prev_time = float(glfwGetTime());
	float angle = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		float time = float(glfwGetTime());
		if (time - prev_time >= 0.1f) {
			angle += 0.1f;
			prev_time = time;
		}
		glClearColor(float(sin(angle)), float(cos(angle)), float(tan(angle)), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Take care of all events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete window
	glfwDestroyWindow(window);

	//Terminate GLFW
	glfwTerminate();
	return 0;
}

