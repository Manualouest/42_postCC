/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:15:01 by mbirou            #+#    #+#             */
/*   Updated: 2025/04/12 21:50:13 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <glad/glad.h>
#include <Buffers/VBO.hpp>

class VAO
{
	public:
		GLuint	ID;
		VAO();

		void	linkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void *offset);
		void	Bind();
		void	Unbind();
		void	Delete();
};