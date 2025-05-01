/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:49:27 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/01 13:07:09 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Generation/Chunk.hpp>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
