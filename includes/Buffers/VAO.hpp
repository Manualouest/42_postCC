/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:15:01 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/09 11:15:22 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <glad/glad.h>
#include <Buffers/VBO.hpp>

class VAO
{
	public:
		VAO();
		VAO(const int &n);

		void	linkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void *offset);
		void	Bind();
		void	Unbind();
		void	Delete();

		GLuint	ID;
};