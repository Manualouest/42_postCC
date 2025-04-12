/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:10:34 by mbirou            #+#    #+#             */
/*   Updated: 2025/04/12 21:50:11 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <Shaders/Shaders.hpp>

class Texture
{
	public:
		GLuint	ID;
		GLenum	type;
		Texture(const char *image, GLenum textType, GLenum slot, GLenum format, GLenum pixelType);
	
		void	texUnit(Shader &shader, const char *uniform, GLuint unit);
		void	Bind();
		void	Unbind();
		void	Delete();
};