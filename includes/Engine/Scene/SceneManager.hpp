/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:54:25 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/07 19:10:42 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEMANAGER_HPP
# define SCENEMANAGER_HPP

#include <Engine/Scene/AScene.hpp>

#include <spellBook.hpp>

class	SceneManager
{
	public:
		SceneManager();
		~SceneManager();

		static void		setCurrent(const std::string &sceneID);
		static void		unloadScene(const std::string &sceneID);

		static AScene	*getCurrent();
		static void		addScene(const std::string &sceneID, AScene *newScene);

	private:
		static void	_checkInstance();

		static SceneManager	*_instance;

		std::string						_current = "";
		std::map<std::string, AScene*>	_scenes;
};

#endif