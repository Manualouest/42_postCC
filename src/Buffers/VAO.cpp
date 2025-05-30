/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAO.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:57 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/09 11:14:53 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Buffers/VAO.hpp>

VAO::VAO()
{
}

VAO::VAO(const int &n)
{
	(void)n;
	glGenVertexArrays(1, &ID);
}

void	VAO::linkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void *offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	// glVertexAttribDivisor(layout, 1); 
	VBO.Unbind();
}

void	VAO::Bind()
{
	glBindVertexArray(ID);
}

void	VAO::Unbind()
{
	glBindVertexArray(0);
}

void	VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
