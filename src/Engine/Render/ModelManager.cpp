/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModelManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:26:48 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/25 13:44:22 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Render/ModelManager.hpp>

ModelManager	*ModelManager::_instance = NULL;

ModelManager::ModelManager()
{
	if (!_instance)
		_instance = this;
}

ModelManager::~ModelManager()
{
	for (auto model : _models)
		model.second.remove();
}

void	ModelManager::addModel(const std::string &modelID, const std::string &path)
{
	_checkInstance();
	if (_instance->_models.find(modelID) != _instance->_models.end())
		throw(std::runtime_error(RED BOLD UNDL "This Model already exist" CLR));

	_instance->_models.insert({modelID, Model(path)});
}

Model	&ModelManager::getModel(const std::string &modelID)
{
	_checkInstance();

	if (_instance->_models.find(modelID) == _instance->_models.end())
		throw(std::runtime_error(RED BOLD UNDL "This Model doesn't exist" CLR));
	
	return (_instance->_models[modelID]);
}

void	ModelManager::delModel(const std::string &modelID)
{
	_checkInstance();

	if (_instance->_models.find(modelID) != _instance->_models.end())
	{
		_instance->_models[modelID].remove();
		_instance->_models.erase(modelID);
	}
}

void	ModelManager::_checkInstance()
{
	if (!_instance)
		throw(std::runtime_error(RED BOLD UNDL "ModelManager instance not created" CLR));
}