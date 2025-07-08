/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:29:15 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/08 20:35:41 by mbirou           ###   ########.fr       */
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

	Shader	objectShader("shaders/default.vert", "shaders/default.frag");
	Shader	lightShader("shaders/lightSource.vert", "shaders/lightSource.frag");

	Texture	Cheerfull("textures/mylittleponey.bmp");
	Texture	cat("textures/cat.bmp");

	Camera camera(glm::vec3(0.0f, 1.0f, -10.0f));

	camera.Matrix(45.0f, 0.1f, 100.0f, objectShader, Window::width, Window::height);

	float width, height;

	Object object = ObjectLoader::loadObject(argv[1]);
	Object lightEmitter = ObjectLoader::loadObject("src/assets/sphere.obj");
	lightEmitter.pos = v3{float(std::max((object.max.x - object.min.x) * 1.5f, (object.max.z - object.min.z) * 1.5f)), object.max.y + 2.0f, 0.0f};
	int	selected = 1;

	ShadowMap		shadowMap;
	ObjectSelecter	objectSelecter;

	while (!glfwWindowShouldClose(window))
	{
		WindowManager.startRenderLoop();
		WindowManager.HandleInputs();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		lightEmitter.movement(WindowManager.getContext(), selected == 0, false);
		object.movement(WindowManager.getContext(), selected == 1, Window::rotate);

		camera.Inputs(window);


		objectSelecter.shader.Activate();
		camera.Matrix(45.0f, 0.1f, 500.0f, objectSelecter.shader, Window::width, Window::height);

		if (Window::select)
		{
			int newSelected = objectSelecter.SelectObject(lightEmitter, object, Window::mousePos, v3{Window::width, Window::height, 0});
			selected = (newSelected != -1 ? newSelected : selected);
		}
		Window::select = false;


		glm::mat4	orthogonalProj = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 1000.0f);
		glm::mat4	lightView = glm::lookAt(glm::vec3(100.0f, 0.5f, 0.5f), glm::vec3(object.pos.x, object.pos.y, object.pos.z), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4	lightProj = orthogonalProj * lightView;

		
		glEnable(GL_DEPTH_TEST);

		shadowMap.startShadowGen(lightProj);
		shadowMap.renderShadows(object);
		shadowMap.endShadowGen();

		glViewport(0, 0, Window::width, Window::height);

		objectShader.Activate();

		camera.Matrix(45.0f, 0.1f, 500.0f, objectShader, Window::width, Window::height);

		v3	color = {1, 0, 0};
		glUniform3fv(glGetUniformLocation(objectShader.ID, "uColor"), 1, glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f)));

		Cheerfull.Bind(objectShader, 0);
		cat.Bind(objectShader, 1);
		
		
		shadowMap.sendToShader(objectShader);

		glUniformMatrix4fv(glGetUniformLocation(objectShader.ID, "uLightProjection"), 1, GL_FALSE, glm::value_ptr(lightProj));
		glUniform3fv(glGetUniformLocation(objectShader.ID, "uLightPos"), 1, &lightEmitter.pos.x);
		glUniform3fv(glGetUniformLocation(objectShader.ID, "uLightColor"), 1, &Window::lightColor.x);
		glUniform3fv(glGetUniformLocation(objectShader.ID, "uMixWay"), 1, glm::value_ptr(glm::vec3(Window::mixWay.x, Window::mixWay.y, Window::mixWay.z)));
		glUniform1i(glGetUniformLocation(objectShader.ID, "uLight"), Window::light);
		glUniform1i(glGetUniformLocation(objectShader.ID, "uTorch"), Window::torch);
		glUniform1i(glGetUniformLocation(objectShader.ID, "uShadows"), Window::shadow);
		glUniform1f(glGetUniformLocation(objectShader.ID, "uTextMix"), Window::textMix);
		glUniform1f(glGetUniformLocation(objectShader.ID, "uTypeMix"), Window::typeMix);
		glUniform1f(glGetUniformLocation(objectShader.ID, "uObjMin"), (object.min * Window::mixWay).sum());
		glUniform1f(glGetUniformLocation(objectShader.ID, "uObjMax"), (object.max * Window::mixWay).sum());

		object.Render(objectShader);
		
		lightShader.Activate();
		camera.Matrix(45.0f, 0.1f, 500.0f, lightShader, Window::width, Window::height);
		glUniform3fv(glGetUniformLocation(lightShader.ID, "uLightColor"), 1, &Window::lightColor.x);
		lightEmitter.Render(lightShader);

		glDisable(GL_DEPTH_TEST);

		WindowManager.endRenderLoop();
	}
	objectShader.Delete();
	lightShader.Delete();
	Cheerfull.Delete();
	cat.Delete();
}
