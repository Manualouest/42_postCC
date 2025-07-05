/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:29:15 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/05 19:06:44 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Window/Window.hpp>

GLFWwindow	*window;

int main(int argc, char **argv)
{
	Window	WindowManager;

	window = WindowManager.getContext();

	Shader	shader("shaders/default.vert", "shaders/default.frag");

	Texture	cat("textures/cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cat.texUnit(shader, "tex0", 0);

	Camera camera(glm::vec3(0.0f, 1.0f, -1.0f));

	camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix", WWIDTH, WHEIGHT);



	// GLfloat	vertices[] =
	// {
	// 	-0.5f,	0.0f,	0.5f,	0.0f, 0.0f,
	// 	-0.5f,	0.0f,	-0.5f,	1.0f, 0.0f,
	// 	0.5f,	0.0f,	-0.5f,	0.0f, 0.0f,
	// 	0.5f,	0.0f,	0.5f,	1.0f, 0.0f,
	// 	0.0f,	0.8f,	0.0f,	0.5f, 1.0f
	// };

	// GLuint indices[] =
	// {
	// 	0, 2, 1,
	// 	0, 2, 3,
	// 	0, 1, 4,
	// 	1, 2, 4,
	// 	2, 3, 4,
	// 	3, 0, 4
	// };

	// VAO VAO1(1);
	// VAO1.Bind();

	// VBO	VBO1(vertices, sizeof(vertices));
	// EBO	EBO1(indices, sizeof(indices));

	// VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	// VAO1.linkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// VAO1.Unbind();
	// VBO1.Unbind();
	// EBO1.Unbind();

	Object test = ObjectLoader::loadObject(argv[1]);

	while (!glfwWindowShouldClose(window))
	{
		WindowManager.startRenderLoop();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 10000.0f, shader, "camMatrix", WWIDTH, WHEIGHT);
		shader.Activate();

		cat.Bind();


		test.Render();
		// VAO1.Bind();
		// glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);



		WindowManager.endRenderLoop();
	}
	shader.Delete();
	cat.Delete();
}
