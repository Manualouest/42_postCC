/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Perlin.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:18:12 by mbirou            #+#    #+#             */
/*   Updated: 2025/05/02 11:15:49 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Perlin
{
	public:
		static void		setupSeed(const unsigned int &seed);
		static float	computePerlin(const glm::vec2 &pointCoord);
		static void		precomputeChunkPerlin(const glm::vec2 &chunkCoord);
		static float	getChunkPerlin(const glm::vec2 &pointCoord);

	private:
		Perlin();
		~Perlin();

		static glm::vec2 randomGradient(const int &ix, const int &iy);

		static glm::vec2	ChunkGrad[4 * 5]; // there are 4 sets of points for earch angles then 5 sets of fract points
		static unsigned int	seed;
		static unsigned int	nbFract;
};