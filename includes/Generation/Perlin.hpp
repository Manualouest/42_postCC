/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Perlin.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:18:12 by mbirou            #+#    #+#             */
/*   Updated: 2025/04/16 19:46:26 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Perlin
{
	public:
		static void	setupSeed(const unsigned int &seed);
		static int	computePerlin(const glm::vec2 &pointCoord);
		static void	precomputeChunkPerlin(const glm::vec2 &chunkCoord);
		static int	getChunkPerlin(const glm::vec2 &pointCoord);

	private:
		Perlin();
		~Perlin();

		static glm::vec2	ChunkGrad[4];
		static unsigned int	seed;
};