/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:54:25 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/06 09:59:57 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEMANAGER_HPP
# define SCENEMANAGER_HPP

#include <Engine/Scene/AScene.hpp>

#include <spellBook.hpp>

class	SceneManager
{
	public:
		SceneManager()	{if (!_instance) _instance = this;}
		~SceneManager() {_checkInstance(); for (auto scene : _instance->_scenes) delete(scene.second); _instance->_scenes.clear();}

		static void		setCurrent(const std::string &sceneID);
		static void		unloadScene(const std::string &sceneID);
		static AScene	*getCurrent()											{_checkInstance(); return (_instance->_scenes[_instance->_current]);}
		static void		addScene(const std::string &sceneID, AScene *newScene)	{_checkInstance(); _instance->_scenes.insert(std::make_pair(sceneID, newScene));}

	private:
		static void	_checkInstance() {if (!_instance) throw(std::runtime_error(RED BOLD UNDL "SceneManager instance not created" CLR));}

		static SceneManager	*_instance;

		std::string						_current;
		std::map<std::string, AScene*>	_scenes;
};

#endif