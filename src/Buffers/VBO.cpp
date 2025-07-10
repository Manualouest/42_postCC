/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VBO.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:57 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 07:36:10 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Buffers/VBO.hpp>

VBO::VBO()
{}

VBO::VBO(GLfloat *vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
	Delete();
}

void	VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void	VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
