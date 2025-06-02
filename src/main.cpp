/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:29:15 by mbirou            #+#    #+#             */
/*   Updated: 2025/06/01 16:35:28 by mbirou           ###   ########.fr       */
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

	Camera camera(glm::vec3(0.0f, 100.0f, 0.0f));

	GLuint uniID = glGetUniformLocation(shader.ID, "indexs");

	camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix", WWIDTH, WHEIGHT);



	double	lastTime;
	double	currentTime;
	double	delta;
	float	nbFrames;
	

	lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.17f, 0.13f, 0.07f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 10000.0f, shader, "camMatrix", WWIDTH, WHEIGHT);
		shader.Activate();

		cat.Bind();

		glfwSwapBuffers(window);
		
		currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		nbFrames++;
		if (delta >= 1.0)
		{
			// glfwGetWindowSize(window, &width, &height);
			// glViewport(0, 0, width, height);
			// glfwSetCursorPos(window, width / 2, height / 2);
			std::stringstream	fps;
			fps << "player pos: " << camera.Position.x << "; " << camera.Position.z << ", fps:";
			fps  << (nbFrames / delta);
			glfwSetWindowTitle(window, fps.str().c_str());
			nbFrames = 0;
			lastTime = currentTime;
		}

	}
	shader.Delete();
	cat.Delete();
}