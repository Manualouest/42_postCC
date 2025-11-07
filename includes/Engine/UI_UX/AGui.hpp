/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AGui.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:56:24 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/07 20:14:08 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AGUI_HPP
# define AGUI_HPP

# include <iostream>
# include <Engine/Render/Objects/Window.hpp>
# include <Engine/Render/ShaderManager.hpp>
# include <Engine/Render/TextureManager.hpp>
# include <Engine/Render/ModelManager.hpp>

class AGui
{
	public:
		AGui() {;}
		virtual ~AGui() {;}

		std::string getId() const					{return (_id);}
		bool		isInit() const					{return (_isInit);}
		void		isInit(const bool &newState)	{_isInit = newState;}

		virtual void init() = 0;
		virtual void unload() = 0;
		virtual void processInputs() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

	private:
		std::string	_id;
		bool		_isInit = false;
};

#endif