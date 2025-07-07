/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 19:21:15 by mbirou           ###   ########.fr       */
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
		void	movement(GLFWwindow *window);

		v3	center = {0, 0, 0};

	private:
		VAO					_VAO;
		VBO					_VBO;
		// EBO					_EBO;
		std::vector<float>	_vertices;
		glm::mat4			_modelMatrix = glm::mat4(1.0f);
		float				_angle = 0;
		int					_nbFaces;
};
