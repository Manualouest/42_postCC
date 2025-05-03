/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:49:27 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/03 15:26:40 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Generation/Chunk.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>

class Chunk;

class ChunkHandler
{
	public:
		ChunkHandler();
		~ChunkHandler();

		void	UpdateChunks(const glm::vec3 &pointCoord, const glm::vec3 &orient);
		void	RenderChunks();
	
	private:
		std::string	posToStr(const glm::vec2 &pos);
		bool		isInRender(const std::string &pos);

		std::unordered_map<std::string, Chunk>	_chunks;
		glm::vec2								_chunkPos;
		float									_renderDist = 930.5; // 10.5^2 + 0.25
		float									_renderRad = 30.5; // related to dist, for the circle
};
