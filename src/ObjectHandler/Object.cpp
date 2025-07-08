/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/08 20:39:41 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ObjectHandler/Object.hpp>

Object::Object(VAO &VAO, VBO &VBO, const std::vector<float> &vertices, int nbFaces) : _VAO(VAO), _VBO(VBO), _vertices(vertices), _nbFaces(nbFaces)
{
	min = {_vertices[8], _vertices[8 + 1], _vertices[8 + 2]};
	max = {_vertices[8], _vertices[8 + 1], _vertices[8 + 2]};
	for (int i = 0; i < _vertices.size() / 8; i++)
	{
		if (_vertices[i * 8] > max.x)
			max.x = _vertices[i * 8];
		else if (_vertices[i * 8] < min.x)
			min.x = _vertices[i * 8];

		if (_vertices[i * 8 + 1] > max.y)
			max.y = _vertices[i * 8 + 1];
		else if (_vertices[i * 8 + 1] < min.y)
			min.y = _vertices[i * 8 + 1];

		if (_vertices[i * 8 + 2] > max.z)
			max.z = _vertices[i * 8 + 2];
		else if (_vertices[i * 8 + 2] < min.z)
			min.z = _vertices[i * 8 + 2];
	}
	center = (max + min) / v3{2, 2, 2};
}

Object::~Object()
{
	_VAO.Delete();
	_VBO.Delete();
}

void	Object::Render(Shader &shader)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uModelMatrix"), 1, GL_FALSE, glm::value_ptr(_modelMatrix));
	glUniform1i(glGetUniformLocation(shader.ID, "uNbFaces"), _nbFaces / 3);
	_VAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
}

void	Object::movement(GLFWwindow *window, bool move, bool rotate)
{
	_modelMatrix = glm::mat4(1.0f);

	v3	change = {0, 0, 0};
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
	_modelMatrix = glm::translate(_modelMatrix, glm::vec3(pos.x, pos.y, pos.z));
	if (rotate)
		_angle += 0.01;
	_modelMatrix = glm::rotate(_modelMatrix, _angle, glm::vec3(0, 1, 0));
	_modelMatrix = glm::translate(_modelMatrix, glm::vec3(-center.x, -center.y, -center.z));
}
