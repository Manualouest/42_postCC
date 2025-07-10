/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 19:04:24 by mbirou           ###   ########.fr       */
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
		Object(GLuint VAO_ID, GLuint VBO_ID, const std::vector<float> &vertices, int nbFaces);
		~Object();

		void	Render(Shader &shader);
		void	movement(GLFWwindow *window, bool move, bool rotate);

		math::v3	pos = {0, 0, 0};
		math::v3	center = {0, 0, 0};
		math::v3	min;
		math::v3	max;

	private:
		VAO					_VAO;
		VBO					_VBO;
		std::vector<float>	_vertices;
		math::mat4			_modelMatrix = math::mat4(1.0f);
		float				_angle = 0;
		int					_nbFaces;
};
