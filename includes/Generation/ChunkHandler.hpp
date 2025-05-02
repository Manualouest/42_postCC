/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:49:27 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/02 11:15:38 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Generation/Chunk.hpp>
#include <iostream>
#include <sstream>

class ChunkHandler
{
	public:
		ChunkHandler();
		~ChunkHandler();

		void	UpdateChunks(const glm::vec2 &pointCoord);
		void	RenderChunks();
	
	private:
		std::unordered_map<std::string, Chunk>	_chunks;
};
