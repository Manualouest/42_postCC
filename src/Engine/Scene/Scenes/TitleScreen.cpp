/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TitleScreen.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:34:50 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/19 12:41:25 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Scene/Scenes/TitleScreen.hpp>

const int clustersize = 50;
const int nbchunks = clustersize * clustersize;

Chunk	chunkTest[nbchunks];
int		x = 0;
int		y = 0;

void	TitleScreen::init()
{
	if (_isInit)
		return ;

	ShaderManager::addShader("chunk", "assets/shaders/chunk");

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
	
	if (y >= 0)
	{
		// PRERR x AND "; " AND y AND "; " AND y * clustersize + x ENDL;
		// if ((x + y) % 6 == 5)
		// 	chunkTest[y * clustersize + x].generate({x * 32, y * 32}, 4, 32);
		// else if ((x + y) % 6 == 4)
			chunkTest[y * clustersize + x].generate({x * 32, y * 32}, 1, 32);
		// else if ((x + y) % 6 == 3)
		// 	chunkTest[y * clustersize + x].generate({x * 32, y * 32}, 0.5, 32);
		// else if ((x + y) % 6 == 2)
		// 	chunkTest[y * clustersize + x].generate({x * 32, y * 32}, 0.25, 32);
		// else if ((x + y) % 6 == 1)
		// 	chunkTest[y * clustersize + x].generate({x * 32, y * 32}, 0.2, 32);
		// else
		// 	chunkTest[y * clustersize + x].generate({x * 32, y * 32}, 0.1, 32);

		x ++;
		if (x == clustersize)
		{
			x = 0;
			y ++;
			if (y == (clustersize))
				y = -1;
		}
	}
	else
	{
		
	}

	for (int i = 0; i < nbchunks; ++i)
		chunkTest[i].draw();
}
