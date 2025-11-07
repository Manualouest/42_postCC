/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GuiManager.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:13:16 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/07 20:13:16 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/UI_UX/GuiManager.hpp>

GuiManager	*GuiManager::_instance = NULL;

GuiManager::GuiManager()
{
	if (!_instance)
		_instance = this;
}

GuiManager::~GuiManager()
{
	for (auto gui : _guis)
		delete(gui.second);
	_guis.clear();

	_instance = NULL;

	PRINT DSTR BOLD "GuiManager Destroyed" CENDL;
}

void	GuiManager::setCurrent(const std::string &guiID)
{
	_checkInstance();

	if (_instance->_guis.find(guiID) == _instance->_guis.end())
		throw(std::runtime_error(RED BOLD UNDL "This Gui doesn't exist." CLR));

	if (!_instance->_guis[guiID]->isInit())
		_instance->_guis[guiID]->init();

	_instance->_current = guiID;
}

void	GuiManager::unloadCurrent(const std::string &guiID)
{
	_checkInstance();

	if (_instance->_guis.find(guiID) == _instance->_guis.end())
		throw(std::runtime_error(RED BOLD UNDL "This Gui doesn't exist." CLR));

	_instance->_guis[guiID]->unload();
}

AGui	*GuiManager::getCurrent()
{
	_checkInstance();

	if (_instance->_current.empty())
		throw(std::runtime_error(RED BOLD UNDL "No current Gui set" CLR));
	return (_instance->_guis[_instance->_current]);
}

AGui	*GuiManager::getGui(const std::string &guiID)
{
	_checkInstance();

	if (_instance->_guis.find(guiID) == _instance->_guis.end())
		throw(std::runtime_error(RED BOLD UNDL "This Gui doesn't exist." CLR));

	return (_instance->_guis[guiID]);
}

void	GuiManager::useGui(const std::string &guiID)
{
	_checkInstance();

	if (_instance->_guis.find(guiID) == _instance->_guis.end())
		throw(std::runtime_error(RED BOLD UNDL "This Gui doesn't exist." CLR));

	if (!_instance->_guis[guiID]->isInit())
		_instance->_guis[guiID]->init();

	_instance->_guis[guiID]->processInputs();
	_instance->_guis[guiID]->update();
	_instance->_guis[guiID]->draw();
}


void	GuiManager::addGui(const std::string &guiID, AGui *newGui)
{
	_checkInstance();

	_instance->_guis.insert(std::make_pair(guiID, newGui));
}

void	GuiManager::_checkInstance()
{
	if (!_instance)
		throw(std::runtime_error(RED BOLD UNDL "GuiManager instance not created" CLR));
}
