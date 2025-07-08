/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/08 20:19:49 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>
#include <Buffers/VAO.hpp>
#include <Buffers/EBO.hpp>
#include <Texture/Texture.hpp>

class Object
{
	public:
		Object(VAO &VAO, VBO &VBO, const std::vector<float> &vertices, int nbFaces);
		~Object();

		void	Render(Shader &shader);
		void	movement(GLFWwindow *window, bool move, bool rotate);

		v3	pos = {0, 0, 0};
		v3	center = {0, 0, 0};
		v3	min;
		v3	max;

	private:
		VAO					_VAO;
		VBO					_VBO;
		std::vector<float>	_vertices;
		glm::mat4			_modelMatrix = glm::mat4(1.0f);
		float				_angle = 0;
		int					_nbFaces;
};
