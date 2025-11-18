/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:40:12 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/18 22:39:14 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_HPP
# define CHUNK_HPP

# include <Engine/Render/ShaderManager.hpp>

# include <map>
# include <vector>

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

struct Layer;

class Chunk
{
	public:
		Chunk();
		~Chunk();

		void	draw();
		void	unload();
		void	upload();
		void	remove();

		void	generate(const glm::vec2 &pos) {generate(pos, DEFAULT_BLOCKSIZE, DEFAULT_CHUNKSIZE);}
		void	generate(const glm::vec2 &pos, const float &blocksize, const float &chunksize);

		static float	BLOCKSIZE;
		static float	CHUNKSIZE;

	private:
		float	_genHeight(const glm::vec2 &pos);
		void	_addVertex(const glm::dvec3 &pos);
		void	_genLayers();
		void	_genBuffers();

		bool	_uploaded = false;
		bool	_generated = false;
		int		_nbVertices = 0;
		GLuint	_VAO = 0;
		GLuint	_VBO = 0;

		glm::vec2	_pos;
		glm::mat4	_matrice;

		std::map<float, Layer>	_RawLayers;
		std::vector<uint64_t>	_vertices;
};

struct Layer
{
	Layer() {blocks.resize(Chunk::CHUNKSIZE * Chunk::CHUNKSIZE / (Chunk::BLOCKSIZE * Chunk::BLOCKSIZE), 0);}

	std::vector<uint8_t>	blocks;
};

#endif