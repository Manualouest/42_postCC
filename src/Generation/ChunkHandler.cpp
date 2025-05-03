/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:48:31 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/03 15:26:19 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Generation/ChunkHandler.hpp>

ChunkHandler::ChunkHandler()
{
	_chunkPos = {-1, -1};
}

ChunkHandler::~ChunkHandler()
{
	// for (std::unordered_map<std::string, Chunk>::iterator it = _chunks.begin(); it != _chunks.end(); ++it)
		// it->second.remove();
}

std::string	ChunkHandler::posToStr(const glm::vec2 &pos)
{
	std::stringstream	posStr;
	posStr << pos.x << ";" << pos.y;
	return (posStr.str());
}

bool	ChunkHandler::isInRender(const std::string &pos)
{
	glm::vec2	cPos = {atol(pos.substr(0, pos.find(';')).c_str()), atol(pos.substr(pos.find(';') + 1, pos.length()).c_str())};
	return (pow(cPos.x - _chunkPos.x, 2) + pow(cPos.y - _chunkPos.y, 2) <= _renderDist);
}

void	ChunkHandler::UpdateChunks(const glm::vec3 &pointCoord, const glm::vec3 &orient)
{
	// if (_chunkPos == glm::vec2{int(pointCoord.x / 32), int(pointCoord.z / 32)})
	// {
	// 	return;
	// }
	_chunkPos = glm::vec2{int(pointCoord.x / 32), int(pointCoord.z / 32)};

	// float angle = atan2(1, 0) - atan2(orient.z, orient.x);
	// if (angle < 0) {angle += 2 * M_PI;}
	// std::cout << orient.x << "; " << orient.z << ": " << angle << std::endl;

	for (std::unordered_map<std::string, Chunk>::iterator it = _chunks.begin(); it != _chunks.end();)
	{
		if (!isInRender(it->first))
		{
			it->second.remove();
            it = _chunks.erase(it);
		}
        else
            ++it;
	}

	int maxloaded = 1;

	for (int i = _chunkPos.y - _renderRad; i <= _chunkPos.y + _renderRad; ++i)
	{
		for (int ii = _chunkPos.x - _renderRad; ii <= _chunkPos.x + _renderRad; ++ii)
		{
			if (isInRender(posToStr({ii, i})) && _chunks.find(posToStr({ii, i})) == _chunks.end())
			{
				_chunks.insert({posToStr({ii, i}), Chunk({ii * 32, i * 32})});
				maxloaded -= 1;
			}
			if (maxloaded < 0)
				return ;
		}
	}
}
void	ChunkHandler::RenderChunks()
{
	for (std::unordered_map<std::string, Chunk>::iterator it = _chunks.begin(); it != _chunks.end(); ++it)
	{
		// std::cout << it->second.pos.x << ": " << it->second.pos.y << std::endl;
		it->second.render();
	}
}
