/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Perlin.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:44:08 by mbirou            #+#    #+#             */
/*   Updated: 2025/04/16 19:48:11 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Generation/Perlin.hpp>

glm::vec2		Perlin::ChunkGrad[4] = {glm::vec2{0, 0}, glm::vec2{0, 0}, glm::vec2{0, 0}, glm::vec2{0, 0}};
unsigned int	Perlin::seed = 0;

void	Perlin::setupSeed(const unsigned int &nSeed)
{
	seed = nSeed;
}

int	Perlin::computePerlin(const glm::vec2 &pointCoord)
{
	precomputeChunkPerlin({(int)pointCoord.x, (int)pointCoord.y});
	return (getChunkPerlin({pointCoord.x - (int)pointCoord.x, pointCoord.y - (int)pointCoord.y}));
}

glm::vec2 randomGradient(const int &ix, const int &iy, const unsigned int &seed)
{
	// No precomputed gradients mean this works for any number of grid coordinates
	unsigned w = 8 * sizeof(unsigned);
	unsigned s = w / 2; 
	unsigned a = ix;
	unsigned b = iy;
	a *= seed; //3284157443

	b ^= a << s | (a >> w) - s;
	b *= seed << 1; //1911520717

	a ^= b << s | (b >> w) - s;
	a *= seed >> 1; //2048419325
	float random = a * (3.14159265 / (seed == 0 ? 1 : seed)); //~(~0u >> 1) // in [0, 2*Pi]

	// Create the vector from the angle
	glm::vec2 v;
	v.x = sin(random);
	v.y = cos(random);

	return v;
}

void	Perlin::precomputeChunkPerlin(const glm::vec2 &chunkCoord)
{
	ChunkGrad[0] = randomGradient(chunkCoord.x, chunkCoord.y, seed);
	ChunkGrad[1] = randomGradient(chunkCoord.x + 1, chunkCoord.y, seed);
	ChunkGrad[2] = randomGradient(chunkCoord.x, chunkCoord.y + 1, seed);
	ChunkGrad[3] = randomGradient(chunkCoord.x + 1, chunkCoord.y + 1, seed);
}

float	interpolate(const float &a0, const float &a1, const float &w)
{
	return ((a1 - a0) * (3.f - w * 2.f) * w * w + a0);
}

int	Perlin::getChunkPerlin(const glm::vec2 &pointCoord)
{
	float	n0 = (pointCoord.x * ChunkGrad[0].x + pointCoord.y * ChunkGrad[0].y);
	float	n1 = (pointCoord.x * ChunkGrad[1].x + pointCoord.y * ChunkGrad[1].y);
	float	ix0 = interpolate(n0, n1, pointCoord.x);

	n0 = (pointCoord.x * ChunkGrad[2].x + pointCoord.y * ChunkGrad[2].y);
	n1 = (pointCoord.x * ChunkGrad[3].x + pointCoord.y * ChunkGrad[3].y);
	float	ix1 = interpolate(n0, n1, pointCoord.x);

	return (interpolate(ix0, ix1, pointCoord.y));
}
