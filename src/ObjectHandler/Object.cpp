/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/10 09:18:36 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ObjectHandler/Object.hpp>

Object::Object(GLuint VAO_ID, GLuint VBO_ID, const std::vector<float> &vertices, int nbFaces) : _vertices(vertices), _nbFaces(nbFaces)
{
	_VAO.ID = VAO_ID;
	_VBO.ID = VBO_ID;
	min = {_vertices[LINELEN], _vertices[LINELEN + 1], _vertices[LINELEN + 2]};
	max = {_vertices[LINELEN], _vertices[LINELEN + 1], _vertices[LINELEN + 2]};
	for (int i = 0; i < _vertices.size() / LINELEN; i++)
	{
		if (_vertices[i * LINELEN] > max.x)
			max.x = _vertices[i * LINELEN];
		else if (_vertices[i * LINELEN] < min.x)
			min.x = _vertices[i * LINELEN];

		if (_vertices[i * LINELEN + 1] > max.y)
			max.y = _vertices[i * LINELEN + 1];
		else if (_vertices[i * LINELEN + 1] < min.y)
			min.y = _vertices[i * LINELEN + 1];

		if (_vertices[i * LINELEN + 2] > max.z)
			max.z = _vertices[i * LINELEN + 2];
		else if (_vertices[i * LINELEN + 2] < min.z)
			min.z = _vertices[i * LINELEN + 2];
	}
	center = (max + min) / math::v3{20000, 20000, 20000};
}

Object::~Object()
{
}

void	Object::Render(Shader &shader)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uModelMatrix"), 1, GL_FALSE, &_modelMatrix.data[0]);
	glUniform1i(glGetUniformLocation(shader.ID, "uNbFaces"), _nbFaces / 3);
	_VAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
}

void	Object::movement(GLFWwindow *window, bool move, bool rotate)
{
	_modelMatrix = math::mat4(1.0f);

	math::v3	change = {0, 0, 0};
	if (move)
	{
		if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
			change.y = 1;
		else if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
			change.y = -1;

		if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
			change.z = 1;
		else if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
			change.z = -1;

		if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
			change.x = 1;
		else if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
			change.x = -1;
	}
	pos = pos + change;
	_modelMatrix = math::mat4::translate(_modelMatrix, pos);
	if (rotate)
		_angle += 0.01;
	_modelMatrix = math::mat4::rotate(_modelMatrix, _angle, math::v3{0, 1, 0});
	_modelMatrix = math::mat4::translate(_modelMatrix, center * math::v3{-1, 0.5, -1});
}
