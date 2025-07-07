/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:29:15 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 20:42:54 by mbirou           ###   ########.fr       */
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

	Object object = ObjectLoader::loadObject(argv[1]);

	ShadowMap shadowMap;

	while (!glfwWindowShouldClose(window))
	{
		WindowManager.startRenderLoop();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 500.0f, shader, Window::width, Window::height);

		glm::mat4	orthogonalProj = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
		glm::mat4	lightView = glm::lookAt(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(object.center.x, object.center.y, object.center.z), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4	lightProj = orthogonalProj * lightView;

		object.movement(WindowManager.getContext());
		
		glEnable(GL_DEPTH_TEST);

		shadowMap.getShadows(lightProj, object);

		glViewport(0, 0, Window::width, Window::height);

		cat.Bind(shader);
		shader.Activate();

		shadowMap.sendToShader(shader);

		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uLightProjection"), 1, GL_FALSE, glm::value_ptr(lightProj));

		object.Render(shader);

		glDisable(GL_DEPTH_TEST);


		WindowManager.endRenderLoop();
	}
	shader.Delete();
	cat.Delete();
}
