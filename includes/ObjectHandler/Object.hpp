/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/05 19:06:16 by mbirou           ###   ########.fr       */
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
		Object(VAO &VAO, VBO &VBO, const std::vector<float> &vertices);
		~Object();

		void	Render();

	private:
		VAO					_VAO;
		VBO					_VBO;
		// EBO					_EBO;
		std::vector<float>	_vertices;
};
