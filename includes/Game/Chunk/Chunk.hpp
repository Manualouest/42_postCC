/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:40:12 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/24 18:39:43 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_HPP
# define CHUNK_HPP

# include <Engine/Render/ShaderManager.hpp>

# include <map>
# include <vector>
# include <bitset>

# include <glad/glad.h>
# include <glfw/glfw3.h>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>


// blank 64bits 0b0000000000000000000000000000000000000000000000000000000000000000
# define CNORM	0b0000000000000000000000111000000000000000000000000000000000000000
# define CX_POS	0b0000000000000000000000000111111111111000000000000000000000000000
# define CY_POS	0b0000000000000000000000000000000000000111111111111111000000000000
# define CZ_POS	0b0000000000000000000000000000000000000000000000000000111111111111

# define CN_OFFSET	39
# define CX_OFFSET	27
# define CY_OFFSET	12
# define CZ_OFFSET	0

# define DEFAULT_BLOCKSIZE	1.f
# define DEFAULT_CHUNKSIZE	32.f

struct Strip
{
	float	height, size;
	uint8_t	type;
};

enum Normals
{
	TOP,
	BOT,
	WEST,
	EAST,
	NORTH,
	SOUTH
};

enum BlockTypes
{
	AIR,
	GRASS,
	DIRT,
	STONE
};

class Chunk
{
	public:
		Chunk();
		~Chunk();

		void	draw();
		void	unload();
		void	upload();
		void	remove();

		glm::vec2	getPos() const {return(_pos);}

		void	regenerate(const glm::vec2 &pos, const float &blocksize, const float &chunksize, const float &targetSize) {remove(); generate(pos, blocksize, chunksize, targetSize);}
		void	changeLOD(const float &targetSize) {unload(); _usedBlocksize = targetSize; _LOD = _usedBlocksize / BLOCKSIZE; /*PRINT _usedBlocksize AND "; " AND _LOD ENDL*/; _genVertices();}
		void	generate(const glm::vec2 &pos) {generate(pos, DEFAULT_BLOCKSIZE, DEFAULT_CHUNKSIZE);}
		void	generate(const glm::vec2 &pos, const float &blocksize, const float &chunksize) {generate(pos, blocksize, chunksize, 1);}
		void	generate(const glm::vec2 &pos, const float &blocksize, const float &chunksize, const float &targetSize);

		static float	BLOCKSIZE;
		static float	CHUNKSIZE;

	private:
		float	_genHeight(const glm::vec2 &pos);
		void	_addVertex(const glm::dvec3 &pos, const uint64_t &normID);
		void	_genLayers();
		float	calFaceSize(const Strip &strip, const std::vector<Strip> &oppositeStrip);
		void	addIndexes(const glm::ivec3 &indexes);
		void	_genVertices();

		bool	_uploaded = false;
		bool	_generated = false;
		int		_nbVertices = 0;
		int		_nbIndices = 0;
		GLuint	_VAO = 0;
		GLuint	_VBO = 0;
		GLuint	_EBO = 0;

		float	_usedBlocksize;
		float	_LOD;

		glm::vec2	_pos = {0, 0};
		glm::mat4	_matrice;

		std::vector<std::vector<Strip>>		_strips;
		std::vector<uint64_t>				_vertices;
		std::vector<int>					_indices;

		// old one
		std::vector<float>					_RawChunk;
};


#endif