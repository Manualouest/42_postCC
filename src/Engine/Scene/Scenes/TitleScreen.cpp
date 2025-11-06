/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TitleScreen.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:34:50 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/06 14:12:15 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Scene/Scenes/TitleScreen.hpp>

TitleScreen::TitleScreen()
{

}

TitleScreen::~TitleScreen()
{

}

void	TitleScreen::init()
{
	ShaderManager::addShader("modeltest", "assets/shaders/modeltest");
	ModelManager::addModel("dragon", "assets/objects/TerrorBird/rapid.obj");
	ModelManager::getModel("dragon").requestTextures();
	TextureManager::makeRequestArray();
	ModelManager::getModel("dragon").scale(glm::vec3{10});

	setInit(true);
}

void	TitleScreen::unload()
{
	ModelManager::getModel("dragon").removeRequests();
	ModelManager::delModel("dragon");
	TextureManager::deleteArray();
	ShaderManager::deleteshader("modeltest");

	setInit(false);
}

void	TitleScreen::processInputs()
{
	if (!isInit())
		return ;

	if (Window::getPressInput(GLFW_KEY_LEFT_CONTROL))
	{
		Window::setlockMouse(!Window::getlockMouse());
		if (Window::getlockMouse())
			glfwSetInputMode(Window::getWindowData(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		else
			glfwSetInputMode(Window::getWindowData(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (Window::getPressInput(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(Window::getWindowData(), GLFW_TRUE);

	if (Window::getRepeatInput(GLFW_KEY_KP_7))
		ModelManager::getModel("dragon").rotate(glm::vec3(1, 0, 0) * Window::getDeltaTime());
	if (Window::getRepeatInput(GLFW_KEY_KP_8))
		ModelManager::getModel("dragon").rotate(glm::vec3(0, 1, 0) * Window::getDeltaTime());
	if (Window::getRepeatInput(GLFW_KEY_KP_9))
		ModelManager::getModel("dragon").rotate(glm::vec3(0, 0, 1) * Window::getDeltaTime());

	if (Window::getRepeatInput(GLFW_KEY_KP_4))
		ModelManager::getModel("dragon").rotate(glm::vec3(-1, 0, 0) * Window::getDeltaTime());
	if (Window::getRepeatInput(GLFW_KEY_KP_5))
		ModelManager::getModel("dragon").rotate(glm::vec3(0, -1, 0) * Window::getDeltaTime());
	if (Window::getRepeatInput(GLFW_KEY_KP_6))
		ModelManager::getModel("dragon").rotate(glm::vec3(0, 0, -1) * Window::getDeltaTime());
}

void	TitleScreen::update()
{
	if (!isInit())
		return ;
}

void	TitleScreen::draw()
{
	if (!isInit())
		return ;

	ShaderManager::bindShader("modeltest");

	Model::sendNormals();

	TextureManager::useArray("texts", 0);

	if (Window::getlockMouse())
		CameraManager::selfUpdate();
	CameraManager::setViewProjMatrix();


	ModelManager::getModel("dragon").draw();
}
