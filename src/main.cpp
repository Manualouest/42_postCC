/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:29:15 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 08:16:55 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Window/Window.hpp>

GLFWwindow	*window;

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);

	Window	WindowManager;

	window = WindowManager.getContext();

	Shader	shader("shaders/default.vert", "shaders/default.frag");

	// Texture	cat("textures/cat.bmp");
	Texture	cat("textures/cat.bmp");

	Camera camera(glm::vec3(0.0f, 1.0f, -10.0f));

	camera.Matrix(45.0f, 0.1f, 100.0f, shader, Window::width, Window::height);

	float width, height;

	Object test = ObjectLoader::loadObject(argv[1]);

	while (!glfwWindowShouldClose(window))
	{
		WindowManager.startRenderLoop();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 10000.0f, shader, Window::width, Window::height);
		shader.Activate();

		cat.Bind();

		test.movement(WindowManager.getContext());
		test.Render(shader);


		WindowManager.endRenderLoop();
	}
	shader.Delete();
	cat.Delete();
}
