/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkLoader.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:48:11 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/09 10:44:00 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>
#include <Generation/Chunk.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <atomic>
#include <sstream>
#include <algorithm>

class Chunk;

class ChunkLoader
{
	public:
		ChunkLoader();
		ChunkLoader(const glm::vec4 &loadingSector);
		~ChunkLoader();

		std::unordered_map<std::string, Chunk>	getLoaded(const glm::vec4 &newLoadingSector);
		void									loaderRoutine();

	private:
		std::string	posToStr(const glm::vec2 &pos);
		glm::vec2	strToPos(const std::string &pos);

		glm::vec4								_loadingSector;
		glm::vec4								_originalSector;
		std::unordered_map<std::string, Chunk>	_loadedChunks;
		std::vector<std::string>				_loadedCoords;
		std::thread								_loader;
		std::atomic<bool>						_running;
		std::mutex								_loaderLock;
};
