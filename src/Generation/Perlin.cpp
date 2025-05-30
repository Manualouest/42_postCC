/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Perlin.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:44:08 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/03 15:51:21 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Generation/Perlin.hpp>

glm::vec2		Perlin::ChunkGrad[4 * 5] = {glm::vec2{0, 0}};
unsigned int	Perlin::seed = 0;
unsigned int	Perlin::nbFract = 1;

void	Perlin::setupSeed(const unsigned int &nSeed)
{
	seed = nSeed;
}

float	Perlin::computePerlin(const glm::vec2 &pointCoord)
{
	// precomputeChunkPerlin({(int)pointCoord.x, (int)pointCoord.y});
	// // PRINT "coords: " AND pointCoord.x AND ";" AND pointCoord.y AND ", " AND pointCoord.x - (int)pointCoord.x AND ";" AND pointCoord.y - (int)pointCoord.y CENDL;
	// return (getChunkPerlin({pointCoord.x - (int)pointCoord.x, pointCoord.y - (int)pointCoord.y}));
	return ((sin(pointCoord.x * 0.04f) + sin(pointCoord.y * 0.04f) + 2.f) / 4.f * 30.f);
}

glm::vec2 Perlin::randomGradient(const int &ix, const int &iy)
{
	// No precomputed gradients mean this works for any number of grid coordinates
	
	// unsigned w = 8 * sizeof(unsigned);
	// unsigned s = w / 2; 
	// unsigned a = ix;
	// unsigned b = iy;
	// a *= seed; //3284157443

	// b ^= a << s | (a >> w) - s;
	// b *= seed << 1; //1911520717

	// a ^= b << s | (b >> w) - s;
	// a *= seed >> 1; //2048419325
	// float random = a * (3.14159265 / (seed == 0 ? 1 : seed)); //~(~0u >> 1) // in [0, 2*Pi]


	float random = (ix + iy * seed);

	// Create the vector from the angle
	glm::vec2 v;
	v.x = sin(random);
	v.y = cos(random);

	return v;
}

void	Perlin::precomputeChunkPerlin(const glm::vec2 &chunkCoord)
{
	if (ChunkGrad[0] == glm::vec2{chunkCoord.x, chunkCoord.y}
		&& ChunkGrad[1] == glm::vec2{chunkCoord.x + 1, chunkCoord.y}
		&& ChunkGrad[2] == glm::vec2{chunkCoord.x, chunkCoord.y + 1}
		&& ChunkGrad[3] == glm::vec2{chunkCoord.x + 1, chunkCoord.y + 1})
		return;
	for (int i = 0; i < nbFract; ++i)
	{
		ChunkGrad[0 + i * 4] = randomGradient(chunkCoord.x - i, chunkCoord.y - i);
		ChunkGrad[1 + i * 4] = randomGradient(chunkCoord.x + 1 + i, chunkCoord.y - i);
		ChunkGrad[2 + i * 4] = randomGradient(chunkCoord.x - i, chunkCoord.y + 1 + i);
		ChunkGrad[3 + i * 4] = randomGradient(chunkCoord.x + 1 + i, chunkCoord.y + 1 + i);
		// PRINT ChunkGrad[0 + i * 4].x AND ": " AND ChunkGrad[0 + i * 4].y AND ", " AND
		// 	ChunkGrad[1 + i * 4].x AND ": " AND ChunkGrad[1 + i * 4].y AND ", " AND
		// 	ChunkGrad[2 + i * 4].x AND ": " AND ChunkGrad[2 + i * 4].y AND ", " AND
		// 	ChunkGrad[3 + i * 4].x AND ": " AND ChunkGrad[3 + i * 4].y CENDL;
	}
}

float	interpolate(const float &a0, const float &a1, const float &w)
{
	return ((a1 - a0) * (3.f - w * 2.f) * w * w + a0);
}

float	Perlin::getChunkPerlin(const glm::vec2 &pointCoord)
{
	float	val = 0;
	float	amp = 1;
	for (int i = 0; i < nbFract; ++i)
	{
		float	n0 = (pointCoord.x * ChunkGrad[0 + i * 4].x + pointCoord.y * ChunkGrad[0 + i * 4].y);
		float	n1 = (pointCoord.x * ChunkGrad[1 + i * 4].x + pointCoord.y * ChunkGrad[1 + i * 4].y);
		// PRINT "(no: " AND pointCoord.x AND ", n1: " AND pointCoord.y AND "), ";
		float	ix0 = interpolate(n0, n1, pointCoord.x);
		// PRINT "ix0: " AND val AND ", ";

		n0 = (pointCoord.x * ChunkGrad[2 + i * 4].x + pointCoord.y * ChunkGrad[2 + i * 4].y);
		n1 = (pointCoord.x * ChunkGrad[3 + i * 4].x + pointCoord.y * ChunkGrad[3 + i * 4].y);
		float	ix1 = interpolate(n0, n1, pointCoord.x);
		// PRINT "ix1: " AND val AND ", ";
		val += interpolate(ix0, ix1, pointCoord.y) * amp;
		// PRINT "val: " AND val AND ", ";

		amp /= 2;
	}
	if (val > 1)
		return 1;
	if (val < -1)
		return -1;

	// NEWL;
	// NEWL;

	return (val);
}
