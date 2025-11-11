/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestGui.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:37:54 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/08 16:22:07 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/UI_UX/Guis/TestGui.hpp>

void	TestGui::init()
{
	if (_isInit)
		return ;

	ModelManager::addModel("guitest", "assets/objects/miku2/miku2.obj");
	ModelManager::getModel("guitest").genTextureArray("miku");

	_isInit = true;
}

void	TestGui::unload()
{
	if (!_isInit)
		return ;

	ModelManager::getModel("guitest").delTextures();
	ModelManager::delModel("guitest");
	TextureManager::deleteArray("miku");

	_isInit = false;
}

void	TestGui::processInputs()
{
	if (!_isInit)
		return ;
	
	if (Window::getRepeatMouseInput(GLFW_MOUSE_BUTTON_LEFT) && Window::getMousePosX() > WWIDTH / 2)
		ModelManager::getModel("guitest").translate(glm::vec3{10, 0, 0} * Window::getDeltaTime());
	else if (Window::getRepeatMouseInput(GLFW_MOUSE_BUTTON_LEFT))
		ModelManager::getModel("guitest").translate(glm::vec3{-10, 0, 0} * Window::getDeltaTime());
}

void	TestGui::update()
{
	if (!_isInit)
		return ;
	
}

void	TestGui::draw()
{
	if (!_isInit)
		return ;

	TextureManager::useArray("miku", "texts", 0);
	ModelManager::getModel("guitest").draw();
}
