#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int windowWidth = 1000, windowHeight = 1000;

float vertices[] = {
	// positions		// texture coords
	 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,		// top right		
	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		// bottom right
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		// bottom left
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f		// top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}

#ifdef _DEBUG

GLenum severityEnum[]{ GL_DEBUG_SEVERITY_HIGH_ARB, GL_DEBUG_SEVERITY_LOW_ARB, GL_DEBUG_SEVERITY_MEDIUM_ARB };
const char* severityText[]{ "HIGH","LOW","MEDIUM" };

GLDEBUGPROCARB x;

void __stdcall openGLDebugCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cerr << "OpenGL";
	for (int i = 0; i < 3; i++)
	{
		if (severity == severityEnum[i])
		{
			std::cerr << " Error " << severityText[i];
		}
	}
	std::cerr << ":\n" << message << "\n";
}
#endif


#ifdef _RELEASE
int WinMain(void*, void*, void*, int)
#endif
#ifdef _DEBUG
int main()
#endif
{
	glfwInit();
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Quick Start", 0, 0);

	if (window == NULL)
	{
		std::cout << "Error Creating Window\n";
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


#ifdef _DEBUG
	glEnable(GL_ARB_debug_output);
	glDebugMessageCallbackARB(openGLDebugCallback, 0);
#endif

	glEnable(GL_BLEND);// you enable blending function
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//Load Texture

	Texture texture1("assets/Dark.png");

	Texture texture2("assets/Matter.png");

	Shader shadey("shaders/simple.vs", "shaders/simple.fs");
	glUseProgram(shadey.id);


	glUniform1i(glGetUniformLocation(shadey.id, "tex"), 0);

	while (GLFW_FALSE == glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float gbValue = (sin(glfwGetTime()) + 1.0f)/12.0f + 0.5f;

		float yscale = 500.0f / (float)windowHeight;
		float xscale = 500.0f / (float)windowWidth;

		float speed = 0.5f;
		
		//range = 1 - half the height x 2 == 1 - height

		float ypos = sin(glfwGetTime() * speed) * (1.0 - (0.5 * yscale));
		float xpos = cos(glfwGetTime() * speed) * (1.0 - (0.5 * xscale));


		glm::mat4 MVP = glm::mat4(1.0f);
		MVP = glm::translate(MVP, glm::vec3(xpos, ypos, 0.0f));
		MVP = glm::scale(MVP, glm::vec3(xscale,yscale,0.0f));

		int colourLocation = glGetUniformLocation(shadey.id, "Colour");
		int MVPLocation = glGetUniformLocation(shadey.id, "MVP");

		glUniform4f(colourLocation, 1.0f, gbValue, gbValue, 1.3f - gbValue);
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1.id);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		MVP = glm::mat4(1.0f);
		MVP = glm::translate(MVP, glm::vec3(-xpos, -ypos, 0.0f));
		MVP = glm::scale(MVP, glm::vec3(xscale, yscale, 0.0f));
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture2.id);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}
	glfwTerminate();
	return 0;
}