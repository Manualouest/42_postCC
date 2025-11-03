/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:54:25 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/21 18:51:11 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEMANAGER_HPP
# define SCENEMANAGER_HPP

#include <Engine/Scene/AScene.hpp>

class	SceneManager
{
	public:
		SceneManager();
		~SceneManager();

		void	setCurrent(const std::string &id) {_current = id;}
		AScene	&getCurrent() {return (_scenes[_current]);}

	private:
		std::string						_current;
		std::map<std::string, AScene>	_scenes;
};

#endif