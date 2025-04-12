/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:20:14 by mbirou            #+#    #+#             */
/*   Updated: 2025/04/12 23:04:30 by mbirou           ###   ########.fr       */
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

const unsigned int width = 800;
const unsigned int height = 800;

int	main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLfloat	vertices[] =
	{
		-0.5f,	0.0f,	0.5f,	1.0f,	0.0f,	0.0f,	0.0f, 0.0f,
		-0.5f,	0.0f,	-0.5f,	0.0f,	1.0f,	0.0f,	1.0f, 0.0f,
		0.5f,	0.0f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f, 0.0f,
		0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f, 0.0f,
		0.0f,	0.8f,	0.0f,	1.0f,	1.0f,	1.0f,	0.5f, 1.0f
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

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

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.17f, 0.13f, 0.07f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

		cat.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
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
