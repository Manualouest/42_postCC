/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VBO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:15:01 by mbirou            #+#    #+#             */
/*   Updated: 2025/06/01 14:34:41 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>

class VBO
{
	public:
		VBO();
		VBO(GLfloat *vertices, GLsizeiptr size);

		void	Bind();
		void	Unbind();
		void	Delete();

		GLuint	ID;
};