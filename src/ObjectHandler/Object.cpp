/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/05 19:03:55 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ObjectHandler/Object.hpp>

Object::Object(VAO &VAO, VBO &VBO, const std::vector<float> &vertices) : _VAO(VAO), _VBO(VBO), _vertices(vertices) {}

Object::~Object()
{
	_VAO.Delete();
	_VBO.Delete();
	// _EBO.Delete();
}

void	Object::Render()
{
	_VAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
}
