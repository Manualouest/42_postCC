/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:57:38 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/03 17:19:06 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Generation/Chunk.hpp>

#include <iostream>
#include <bitset>

Chunk::Chunk()
{
}

Chunk::Chunk(const glm::vec2 &newPos)
{
	pos.x = (int)(newPos.x / 32.f) * 32;
	pos.y = (int)(newPos.y / 32.f) * 32;
	_indicesSize = 0;
	_minHeight = 255;
	_maxHeight = 0;

	load();
	genMesh(vertices, indices);

	_indicesSize = indices.size();

}

void		makeBuffers()
{
}

Chunk::~Chunk()
{
	_CVAO = VAO();
	_CVAO.Bind();
	_CVBO = VBO(vertices.data(), vertices.size() * sizeof(float));
	_CEBO = EBO((GLuint*)indices.data(), indices.size() * sizeof(GLuint));

	_CVAO.linkAttrib(_CVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	_CVAO.linkAttrib(_CVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	_CVAO.Unbind();
	_CVBO.Unbind();
	_CEBO.Unbind();
}

void	Chunk::remove()
{
	chunkData.clear();
	_CVAO.Delete();
	_CVBO.Delete();
	_CEBO.Delete();
}

void	Chunk::render()
{
	_CVAO.Bind();
	glDrawElements(GL_TRIANGLES, _indicesSize, GL_UNSIGNED_INT, 0);
}

void	Chunk::load()
{
	int	height;

	for (int i = 0; i < 32; ++i)
	{
		for (int ii = 0; ii < 32; ++ii)
		{
			// std::cout << pos.x + ii << ";" << pos.y + i << ", ";
			height = Perlin::computePerlin(glm::vec2{pos.x + (31 - ii), pos.y + i});
			std::unordered_map<int, char32_t>::iterator chunkSlice = chunkData.find(height * 32 + i);

			if (chunkSlice != chunkData.end())
				chunkSlice->second = chunkSlice->second | (char32_t)(((char32_t)1) << (31 - ii));
			else
				chunkData.insert(std::pair<int, char32_t>(height * 32 + i, (char32_t)(((char32_t)1) << (31 - ii))));

			if (height > _maxHeight)
				_maxHeight = height;
			if (height < _minHeight)
				_minHeight = height;
		}
		// std::cout << std::endl;
	}
	// std::cout << std::endl;

	for (int i = _maxHeight; i > 0; --i)
	{
		for (int ii = 0; ii < 32; ++ii)
		{
			std::unordered_map<int, char32_t>::iterator chunkSlice = chunkData.find((i * 32 + ii));

			if (chunkSlice != chunkData.end())
			{
				std::unordered_map<int, char32_t>::iterator underSlice = chunkData.find(((i - 1) * 32 + ii));
				if (underSlice != chunkData.end())
					underSlice->second = underSlice->second | chunkSlice->second;
				else
					chunkData.insert(std::pair<int, char32_t>(((i - 1) * 32 + ii), chunkSlice->second));
			}
			else
			{
				if (i > _minHeight)
					chunkData.insert(std::pair<int, char32_t>((i * 32 + ii), 0));
				else
					chunkData.insert(std::pair<int, char32_t>((i * 32 + ii), char32_t(2147483648)));
			}
		}
	}
	for (int i = 0; i < 32; ++i)
	{
		std::unordered_map<int, char32_t>::iterator chunkSlice = chunkData.find((i));
		if (chunkSlice == chunkData.end())
			chunkData.insert(std::pair<int, char32_t>((i), char32_t(2147483648)));
	}
}

char32_t	Chunk::culling(const char32_t &slice, const bool &dir, const int &edge)
{
	if (dir)
		return (slice & ~((slice << 1) | edge)); // right faces
	else
		return (slice & ~((slice >> 1) | (edge << 31))); // left faces
}

void	Chunk::getRotSlice(std::vector<char32_t> &rotSlice, const int &height)
{
	char32_t slice;
	for (int i = 0; i < 32; ++i)
	{
		slice = chunkData.find((height + i))->second;
		for (int ii = 0; ii < 32; ++ii)
			rotSlice[ii] = rotSlice[ii] << 1 | (((slice >> (31 - ii)) & 1));
	}
}

void	addVertices(std::vector<float> &vertices, std::vector<int> &indices, const glm::vec3 &TL, const glm::vec3 &TR, const glm::vec3 &BL, const glm::vec3 &BR)
{
	vertices.insert(vertices.end(), {BL.x, BL.y, BL.z, 0, 0, TL.x, TL.y, TL.z, 0, 1, TR.x, TR.y, TR.z, 1, 1, BR.x, BR.y, BR.z, 1, 0});
	int vertLen = vertices.size() / 5 - 1;
	indices.insert(indices.end(), {vertLen - 3, vertLen - 1, vertLen - 2, vertLen - 3, vertLen - 0, vertLen - 1});
}

void	Chunk::genMesh(std::vector<float> &vertices, std::vector<int> &indices)
{
	char32_t				chunkSlice;
	std::vector<char32_t>	rotSlices;
	rotSlices.reserve(32);

	for (int i = 0; i <= _maxHeight; ++i)
	{
		rotSlices.clear();
		getRotSlice(rotSlices, i * 32);
		for (int ii = 0; ii < 32; ++ii)
		{
			chunkSlice = chunkData.find((i * 32 + ii))->second;
			// if (!chunkSlice && !rotSlices[ii])
			// 	continue;
			char32_t westFaces = culling(chunkSlice, true, int(Perlin::computePerlin(glm::vec2{pos.x - 1, pos.y + ii})) >= i);
			char32_t eastFaces = culling(chunkSlice, false, int(Perlin::computePerlin(glm::vec2{pos.x + 32, pos.y + ii})) >= i);
			char32_t northFaces = culling(rotSlices[ii], true, int(Perlin::computePerlin(glm::vec2{pos.x + (31 - ii), pos.y + 32})) >= i);
			char32_t southFaces = culling(rotSlices[ii], false, int(Perlin::computePerlin(glm::vec2{pos.x + (31 - ii), pos.y - 1})) >= i);

			for (int iii = 0; iii < 32; ++iii)
			{
				if ((westFaces >> iii) & 1)
					addVertices(vertices, indices, {0 + pos.x + iii, 1 + i, 1 + pos.y + ii}, {0 + pos.x + iii, 1 + i, 0 + pos.y + ii}, {0 + pos.x + iii, 0 + i, 1 + pos.y + ii}, {0 + pos.x + iii, 0 + i, 0 + pos.y + ii});
				if ((eastFaces >> iii) & 1)
					addVertices(vertices, indices, {1 + pos.x + iii, 1 + i, 0 + pos.y + ii}, {1 + pos.x + iii, 1 + i, 1 + pos.y + ii}, {1 + pos.x + iii, 0 + i, 0 + pos.y + ii}, {1 + pos.x + iii, 0 + i, 1 + pos.y + ii});
				if ((northFaces >> iii) & 1)
					addVertices(vertices, indices, {1 + pos.x + (31 - ii), 1 + i, 1 + pos.y + (31 - iii)}, {0 + pos.x + (31 - ii), 1 + i, 1 + pos.y + (31 - iii)}, {1 + pos.x + (31 - ii), 0 + i, 1 + pos.y + (31 - iii)}, {0 + pos.x + (31 - ii), 0 + i, 1 + pos.y + (31 - iii)});
				if ((southFaces >> iii) & 1)
					addVertices(vertices, indices, {0 + pos.x + (31 - ii), 1 + i, 0 + pos.y + (31 - iii)}, {1 + pos.x + (31 - ii), 1 + i, 0 + pos.y + (31 - iii)}, {0 + pos.x + (31 - ii), 0 + i, 0 + pos.y + (31 - iii)}, {1 + pos.x + (31 - ii), 0 + i, 0 + pos.y + (31 - iii)});
			
				if ((chunkSlice >> iii) & 1 && 
					(chunkData.find(((i + 1) * 32 + ii)) != chunkData.end() && !((chunkData.find(((i + 1) * 32 + ii))->second >> iii) & 1)
						|| chunkData.find(((i + 1) * 32 + ii)) == chunkData.end()))
					addVertices(vertices, indices, {0 + pos.x + iii, 1 + i, 1 + pos.y + ii}, {1 + pos.x + iii, 1 + i, 1 + pos.y + ii}, {0 + pos.x + iii, 1 + i, 0 + pos.y + ii}, {1 + pos.x + iii, 1 + i, 0 + pos.y + ii});
				
			}
		}
	}
	// if (_minHeight == _maxHeight)
	// {
	// 	std::cout << "empty chunk pos: " << pos.x << "; " << pos.y << std::endl;
	// 	for (int i = 0; i < 32; ++i)
	// 	{
	// 		for (int ii = 0; ii < 32; ++ii)
	// 		{
	// 			addVertices(vertices, indices, {0 + pos.x + ii, 10, 1 + pos.y + i}, {1 + pos.x + ii, 10, 1 + pos.y + i}, {0 + pos.x + ii, 10, 0 + pos.y + i}, {1 + pos.x + ii, 10, 0 + pos.y + i});
	// 		}
	// 	}
	// }
}

