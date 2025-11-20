/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TitleScreen.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:34:50 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/20 15:59:53 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Scene/Scenes/TitleScreen.hpp>

const int clustersizex = 28;
const int clustersizey = 15;
const int nbchunks = clustersizey * clustersizex;

float startLOD = 0.25;
float currentLOD = 0.25;

Chunk	chunkTest[nbchunks];
int		x = 0;
int		y = 0;

void	TitleScreen::init()
{
	if (_isInit)
		return ;

	ShaderManager::addShader("object", "assets/shaders/modeltest");
	ModelManager::addModel("miku", "assets/objects/miku2/miku2.obj");
	ModelManager::getModel("miku").genTextureArray("miku");
	ModelManager::getModel("miku").scale({10, 10, 10});


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


	if (Window::getPressInput(GLFW_KEY_KP_ADD))
	{
		if (currentLOD < 32)
		{
			currentLOD *= 2;
			PRINT "LOD UP" ENDL;
			chunkTest[0].regenerate(currentLOD);
			chunkTest[1].regenerate(currentLOD);
			chunkTest[clustersizex].regenerate(currentLOD);
			chunkTest[clustersizex + 1].regenerate(currentLOD);
		}
	}
	if (Window::getPressInput(GLFW_KEY_KP_SUBTRACT))
	{
		if (currentLOD > startLOD)
		{
			currentLOD /= 2;
			PRINT "LOD DOWN" ENDL;
			chunkTest[0].regenerate(currentLOD);
			chunkTest[1].regenerate(currentLOD);
			chunkTest[clustersizex].regenerate(currentLOD);
			chunkTest[clustersizex + 1].regenerate(currentLOD);
		}
	}

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
		// PRERR x AND "; " AND y AND "; " AND y * clustersizex + x ENDL;

		if (x < 8)
			chunkTest[y * clustersizex + x].generate({x * 32, y * 32}, startLOD, 32, currentLOD);
		else
			chunkTest[y * clustersizex + x].generate({x * 32, y * 32}, startLOD, 32, currentLOD * glm::pow(2, std::min((x - 8) / 5 + 2, 7)));

		x ++;
		if (x == clustersizex)
		{
			x = 0;
			y ++;
			if (y == (clustersizey))
				y = -1;
		}
	}

	for (int i = 0; i < nbchunks; ++i)
		chunkTest[i].draw();


	ShaderManager::bindShader("object");
	CameraManager::setViewProjMatrix();
	TextureManager::useArray("miku", "texts", 0);
	ModelManager::getModel("miku").draw();
}
