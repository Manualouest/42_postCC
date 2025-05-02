/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:57:38 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/02 19:30:43 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Generation/Chunk.hpp>

#include <iostream>
#include <bitset>

Chunk::Chunk(const glm::vec2 &newPos)
{
	pos.x = (int)(newPos.x / 32.f) * 32;
	pos.y = (int)(newPos.y / 32.f) * 32;
	_indicesSize = 0;
	_minHeight = 255;
	_maxHeight = 0;

	std::vector<float> vertices;
	std::vector<int> indices;

	load();
	genMesh(vertices, indices);

	_indicesSize = indices.size();

	_CVAO.Bind();
	_CVBO = VBO(vertices.data(), vertices.size());
	_CEBO = EBO((GLuint*)indices.data(), indices.size());

	_CVAO.linkAttrib(_CVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	_CVAO.linkAttrib(_CVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	_CVAO.Unbind();
	_CVBO.Unbind();
	_CEBO.Unbind();
}

Chunk::~Chunk()
{}

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
			height = (Perlin::computePerlin(glm::vec2{pos.x + ii, pos.y + i}) + 1.f) * 0.5f * 3.f;
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
	}

	for (int i = _maxHeight; i > _minHeight; --i)
	{
		for (int ii = 0; ii < 32; ++ii)
		{
			std::unordered_map<int, char32_t>::iterator chunkSlice = chunkData.find((i * 32 + ii));

			if (chunkSlice != chunkData.end())
			{
				std::unordered_map<int, char32_t>::iterator underSlice = chunkData.find(((i - 1) * 32 + ii));
				if (underSlice != chunkData.end())
				{
					underSlice->second = underSlice->second | chunkSlice->second;
				}
				else
					chunkData.insert(std::pair<int, char32_t>(((i - 1) * 32 + ii), chunkSlice->second));
			}
			else
			{
				chunkData.insert(std::pair<int, char32_t>((i * 32 + ii), 0));
				continue;
			}
		}
	}
}
char32_t	Chunk::culling(const char32_t &slice, const bool &dir)
{
	if (dir)
	{
		std::bitset<32> bits = slice;
		std::cout << bits << ";  ";
		bits = slice & ~(slice << 1);
		std::cout << bits << std::endl;
		return (slice & ~(slice << 1)); // right faces
	}
	else
	{
		std::bitset<32> bits = slice;
		std::cout << bits << ";  ";
		bits = slice & ~(slice >> 1);
		std::cout << bits << std::endl;
		return (slice & ~(slice >> 1)); // left faces
	}
}

void	Chunk::getRotSlice(std::vector<char32_t> &rotSlice, const int &height)
{
	std::vector<char32_t> slice;
	slice.reserve(32);
	for (int i = 0; i < 32; ++i)
	{
		if (chunkData.find((height + i)) != chunkData.end())
			slice[i] = chunkData.find((height + i))->second;
		else
			std::cout << height << "; " << i << std::endl;
	}
	for (int i = 0; i < 32; ++i)
	{
		for (int ii = 0; ii < 32; ++ii)
			rotSlice[i] = rotSlice[i] | (slice[ii] << (31 - ii));
	}
}

void	addVertices(std::vector<float> &vertices, std::vector<int> &indices, const glm::vec3 &TL, const glm::vec3 &TR, const glm::vec3 &BL, const glm::vec3 &BR)
{
	std::cout << TL.x << "," << TL.y << "," << TL.z << "; " << TR.x << "," << TR.y << "," << TR.z << "; " << BL.x << "," << BL.y << "," << BL.z << "; " << BR.x << "," << BR.y << "," << BR.z << std::endl;
	vertices.insert(vertices.end(), {BL.x, BL.y, BL.z, 0, 0, TL.x, TL.y, TL.z, 0, 1, TR.x, TR.y, TR.z, 1, 1, BR.x, BR.y, BR.z, 1, 0});
	int vertLen = vertices.size() / 5 - 1;
	std::cout << vertLen << std::endl;
	indices.insert(indices.end(), {vertLen - 3, vertLen - 1, vertLen - 2, vertLen - 3, vertLen - 0, vertLen - 1});
	std::cout << indices.size() << std::endl;
	std::cout << indices[indices.size() - 6] << ", " << indices[indices.size() - 5] << ", " << indices[indices.size() - 4] << ", " << indices[indices.size() - 3] << ", " << indices[indices.size() - 2] << ", " << indices[indices.size() - 1] << std::endl;
}

void	Chunk::genMesh(std::vector<float> &vertices, std::vector<int> &indices)
{
	std::unordered_map<int, char32_t>::iterator chunkSlice;
	std::vector<char32_t>						rotSlices;
	rotSlices.reserve(32);

	for (int i = _minHeight; i < _maxHeight; ++i)
	{
		getRotSlice(rotSlices, i * 32);
		for (int ii = 0; ii < 32; ++ii)
		{
			chunkSlice = chunkData.find((i * 32 + ii));
			if (!chunkSlice->second)
				continue;
			char32_t westFaces = culling(chunkSlice->second, false);
			char32_t eastFaces = culling(chunkSlice->second, true);
			char32_t northFaces = culling(rotSlices[ii], false);
			char32_t southFaces = culling(rotSlices[ii], true);

			std::cout << std::endl;
			// std::bitset<32> bits = westFaces;
			// std::bitset<32> bits1 = eastFaces;
			// std::bitset<32> bits2 = northFaces;
			// std::bitset<32> bits3 = southFaces;
			// std::cout << bits << std::endl << bits1 << std::endl << bits2 << std::endl << bits3 << std::endl << std::endl;

			for (int iii = 0; iii < 32; ++iii)
			{
				if ((westFaces >> iii) & 1)
				{
					std::cout << "yes1" << std::endl;
					addVertices(vertices, indices, {pos.x + iii, i + 1, pos.y + 1 + ii}, {pos.x + iii, i + 1, pos.y + ii}, {pos.x + iii, i, pos.y + 1 + ii}, {pos.x + iii, i, pos.y + ii});
					// addVertices(vertices, indices, {-0.5, 0.5, 0}, {0.5, 0.5, 0}, {-0.5, -0.5, 0}, {0.5, -0.5, 0});
				}
				if ((eastFaces >> iii) & 1)
				{
					std::cout << "yes2" << std::endl;
					addVertices(vertices, indices, {pos.x + (31 - iii), i + 1, pos.y + (32 - ii)}, {pos.x + (31 - iii), i + 1, pos.y + 1 + (32 - ii)}, {pos.x + (31 - iii), i, pos.y + (32 - ii)}, {pos.x + (31 - iii), i, pos.y + 1 + (32 - ii)});
					// addVertices(vertices, indices, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0});
				}
				if ((northFaces >> iii) & 1)
				{
					std::cout << "yes3" << std::endl;
					addVertices(vertices, indices, {pos.x + 1 + ii, i + 1, pos.y + iii}, {pos.x + ii, i + 1, pos.y + iii}, {pos.x + 1 + ii, i, pos.y + iii}, {pos.x + ii, i, pos.y + iii});
					// addVertices(vertices, indices, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0});
				}
				if ((southFaces >> iii) & 1)
				{
					std::cout << "yes4" << std::endl;
					addVertices(vertices, indices, {pos.x + (32 - ii), i + 1, pos.y + (31 - iii)}, {pos.x + 1 + (32 - ii), i + 1, pos.y + (31 - iii)}, {pos.x + (32 - ii), i, pos.y + (31 - iii)}, {pos.x + 1 + (32 - ii), i, pos.y + (31 - iii)});
					// addVertices(vertices, indices, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0});
				}
			}
		}
	}
}

