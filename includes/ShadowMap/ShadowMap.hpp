/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShadowMap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:23:45 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 20:37:46 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>
#include <Shaders/Shaders.hpp>
#include <ObjectHandler/Object.hpp>

class ShadowMap
{
	public:
		ShadowMap();
		~ShadowMap();

		void	getShadows(glm::mat4 lightProj, Object &object);
		void	sendToShader(Shader shader);
	
		Shader	shader;

	private:
		unsigned int	_FBO;
		unsigned int	_width = 2048;
		unsigned int	_height = 2048;
		unsigned int	_shadowMap;
};
