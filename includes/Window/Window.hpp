/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:22:40 by mbirou            #+#    #+#             */
/*   Updated: 2025/06/01 16:26:02 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Buffers/VAO.hpp>
#include <Buffers/EBO.hpp>
#include <Texture/Texture.hpp>
#include <Camera/Camera.hpp>

class Window
{
	public:
		Window();
		~Window();

		GLFWwindow *getContext() const;
	
	private:
		GLFWwindow *_window;
};