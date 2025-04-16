/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:20:14 by mbirou            #+#    #+#             */
/*   Updated: 2025/04/16 16:18:49 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION

#include <includes.hpp>
#include <Shaders/Shaders.hpp>
#include <Buffers/VBO.hpp>
#include <Buffers/VAO.hpp>
#include <Buffers/EBO.hpp>
#include <Texture/Texture.hpp>
#include <Camera/Camera.hpp>

int width = 1000;
int height = 1000;

void framebuffer_size_callback(GLFWwindow* window, int nWidth, int nHeight)
{
	width = nWidth;
	height = nHeight;
    glViewport(0, 0, width, height);
}

int	main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glm::vec3 instanceIndex[] =
	{
		glm::vec3{1, 2, 0},
		glm::vec3{0, 4, 1},
		glm::vec3{2, 6, 0},
		glm::vec3{0, 8, 2}
	};
	
	GLfloat	vertices_Base[] =
	{
		-0.5f,	0.0f,	0.5f,	1.0f,	0.0f,	0.0f,	0.0f, 0.0f,
		-0.5f,	0.0f,	-0.5f,	0.0f,	1.0f,	0.0f,	1.0f, 0.0f,
		0.5f,	0.0f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f, 0.0f,
		0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f, 0.0f,
		0.0f,	2.0f,	0.0f,	1.0f,	1.0f,	1.0f,	0.5f, 1.0f
	};

	GLfloat	vertices[40 * 10000]; // 10000 elements of size 40(vertices_Base)

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			for (int n = 0; n < 40; ++n) // 40 cause vertices_Base has 40 things
				vertices[(i * 100 + j) * 40 + n] = vertices_Base[n];
			vertices[(i * 100 + j) * 40] += 1.0f * j;
			vertices[(i * 100 + j) * 40 + 8] += 1.0f * j;
			vertices[(i * 100 + j) * 40 + 16] += 1.0f * j;
			vertices[(i * 100 + j) * 40 + 24] += 1.0f * j;
			vertices[(i * 100 + j) * 40 + 32] += 1.0f * j;

			vertices[(i * 100 + j) * 40 + 2] += 1.0f * i;
			vertices[(i * 100 + j) * 40 + 10] += 1.0f * i;
			vertices[(i * 100 + j) * 40 + 18] += 1.0f * i;
			vertices[(i * 100 + j) * 40 + 26] += 1.0f * i;
			vertices[(i * 100 + j) * 40 + 34] += 1.0f * i;
		}
	}

	GLuint indices_Base[] =
	{
		0, 2, 1,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	GLuint	indices[18 * 10000]; // 10000 elemets of size 18 (size of indices_Base)

	for (int i = 0; i < 10000; ++i)
	{
		for (int j = 0; j < 18; ++j) // 18 for size of indices_Base
			indices[i * 18 + j] = indices_Base[j] + 5 * i;
	}

	GLFWwindow	*window = glfwCreateWindow(width, height, "ft_vox", NULL, NULL);
	if (!window)
	{
		std::cout << "Erm What Da Hell" << std::endl;
		glfwTerminate();
		return (-1);
	}
	
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	Shader	shader("shaders/default.vert", "shaders/default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO	VBO1(vertices, sizeof(vertices));
	EBO	EBO1(indices, sizeof(indices));

	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Texture	cat("textures/cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cat.texUnit(shader, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

	GLuint uniID = glGetUniformLocation(shader.ID, "indexs");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPos(window, width / 2, height / 2);

	camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix", width, height);

	double	lastTime;
	double	currentTime;
	double	delta;
	float	nbFrames;
	

	lastTime = glfwGetTime();

	// glfwSwapInterval(0); //danger

	while (!glfwWindowShouldClose(window))
	{


		// glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
		// glfwGetWindowSize(window, &width, &height);
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.17f, 0.13f, 0.07f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 10000.0f, shader, "camMatrix", width, height);
		shader.Activate();
		
		glUniform3fv(uniID, 4, reinterpret_cast<GLfloat*>(instanceIndex));
		
		cat.Bind();
		VAO1.Bind();
		// glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
		
		glDrawElementsInstanced(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0, 4);

		glfwSwapBuffers(window);
		
		currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		nbFrames++;
		if (delta >= 1.0)
		{
			std::stringstream	fps;
			fps  << (nbFrames / delta);
			glfwSetWindowTitle(window, fps.str().c_str());
			nbFrames = 0;
			lastTime = currentTime;
		}

	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shader.Delete();
	cat.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}



