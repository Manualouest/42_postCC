/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkLoader.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:47:30 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/09 11:39:39 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ChunkLoader/ChunkLoader.hpp>

ChunkLoader::ChunkLoader()
{
	_loadingSector = {0, 0, 0, 0};
	_originalSector = _loadingSector;
	_running.store(true);
	// _loader = std::thread(&ChunkLoader::loaderRoutine, this);
}

ChunkLoader::ChunkLoader(const glm::vec4 &loadingSector)
{
	_loadingSector = loadingSector;
	_originalSector = _loadingSector;
	_running.store(true);
	_loader = std::thread(&ChunkLoader::loaderRoutine, this);
}

ChunkLoader::~ChunkLoader()
{
	_running.store(false);
	for (std::unordered_map<std::string, Chunk>::iterator it = _loadedChunks.begin(); it != _loadedChunks.end(); ++it)
		it->second.remove();
}

std::unordered_map<std::string, Chunk>	ChunkLoader::getLoaded(const glm::vec4 &newLoadingSector)
{
	_loaderLock.lock();
	std::unordered_map<std::string, Chunk>	loadedcopy(_loadedChunks);
	_loadedChunks.clear();
	if (_originalSector != newLoadingSector)
	{
		_loadingSector = newLoadingSector;
		_originalSector = _loadingSector;
	}
	_loaderLock.unlock();
	return loadedcopy;
}

void	ChunkLoader::loaderRoutine()
{
	while(_running.load())
	{

		for (;_loadingSector.x <= _loadingSector.y; ++_loadingSector.x)
		{
			for (; _loadingSector.z <= _loadingSector.w; ++_loadingSector.z)
			{
				if (!_running.load())
					return ;
				_loaderLock.lock();
				if (std::find(_loadedCoords.begin(), _loadedCoords.end(), posToStr({_loadingSector.z, _loadingSector.x})) == _loadedCoords.end())
				{
					_loadedChunks.insert({posToStr({_loadingSector.z, _loadingSector.x}), Chunk({_loadingSector.z * 32, _loadingSector.x * 32})});
					_loadedCoords.insert(_loadedCoords.end(), posToStr({_loadingSector.z, _loadingSector.x}));
				}
				_loaderLock.unlock();
			}
		}

	}
}

std::string	ChunkLoader::posToStr(const glm::vec2 &pos)
{
	std::stringstream	posStr;
	posStr << pos.x << ";" << pos.y;
	return (posStr.str());
}

glm::vec2	ChunkLoader::strToPos(const std::string &pos)
{
	glm::vec2	cPos = {atol(pos.substr(0, pos.find(';')).c_str()), atol(pos.substr(pos.find(';') + 1, pos.length()).c_str())};
	return (cPos);
}
