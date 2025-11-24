/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TitleScreen.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:34:50 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/24 16:29:30 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Scene/Scenes/TitleScreen.hpp>

const int clustersizex = 10;
const int clustersizey = 10;
const int nbchunks = clustersizey * clustersizex;
int sideOffset = clustersizex / 2 * 32;

float startLOD = 0.25;
float currentLOD = 0.25;

glm::ivec2	lastCamPos = {0, 0};

Chunk					chunkTest[nbchunks];
std::vector<Chunk*>		waitingChunks;
std::vector<glm::vec2>	requestedPos;
int		x = 0;
int		y = 0;

void	TitleScreen::init()
{
	if (_isInit)
		return ;

	// ShaderManager::addShader("object", "assets/shaders/modeltest");
	// ModelManager::addModel("miku", "assets/objects/miku2/miku2.obj");
	// ModelManager::getModel("miku").genTextureArray("miku");
	// ModelManager::getModel("miku").scale({10, 10, 10});


	ShaderManager::addShader("chunk", "assets/shaders/chunk");



	for (int y = 0; y < clustersizey; ++y)
	{
		for (int x = 0; x < clustersizex; ++x)
		{
			chunkTest[y * clustersizex + x].regenerate(lastCamPos + glm::ivec2{-(sideOffset) + 32 * y, -(sideOffset) + 32 * x}, startLOD, 32, currentLOD);
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

	if (Window::getPressMouseInput(GLFW_MOUSE_BUTTON_MIDDLE))
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
			for (auto &chunk : chunkTest)
				chunk.changeLOD(currentLOD);
			// chunkTest[0].changeLOD(currentLOD);
			// chunkTest[1].changeLOD(currentLOD);
			// chunkTest[clustersizex].changeLOD(currentLOD);
			// chunkTest[clustersizex + 1].changeLOD(currentLOD);
		}
	}
	if (Window::getPressInput(GLFW_KEY_KP_SUBTRACT))
	{
		if (currentLOD > startLOD)
		{
			currentLOD /= 2;
			for (auto &chunk : chunkTest)
				chunk.changeLOD(currentLOD);
			// chunkTest[0].changeLOD(currentLOD);
			// chunkTest[1].changeLOD(currentLOD);
			// chunkTest[clustersizex].changeLOD(currentLOD);
			// chunkTest[clustersizex + 1].changeLOD(currentLOD);
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


	if (waitingChunks.empty() && glm::ivec2{CameraManager::getPlanePos()} != lastCamPos)
	{
		lastCamPos = glm::ivec2{CameraManager::getPlanePos()} / 32 * 32;
		requestedPos.resize(clustersizey * clustersizex, {0, 0});
		for (int y = 0; y < clustersizey; ++y)
		{
			for (int x = 0; x < clustersizex; ++x)
			{
				requestedPos[y * clustersizex + x] = lastCamPos + glm::ivec2{-(sideOffset) + 32 * y, -(sideOffset) + 32 * x};
				glm::vec2	chunkPos = chunkTest[y * clustersizex + x].getPos();
				if (chunkPos.y < lastCamPos.y - (sideOffset) || chunkPos.y > lastCamPos.y + (sideOffset)
						|| chunkPos.x < lastCamPos.x - (sideOffset) || chunkPos.x > lastCamPos.x + (sideOffset))
					waitingChunks.push_back(&chunkTest[y * clustersizex + x]);
			}
		}
		for (auto &chunk : chunkTest)
		{
			if (std::find(requestedPos.begin(), requestedPos.end(), chunk.getPos()) != requestedPos.end())
				requestedPos.erase(std::find(requestedPos.begin(), requestedPos.end(), chunk.getPos()));
		}
	}
	if (!waitingChunks.empty())
	{
		for (int i = 0; i < glm::min(2, (int)waitingChunks.size()); ++i)
		{
			waitingChunks[0]->regenerate(requestedPos[0], startLOD, 32, currentLOD);
			waitingChunks.erase(waitingChunks.begin());
			requestedPos.erase(requestedPos.begin());
		}
	}


	for (int i = 0; i < nbchunks; ++i)
		chunkTest[i].draw();


	// ShaderManager::bindShader("object");
	// CameraManager::setViewProjMatrix();
	// TextureManager::useArray("miku", "texts", 0);
	// ModelManager::getModel("miku").draw();
}
