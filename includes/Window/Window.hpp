/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:22:40 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 16:29:21 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include <Buffers/VAO.hpp>
// #include <Buffers/EBO.hpp>
// #include <Texture/Texture.hpp>
#include <includes.hpp>
#include <ObjectHandler/ObjectLoader.hpp>
#include <Camera/Camera.hpp>
#include <ShadowMap/ShadowMap.hpp>
#include <ObjectSelecter/ObjectSelecter.hpp>

class Window
{
	public:
		Window();
		~Window();

		static float	width;
		static float	height;
		static bool		rotate;
		static bool		light;
		static bool		torch;
		static bool		shadow;
		static float	typeMix;
		static float	textMix;
		static float	typeMixDiff;
		static float	textMixDiff;
		static math::v3	mixWay;
		static bool		select;
		static math::v3	mousePos;
		static math::v3	lightColor;

		GLFWwindow	*getContext() const;
		float		startRenderLoop();
		void		endRenderLoop();

	private:
		GLFWwindow		*_window;
		float			_deltaTime;
		double			_oldTime;
		unsigned int	_monitorWidth;
		unsigned int	_monitorHeight;
};