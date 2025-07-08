/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShadowMap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:23:45 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/08 13:32:37 by mbirou           ###   ########.fr       */
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

		void	startShadowGen(glm::mat4 lightProj);
		void	renderShadows(Object &object);
		void	endShadowGen();
		void	sendToShader(Shader shader);
	
		Shader	shader;

	private:
		unsigned int	_FBO;
		unsigned int	_width = 4096 * 2;
		unsigned int	_height = 4096 * 2;
		unsigned int	_shadowMap;
};
