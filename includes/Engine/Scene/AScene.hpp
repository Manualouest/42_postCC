/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScene.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:55:16 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/21 18:06:20 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_HPP
# define SCENE_HPP

# include <Engine/UI_UX/AGUI.hpp>

# include <iostream>
# include <map>

class AScene
{
	public:
		AScene();
		~AScene();

		std::string	getId() {return (_id);}

		virtual void	init() = 0;
		virtual void	processInputs(const double &deltaTime) = 0;
		virtual void	update(const double &deltaTime) = 0;
		virtual void	draw() = 0;

	private:
		std::string	_id;
		std::string	_currentGUI;

		std::map<std::string, AGUI>	_GUIs;
};

#endif