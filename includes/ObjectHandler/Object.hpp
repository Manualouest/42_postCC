/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/06/03 11:19:44 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <includes.hpp>
#include <Buffers/VAO.hpp>
#include <Buffers/EBO.hpp>
#include <Texture/Texture.hpp>

class Object
{
	public:
		Object(VAO &VAO, std::vector<VBO> &VBO, std::vector<EBO> &EBO, const std::vector<float> &indices);
		~Object();

		void	Render();

	private:
		VAO					_VAO;
		std::vector<VBO>	_VBO;
		std::vector<EBO> 	_EBO;
		std::vector<float>	_indices;
};
