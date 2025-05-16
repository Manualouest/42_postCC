/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:49:27 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/09 11:43:35 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Generation/Chunk.hpp>
#include <ChunkLoader/ChunkLoader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <includes.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>

#define M_PI2 M_PI * 2
#define M_PI1Q M_PI * 0.25
#define M_PI1T M_PI * 0.5
#define M_PI3Q M_PI * 0.75

class ChunkHandler
{
	public:
		ChunkHandler();
		~ChunkHandler();

		void	UpdateChunks(const glm::vec3 &pointCoord, const glm::vec3 &orient, GLFWwindow *window);
		void	RenderChunks();
	
	private:
		std::string	posToStr(const glm::vec2 &pos);
		glm::vec2	strToPos(const std::string &pos);
		bool		isInRender(const std::string &pos);
		bool		isInFront(const glm::vec2 &pos);

		// ChunkLoader								_loader;
		std::unordered_map<std::string, Chunk>	_chunks;
		// std::unordered_map<std::string, Chunk>	_tpChunks;
		glm::vec2								_chunkPos;
		float									_renderRad = 10.5; // related to dist, for the circle
		float									_renderDist = (int)(_renderRad * _renderRad) + 0.5f; // 10.5^2 + 0.25
		// float									_tpRenderRad = 10.5; // related to dist, for the circle
		// float									_tpRenderDist = (int)(_renderRad * _renderRad) + 0.5f; // 10.5^2 + 0.25
		bool									_showAll;
		float									_angle;
};
