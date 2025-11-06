/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:54:09 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/06 10:02:17 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Scene/SceneManager.hpp>

SceneManager	*SceneManager::_instance = NULL;


void	SceneManager::setCurrent(const std::string &sceneID)
{
	_checkInstance();

	if (_instance->_scenes.find(sceneID) == _instance->_scenes.end())
		throw (RED BOLD UNDL "This Scene doesn't exist." CLR);

	if (!_instance->_scenes[sceneID]->isInit())
		_instance->_scenes[sceneID]->init();

	_instance->_current = sceneID;
}

void	SceneManager::unloadScene(const std::string &sceneID)
{
	_checkInstance();

	if (_instance->_scenes.find(sceneID) == _instance->_scenes.end())
		throw (RED BOLD UNDL "This Scene doesn't exist." CLR);

	_instance->_scenes[sceneID]->unload();
}
