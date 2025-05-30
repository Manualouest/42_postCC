/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:48:31 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/09 13:32:46 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Generation/ChunkHandler.hpp>

ChunkHandler::ChunkHandler()// : _loader({-2, 0, -2, 0})
{
	_chunkPos = {-1, -1};
	_showAll = false;
	_angle = 0;
}

ChunkHandler::~ChunkHandler()
{
	for (std::unordered_map<std::string, Chunk>::iterator it = _chunks.begin(); it != _chunks.end(); ++it)
		it->second.remove();
}

std::string	ChunkHandler::posToStr(const glm::vec2 &pos)
{
	std::stringstream	posStr;
	posStr << pos.x << ";" << pos.y;
	return (posStr.str());
}

glm::vec2	ChunkHandler::strToPos(const std::string &pos)
{
	glm::vec2	cPos = {atol(pos.substr(0, pos.find(';')).c_str()), atol(pos.substr(pos.find(';') + 1, pos.length()).c_str())};
	return (cPos);
}

bool	ChunkHandler::isInRender(const std::string &pos)
{
	glm::vec2	cPos = {atol(pos.substr(0, pos.find(';')).c_str()), atol(pos.substr(pos.find(';') + 1, pos.length()).c_str())};
	return (pow(cPos.x - (_chunkPos.x + 1), 2) + pow(cPos.y - (_chunkPos.y + 1), 2) <= _renderDist);
}

bool	ChunkHandler::isInFront(const glm::vec2 &pos)
{
	if (_angle <= M_PI1Q || _angle >= M_PI + M_PI3Q)
		return (pos.y < _chunkPos.y);
	else if (_angle >= M_PI1Q && _angle <= M_PI3Q)
		return (pos.x < _chunkPos.x);
	else if (_angle >= M_PI3Q && _angle <= M_PI + M_PI1Q)
		return (pos.y > _chunkPos.y);
	else if (_angle >= M_PI +M_PI1Q && _angle <= M_PI + M_PI3Q)
		return (pos.x > _chunkPos.x);
	return (false);
}

void	ChunkHandler::UpdateChunks(const glm::vec3 &pointCoord, const glm::vec3 &orient, GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS && _renderRad < 50)
	{
		_renderRad ++;
		_renderDist = (int)(_renderRad * _renderRad) + 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && _renderRad > 1)
	{
		_renderRad --;
		_renderDist = (int)(_renderRad * _renderRad) + 0.5f;
	}

	_chunkPos = glm::vec2{int(pointCoord.x / 32), int(pointCoord.z / 32)};
	_angle = atan2(0, 0) - atan2(orient.z, orient.x) - M_PI / 2.0f;
	
	if (_angle < 0) {_angle += M_PI2;}
	if (_angle > M_PI2) {_angle -= M_PI2;}

	for (std::unordered_map<std::string, Chunk>::iterator it = _chunks.begin(); it != _chunks.end(); ++it)
		if (!isInRender(it->first))
			it->second.unload();

	int maxloaded = 1;

	int	starty = _chunkPos.y - 1;
	int	endy = _chunkPos.y + 1;
	int	startx = _chunkPos.x - 1;
	int	endx = _chunkPos.x + 1;

	if (orient.y > -0.9)
	{
		_showAll = true;
		if (_angle <= M_PI1Q || _angle >= M_PI + M_PI3Q)
		{
			starty -= _renderRad;
			startx -= _renderRad;
			endx += _renderRad;
		}
		else if (_angle >= M_PI1Q && _angle <= M_PI3Q)
		{
			startx -= _renderRad;
			starty -= _renderRad;
			endy += _renderRad;
		}
		else if (_angle >= M_PI3Q && _angle <= M_PI + M_PI1Q)
		{
			endy += _renderRad;
			startx -= _renderRad;
			endx += _renderRad;
		}
		else if (_angle >= M_PI +M_PI1Q && _angle <= M_PI + M_PI3Q)
		{
			endx += _renderRad;
			starty -= _renderRad;
			endy += _renderRad;
		}
	}
	else
	{
		_showAll = true;
		starty -= _renderRad;
		endy += _renderRad;
		startx -= _renderRad;
		endx += _renderRad;
	}


	for (int i = starty; i < endy;++i)
	{
		for (int ii = startx; ii < endx; ++ii)
			if (isInRender(posToStr({ii, i})) && _chunks.find(posToStr({ii, i})) == _chunks.end())
				_chunks.insert({posToStr({ii, i}), Chunk({ii * 32, i * 32})});
	}

	// _tpChunks = _loader.getLoaded({starty, endy, startx, endx});
	// _chunks.insert(_tpChunks.begin(), _tpChunks.end());
}
void	ChunkHandler::RenderChunks()
{
	for (std::unordered_map<std::string, Chunk>::iterator it = _chunks.begin(); it != _chunks.end(); ++it)
		if (isInRender(it->first) && (_showAll || isInFront(strToPos(it->first))))
			it->second.render();
}
