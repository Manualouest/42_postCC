/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScene.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:55:16 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/08 12:44:50 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_HPP
# define SCENE_HPP

# include <iostream>
# include <Engine/Render/Objects/Window.hpp>
# include <Engine/Render/CameraManager.hpp>
# include <Engine/Render/ShaderManager.hpp>
# include <Engine/Render/TextureManager.hpp>
# include <Engine/Render/ModelManager.hpp>
# include <Engine/UI_UX/GuiManager.hpp>

class AScene
{
	public:
		AScene() {;}
		virtual ~AScene() {;}

		std::string	getId() const					{return (_id);}
		bool		isInit() const					{return (_isInit);}
		void		setInit(const bool &newState)	{_isInit = newState;}

		virtual void	init() = 0;
		virtual void	unload() = 0;
		virtual void	processInputs() = 0;
		virtual void	update() = 0;
		virtual void	draw() = 0;

	protected:
		std::string	_id;
		bool		_isInit = false;
};

#endif