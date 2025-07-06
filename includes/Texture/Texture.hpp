/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:10:34 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/06 14:28:41 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb/stb_image.h>

#include <Shaders/Shaders.hpp>

class Texture
{
	public:
		GLuint	ID;
		GLenum	type;
		Texture(const char *path);
	
		void	texUnit(Shader &shader, const char *uniform, GLuint unit);
		void	LoadImage(const char *path);
		void	Bind();
		void	Unbind();
		void	Delete();

		int							width;
		int							height;
		std::vector<unsigned char>	data;
};