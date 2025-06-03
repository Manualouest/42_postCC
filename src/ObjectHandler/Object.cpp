/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/06/03 11:20:12 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ObjectHandler/Object.hpp>

Object::Object(VAO &VAO, std::vector<VBO> &VBO, std::vector<EBO> &EBO, const std::vector<float> &indices) : _VAO(VAO), _VBO(VBO), _EBO(EBO), _indices(indices) {}

Object::~Object()
{
	_VAO.Delete();
	for (std::vector<VBO>::iterator it = _VBO.begin(); it != _VBO.end(); ++it)
		(*it).Delete();
	for (std::vector<EBO>::iterator it = _EBO.begin(); it != _EBO.end(); ++it)
		(*it).Delete();
}

void	Object::Render()
{
	_VAO.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(_indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}
