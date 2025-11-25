/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:54:09 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/07 20:23:28 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Scene/SceneManager.hpp>

SceneManager	*SceneManager::_instance = NULL;

SceneManager::SceneManager()
{
	if (!_instance)
		_instance = this;
}
SceneManager::~SceneManager()
{
	for (auto scene : _scenes)
	{
		scene.second->unload();
		delete(scene.second);
	}
	_scenes.clear();

	_instance = NULL;

	PRINT DSTR BOLD "SceneManager Destroyed" CENDL;
}

void	SceneManager::setCurrent(const std::string &sceneID)
{
	_checkInstance();

	if (_instance->_scenes.find(sceneID) == _instance->_scenes.end())
		throw(std::runtime_error(RED BOLD UNDL "This Scene doesn't exist." CLR));

	if (!_instance->_scenes[sceneID]->isInit())
		_instance->_scenes[sceneID]->init();

	_instance->_current = sceneID;
}

void	SceneManager::unloadScene(const std::string &sceneID)
{
	_checkInstance();

	if (_instance->_scenes.find(sceneID) == _instance->_scenes.end())
		throw(std::runtime_error(RED BOLD UNDL "This Scene doesn't exist." CLR));

	_instance->_scenes[sceneID]->unload();
}

AScene	*SceneManager::getCurrent()
{
	_checkInstance();

	if (_instance->_current.empty())
		throw(std::runtime_error(RED BOLD UNDL "No current Scene set" CLR));
	return (_instance->_scenes[_instance->_current]);
}

void	SceneManager::addScene(const std::string &sceneID, AScene *newScene)
{
	_checkInstance();

	_instance->_scenes.insert(std::make_pair(sceneID, newScene));
}

void	SceneManager::_checkInstance()
{
	if (!_instance)
		throw(std::runtime_error(RED BOLD UNDL "SceneManager instance not created" CLR));
}

