#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"

#include "Shader.h"
#include "Renderer.h"

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit()) return -1;
 
	window = glfwCreateWindow(640, 480, "olá mundo", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) return -1; 

	float positions[] = {
		-1.0f,  1.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,
     1.0f,  1.0f,  0.0f,
  	 1.0f, -1.0f,  0.0f,
  	-1.0f,  1.0f, -1.0f,
  	-1.0f, -1.0f, -1.0f,
  	 1.0f,  1.0f, -1.0f,
  	 1.0f, -1.0f, -1.0f
	};

	unsigned int indices[] = {
		0, 2, 3, 0, 3, 1,
		2, 6, 7, 2, 7, 3,
		6, 4, 5, 6, 5, 7,
		4, 0, 1, 4, 1, 5,
		0, 4, 6, 0, 6, 2,
		1, 5, 7, 1, 7, 3,
	};

	VertexArray va;
	VertexBuffer vb(positions, 3*8*sizeof(float));

	VertexBufferLayout layout;
	layout.push<float>(3);
	va.addBuffer(vb, layout);

	IndexBuffer ib(indices, 36);

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0f));
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0f, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projection = glm::perspective(45.0f, 640.0f/480.0f, 0.0001f, 10.0f);

	Shader shader("../../res/shaders/Basic.shader");

	Renderer renderer;
	float rot = 1.0f;

	glClearColor(1, 1, 1, 1);
	while (!glfwWindowShouldClose(window))
	{
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 1.0f));
		shader.bind();	
		shader.setUniformMat4f("u_MVP", projection * view * model);

		renderer.clear();
		renderer.draw(va, ib, shader);

		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
