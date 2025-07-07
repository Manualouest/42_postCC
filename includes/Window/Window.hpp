/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:22:40 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 16:00:05 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include <Buffers/VAO.hpp>
// #include <Buffers/EBO.hpp>
// #include <Texture/Texture.hpp>
#include <ObjectHandler/ObjectLoader.hpp>
#include <Camera/Camera.hpp>
#include <ShadowMap/ShadowMap.hpp>

class Window
{
	public:
		Window();
		~Window();

		static float	width;
		static float	height;

		GLFWwindow	*getContext() const;
		float		startRenderLoop();
		void		endRenderLoop();

	private:
		GLFWwindow	*_window;
		float		_deltaTime;
		double		_oldTime;
};