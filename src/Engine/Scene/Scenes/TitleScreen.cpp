/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TitleScreen.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:34:50 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/18 23:31:25 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Scene/Scenes/TitleScreen.hpp>

const int clustersize = 6;
const int nbchunks = clustersize * clustersize;

Chunk	chunkTest[nbchunks];

void	TitleScreen::init()
{
	if (_isInit)
		return ;

	ShaderManager::addShader("chunk", "assets/shaders/chunk");

	for (int y = 0; y < clustersize; ++y)
	{
		for (int x = 0; x < clustersize; ++x)
		{
			chunkTest[y * clustersize + x].generate({x * 32, y * 32}, 0.25, 32);
		}
	}


	_isInit = true;
}

void	TitleScreen::unload()
{
	if (!_isInit)
		return ;

	for (int i = 0; i < nbchunks; ++i)
		chunkTest[i].remove();

	_isInit = false;
}

void	TitleScreen::processInputs()
{
	if (!_isInit)
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
}

void	TitleScreen::update()
{
	if (!_isInit)
		return ;

	if (Window::getlockMouse())
		CameraManager::selfUpdate();
}

void	TitleScreen::draw()
{
	if (!_isInit)
		return ;


	ShaderManager::bindShader("chunk");
	CameraManager::setViewProjMatrix();

	for (int i = 0; i < nbchunks; ++i)
		chunkTest[i].draw();
}
