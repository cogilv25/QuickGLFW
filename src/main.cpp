#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Effect.h"
#include "Texture.h"
#include "ModelBuilder.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


int windowWidth = 1000, windowHeight = 1000;


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

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);


	ModelBuilder builder;

	Model* model1 = builder.buildPlane(1.0f, 1.0f, 0.0f);

	//Load Texture

	Texture texture1("assets/Dark.png");

	Texture texture2("assets/Matter.png");

	Shader shadey1("shaders/simple.fs", GL_FRAGMENT_SHADER);
	Shader shadey2("shaders/simple.vs", GL_VERTEX_SHADER);
	Effect effect;
	effect.addShader(shadey1);
	effect.addShader(shadey2);
	effect.build();
	glUseProgram(effect.id);


	glUniform1i(glGetUniformLocation(effect.id, "tex"), 0);

	glBindVertexArray(model1->id);

	while (GLFW_FALSE == glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float yscale = 500.0f / (float)windowHeight;
		float xscale = 500.0f / (float)windowWidth;

		float speed = 0.5f;
		
		//range = 1 - half the height x 2 == 1 - height

		float ypos = sin(glfwGetTime() * speed) * (1.0 - (0.5 * yscale));
		float xpos = cos(glfwGetTime() * speed) * (1.0 - (0.5 * xscale));


		glm::mat4 MVP = glm::mat4(1.0f);
		MVP = glm::translate(MVP, glm::vec3(xpos, ypos, 0.0f));
		MVP = glm::scale(MVP, glm::vec3(xscale,yscale,0.0f));

		int colourLocation = glGetUniformLocation(effect.id, "Colour");
		int MVPLocation = glGetUniformLocation(effect.id, "MVP");

		glUniform4f(colourLocation, 0.0f, 1.0f, 0.0f, 1.0f);
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