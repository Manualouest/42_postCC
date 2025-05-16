/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:20:55 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/09 11:18:08 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Generation/Perlin.hpp>
#include <Buffers/VBO.hpp>
#include <Buffers/VAO.hpp>
#include <Buffers/EBO.hpp>

class Chunk
{
	public:
		Chunk();
		Chunk(const glm::vec2 &newPos);
		~Chunk();

		void		render();
		void		load();
		void		unload();
		void		reload();
		void		remove();

		std::unordered_map<int, char32_t>	chunkData;
		glm::vec2							pos;

	private:
		char32_t	culling(const char32_t &slice, const bool &dir, const int &edge);
		void		genMesh(std::vector<float> &vertices, std::vector<int> &indices);
		void		getRotSlice(std::vector<char32_t> &rotSlice, const int &height);
		void		makeBuffers();

		VAO					_CVAO;
		VBO					_CVBO;
		EBO					_CEBO;
		int					_indicesSize;
		unsigned int		_minHeight:8;
		unsigned int		_maxHeight:8;
		bool				_meshMade;
		bool				_unloaded;
		std::vector<float>	vertices;
		std::vector<int>	indices;
};
