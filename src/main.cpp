/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:29:15 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 19:26:19 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Window/Window.hpp>

GLFWwindow	*window;

void	printManual()
{
	PRINT WHT BOLD "--USER MANUAL--" CENDL;
	PRINT WHT TAB "crtl: Lock Camera" ENDL;
	PRINT TAB "WASD: Move Camera" ENDL;
	PRINT TAB "Space/alt: Camera Up/Down" ENDL;
	PRINT TAB "shift: Fast Camera" ENDL;
	PRINT TAB "r: Toggle Rotation" ENDL;
	PRINT TAB "t: Switch between Texture and Color" ENDL;
	PRINT TAB "y: Switch Texture/Color" ENDL;
	PRINT TAB "f: Toggle Light" ENDL;
	PRINT TAB "g: Toggle Shadow" ENDL;
	PRINT TAB "h: Switch Transition Orientation" ENDL;
	PRINT TAB "uio: Increase Lightcolor RGB" ENDL;
	PRINT TAB "jkl: Decrease Lightcolor RGB" ENDL;
	PRINT TAB "Numpad 1/2: Increase/Decrease X Value of Object" ENDL;
	PRINT TAB "Numpad 7/4: Increase/Decrease Y Value of Object" ENDL;
	PRINT TAB "Numpad 8/5: Increase/Decrease Z Value of Object" ENDL;
	PRINT TAB "LeftClick: Select Object" ENDL;
	PRINT TAB "RightClick: Toggle Torch" CENDL;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);

	try
	{
		Window	WindowManager;

		window = WindowManager.getContext();

		Shader	objectShader("shaders/default.vert", "shaders/default.frag");
		Shader	lightShader("shaders/lightSource.vert", "shaders/lightSource.frag");

		Texture	Cheerfull("src/textures/mylittleponey.bmp");
		Texture	cat("src/textures/cat.bmp");

		float width, height;

		Object object = ObjectLoader::loadObject(argv[1]);
		Object lightEmitter = ObjectLoader::loadObject("src/asset/sphere.obj");
		lightEmitter.pos = math::v3{float(std::max((object.max.x - object.min.x) * 1.5f, (object.max.z - object.min.z) * 1.5f)), object.max.y + 2.0f, 0.0f};
		int	selected = 1;

		Camera camera(math::v3{float(-std::max((object.max.x - object.min.x) * 1.5f, (object.max.z - object.min.z) * 1.5f)), 0, 0.0f});

		camera.Matrix(45.0f, 0.1f, 100.0f, objectShader, Window::width, Window::height);

		ShadowMap		shadowMap;
		ObjectSelecter	objectSelecter;

		printManual();

		while (!glfwWindowShouldClose(window))
		{
			WindowManager.startRenderLoop();

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);

			lightEmitter.movement(WindowManager.getContext(), selected == 0, false);
			object.movement(WindowManager.getContext(), selected == 1, Window::rotate);

			camera.Inputs(window);


			objectSelecter.shader.Activate();
			camera.Matrix(45.0f, 0.1f, 500.0f, objectSelecter.shader, Window::width, Window::height);

			if (Window::select)
			{
				int newSelected = objectSelecter.SelectObject(lightEmitter, object, Window::mousePos, math::v3{Window::width, Window::height, 0});
				selected = (newSelected != -1 ? newSelected : selected);
			}
			Window::select = false;


			math::mat4	orthogonalProj = math::mat4::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 1000.0f);
			math::mat4	lightView = math::mat4::lookAt(math::v3{100.0f, 0.5f, 0.5f}, math::v3{object.pos.x, object.pos.y, object.pos.z}, math::v3{0.0f, 1.0f, 0.0f});
			math::mat4	lightProj = orthogonalProj * lightView;

			
			glEnable(GL_DEPTH_TEST);

			shadowMap.startShadowGen(lightProj);
			shadowMap.renderShadows(object);
			shadowMap.endShadowGen();

			glViewport(0, 0, Window::width, Window::height);

			objectShader.Activate();

			camera.Matrix(45.0f, 0.1f, 500.0f, objectShader, Window::width, Window::height);

			Cheerfull.Bind(objectShader, 0);
			cat.Bind(objectShader, 1);
			shadowMap.sendToShader(objectShader);

			glUniformMatrix4fv(glGetUniformLocation(objectShader.ID, "uLightProjection"), 1, GL_FALSE, &lightProj.data[0]);
			glUniform3fv(glGetUniformLocation(objectShader.ID, "uLightPos"), 1, &lightEmitter.pos.x);
			glUniform3fv(glGetUniformLocation(objectShader.ID, "uLightColor"), 1, &Window::lightColor.x);
			glUniform3fv(glGetUniformLocation(objectShader.ID, "uMixWay"), 1, &Window::mixWay.x);
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
	}
	catch (std::exception &e)
	{
		PRINT RED BOLD AND e.what() AND CLR ENDL;
		return (0);
	}
}
