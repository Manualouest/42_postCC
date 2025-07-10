/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectSelecter.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:20:47 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 16:29:12 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>
#include <Shaders/Shaders.hpp>
#include <ObjectHandler/Object.hpp>

class ObjectSelecter
{
	public:
		ObjectSelecter();
		~ObjectSelecter();

		int	SelectObject(Object &lightEmitter, Object &object, math::v3 mousePos, math::v3 winSize);
	
		Shader	shader;

		unsigned int	_ObjectSelecterMap;
	private:
		unsigned int	_FBO;
		unsigned int	_RBO;
		unsigned int	_width = 2048;
		unsigned int	_height = 2048;
		math::v3				_colors[3] = {math::v3{1, 0, 0}, math::v3{0, 1, 0}, math::v3{0, 0, 1}};
};