/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:49:41 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/24 16:30:15 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Engine.hpp>

Engine::Engine()
{
}

Engine::~Engine()
{
}

void	Engine::run()
{
	_init();
	
	Window::setRunning(true);
	CameraManager::selfUpdate();
	_renderLoop();
}

void	Engine::_init()
{
	SceneManager::addScene("title", new TitleScreen);
	SceneManager.setCurrent("title");
	computeNormals();
}

void	Engine::_renderLoop()
{
	while (Window::isRunning())
	{
		Window::startFrame();

		SceneManager::getCurrent()->processInputs();
		SceneManager::getCurrent()->update();
		SceneManager::getCurrent()->draw();

		Window::endFrame();
	}
}
