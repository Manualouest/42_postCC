/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:55:29 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/19 21:08:47 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Game/Chunk/Chunk.hpp>

float	Chunk::CHUNKSIZE = DEFAULT_CHUNKSIZE;
float	Chunk::BLOCKSIZE = DEFAULT_BLOCKSIZE;


// ========================== Since no noise yet =========================


float	noiseMapSize = 2;
int		noiseMap[2][2] = {
	{0, 1},
	{0, 1}
};

/*
	PRINT pos.x AND "; " AND pos.y AND ": " AND (pos.x + pos.y) / Chunk::CHUNKSIZE ENDL;

	return ((pos.x + pos.y) / Chunk::CHUNKSIZE);
*/


float	Chunk::_genHeight(const glm::vec2 &pos)
{
	float maxDist = glm::distance(glm::vec2{0, 0}, glm::vec2{Chunk::CHUNKSIZE / 2.f, Chunk::CHUNKSIZE / 2.f});
	// PRINT pos.x AND "; " AND pos.y AND ": " AND (pos.x + pos.y) / Chunk::CHUNKSIZE ENDL;
	return ((maxDist - glm::distance(pos, glm::vec2{Chunk::CHUNKSIZE / 2.f, Chunk::CHUNKSIZE / 2.f})));
	return (glm::mod((pos.x + pos.y), Chunk::BLOCKSIZE * 2.f));
}

int seed = 6967;

glm::vec2 randomGradient(int ix, int iy)
{
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443 + (seed + 1);

	b ^= a << s | a >> (w - s);
    b *= 1911520717;

	a ^= b << s | b >> (w - s);
    a *= 2048419325;
	float random = (a / (float)UINT_MAX) * 2.0f * M_PI;

	glm::vec2 v;
    v.x = sin(random);
    v.y = cos(random);

	return v;
}

float dotGridGradient(int ix, int iy, float x, float y)
{
    glm::vec2 gradient = randomGradient(ix, iy);

	float dx = x - (float)ix;
    float dy = y - (float)iy;

	return (dx * gradient.x + dy * gradient.y);
}

float interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float perlin(float x, float y)
{
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

	float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);

    float value = interpolate(ix0, ix1, sy);

    return (value);
}

float	calcNoise(const glm::vec2 &pos, float freq, float amp, int noisiness)
{
	float	res = 0;
	for (int i = 0; i < noisiness; i++)
	{
		res += perlin(pos.x * freq, pos.y * freq) * amp;

		freq *= 2;
		amp /= 2;
	}

	if (res > 1.0f)
		res = 1.0f;
	else if (res < -1.0f)
		res = -1.0f;

	return (res);
}

// =======================================================================


Chunk::Chunk()
{
}

Chunk::~Chunk()
{
	remove();
}

void	Chunk::draw()
{
	if (!_generated)
		return ;

	if (!_uploaded)
		upload();

	ShaderManager::setMat4("model", _matrice);

	// PRINT _nbVertices ENDL;

	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, _nbVertices);
	glBindVertexArray(0);
}

void	Chunk::unload()
{
	if (!_generated)
		return ;

	_uploaded = false;
	if (_VBO)
		glDeleteBuffers(1, &_VBO);
	_VBO = 0;
	if (_VAO)
		glDeleteVertexArrays(1, &_VAO);
	_VAO = 0;
}

void	Chunk::upload()
{
	if (!_generated)
		return ;

	if (_VAO <= 0)
		glGenVertexArrays(1, &_VAO);
	if (_VBO <= 0)
    	glGenBuffers(1, &_VBO);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(uint64_t), _vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribLPointer(0, 1, GL_DOUBLE, sizeof(uint64_t), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);	

	_vertices.clear();
	_vertices.shrink_to_fit();

	_uploaded = true;
}

void	Chunk::remove()
{
	_uploaded = false;
	_generated = false;

	if (_VBO)
		glDeleteBuffers(1, &_VBO);
	_VBO = 0;
	if (_VAO)
		glDeleteVertexArrays(1, &_VAO);
	_VAO = 0;

	_RawLayers.clear();
	_vertices.clear();
	_vertices.shrink_to_fit();
	_nbVertices = 0;
}

void	Chunk::generate(const glm::vec2 &pos, const float &blocksize, const float &chunksize, const float &targetSize)
{
	if (_generated)
		return;

	Chunk::BLOCKSIZE = blocksize;
	// Chunk::CHUNKSIZE = chunksize;
	Chunk::CHUNKSIZE = chunksize / blocksize;

	_usedBlocksize = targetSize;
	_LOD = _usedBlocksize / Chunk::BLOCKSIZE;

	_pos = pos;
	_matrice = glm::translate(glm::mat4(1.f), {pos.x, 0, pos.y});
	// _matrice = glm::mat4(1.f);

	_RawChunk.resize(Chunk::CHUNKSIZE * Chunk::CHUNKSIZE, 0);

	_genLayers();
	_genVertices();

	_generated = true;
}


float Increment(int dec, int inc)
{
	int mod = (dec % inc);
	return (dec - glm::abs(mod) + (inc < 0 && mod != 0 ? glm::abs(inc) : 0) + inc);
}

void	Chunk::_genLayers()
{
	// for (int y = 0; y < Chunk::CHUNKSIZE; ++y)
	// {
	// 	float By = y / Chunk::BLOCKSIZE;
	// 	for (int x = 0; x < Chunk::CHUNKSIZE; ++x)
	// 	{
	// 		float Bx = x / Chunk::BLOCKSIZE;
	// 		for (int yo = 0; yo < 1 / Chunk::BLOCKSIZE; ++yo)
	// 		{
	// 			float ByyoCB = (By + yo) * (Chunk::CHUNKSIZE / Chunk::BLOCKSIZE);
	// 			for (int xo = 0; xo < 1 / Chunk::BLOCKSIZE; ++xo)
	// 			{
	// 				float	height = Increment((calcNoise({y + yo * Chunk::BLOCKSIZE + _pos.y, x + xo * Chunk::BLOCKSIZE + _pos.x}, 0.005, 1, 6) + 1) / 2 * 200 * 100, Chunk::BLOCKSIZE * 100) / 100;

	// 				_RawLayers[height].blocks[ByyoCB + (Bx + xo)] = 1;
	// 			}
	// 		}
	// 	}
	// }

	for (int y = 0; y < Chunk::CHUNKSIZE; ++y)
	{
		for (int x = 0; x < Chunk::CHUNKSIZE; ++x)
		{
			// PRERR Chunk::CHUNKSIZE * Chunk::CHUNKSIZE / (Chunk::BLOCKSIZE * Chunk::BLOCKSIZE) AND "; " AND y * Chunk::CHUNKSIZE + x AND "; " AND Chunk::CHUNKSIZE ENDL;
			float	height = Increment((calcNoise({y * Chunk::BLOCKSIZE + _pos.y, x * Chunk::BLOCKSIZE + _pos.x}, 0.005, 1, 6) + 1) / 2 * 200 * 100, Chunk::BLOCKSIZE * 100) / 100;
			_RawChunk[y * Chunk::CHUNKSIZE + x] = height;
			// _RawLayers[height].blocks[y * Chunk::CHUNKSIZE + x] = 1;
		}
	}
}

void	Chunk::_addVertex(const glm::dvec3 &pos, const uint64_t &normID)
{
	glm::dvec3 realPos = pos;

	// PRINT "[" AND pos.x AND "; " AND realPos.x AND "];	[" AND pos.y AND "; " AND realPos.y AND "];	[" AND pos.z AND ";" AND realPos.z AND "]" ENDL;

	_vertices.push_back(
		normID << CN_OFFSET
		| (uint64_t)(realPos.x * 100) << CX_OFFSET
		| (uint64_t)(realPos.y * 100) << CY_OFFSET
		| (uint64_t)(realPos.z * 100)
	);
}

//      1_______2
//     /:      /│
//    4_:_____3 │                N
//    │ 5_ _ _│_6        top:  W U E
//    │.      │/                 S
//    8_______7

// normals:
// 	vec3 (0, 1, 0)	TOP
// 	vec3 (0, -1, 0)	BOT
// 	vec3 (-1, 0, 0)	WEST
// 	vec3 (1, 0, 0)	EAST
// 	vec3 (0, 0, 1)	NORTH
// 	vec3 (0, 0, -1)	SOUTH



void	Chunk::_genVertices()
{

	// offsets for the cube's edges: NO MORE MAGIC VECTORS
	glm::dvec3 V1 = glm::dvec3(0, _usedBlocksize, _usedBlocksize);
	glm::dvec3 V2 = glm::dvec3(_usedBlocksize, _usedBlocksize, _usedBlocksize);
	glm::dvec3 V3 = glm::dvec3(_usedBlocksize, _usedBlocksize, 0);
	glm::dvec3 V4 = glm::dvec3(0, _usedBlocksize, 0);
	glm::dvec3 V5 = glm::dvec3(0, 0, _usedBlocksize);
	glm::dvec3 V6 = glm::dvec3(_usedBlocksize, 0, _usedBlocksize);
	glm::dvec3 V7 = glm::dvec3(_usedBlocksize, 0, 0);
	glm::dvec3 V8 = glm::dvec3(0, 0, 0);

	_vertices.clear();
	_vertices.shrink_to_fit();
	_nbVertices = 0;

	float	min = _RawLayers.begin()->first;

	float	x = 0;
	float	counter = 0;
	float	z = 0;

	for (int i = 0; i < Chunk::CHUNKSIZE * Chunk::CHUNKSIZE / _LOD; i += _LOD)
	{
		glm::dvec3 pos = glm::dvec3(
			x,
			_RawChunk[i] - (_LOD * Chunk::BLOCKSIZE),
			z
		);


		// top face
		_addVertex(pos + V1, TOP);
		_addVertex(pos + V2, TOP);
		_addVertex(pos + V3, TOP);

		_addVertex(pos + V1, TOP);
		_addVertex(pos + V3, TOP);
		_addVertex(pos + V4, TOP);


		// side faces
		_addVertex(pos + V1, WEST);
		_addVertex(pos + V4, WEST);
		_addVertex(pos + V8, WEST);
	
		_addVertex(pos + V1, WEST);
		_addVertex(pos + V8, WEST);
		_addVertex(pos + V5, WEST);


		_addVertex(pos + V2, NORTH);
		_addVertex(pos + V1, NORTH);
		_addVertex(pos + V5, NORTH);
	
		_addVertex(pos + V2, NORTH);
		_addVertex(pos + V5, NORTH);
		_addVertex(pos + V6, NORTH);


		_addVertex(pos + V3, EAST);
		_addVertex(pos + V2, EAST);
		_addVertex(pos + V6, EAST);
	
		_addVertex(pos + V3, EAST);
		_addVertex(pos + V6, EAST);
		_addVertex(pos + V7, EAST);


		_addVertex(pos + V4, SOUTH);
		_addVertex(pos + V3, SOUTH);
		_addVertex(pos + V7, SOUTH);
	
		_addVertex(pos + V4, SOUTH);
		_addVertex(pos + V7, SOUTH);
		_addVertex(pos + V8, SOUTH);


		// bot
		_addVertex(pos + V5, BOT);
		_addVertex(pos + V6, BOT);
		_addVertex(pos + V7, BOT);
		
		_addVertex(pos + V5, BOT);
		_addVertex(pos + V7, BOT);
		_addVertex(pos + V8, BOT);


		x += _usedBlocksize;
		counter += _LOD;
		if (counter >= Chunk::CHUNKSIZE)
		{
			x = 0;
			counter = 0;
			z += _usedBlocksize;
		}
	}

	_nbVertices = _vertices.size();

	_RawLayers.clear();
}





/*
for (auto layer : _RawLayers)
	{
		float	x = 0;
		float	y = 0;
		float	z = 0;
		int		counter = 0;
		uint8_t	*blocks = layer.second.blocks.data();
		// for (uint64_t i = 0; i < Chunk::CHUNKSIZE * Chunk::CHUNKSIZE / (Chunk::BLOCKSIZE * Chunk::BLOCKSIZE); ++i)
		for (uint64_t i = 0; i < Chunk::CHUNKSIZE * Chunk::CHUNKSIZE; i += _LOD)
		{
			if (blocks[i])
			{
				glm::dvec3 pos = glm::dvec3(
					x,
					layer.first,
					z
				);

				// top face
				_addVertex(pos + V1, TOP);
				_addVertex(pos + V2, TOP);
				_addVertex(pos + V3, TOP);

				_addVertex(pos + V1, TOP);
				_addVertex(pos + V3, TOP);
				_addVertex(pos + V4, TOP);


				// side faces
				_addVertex(pos + V1, WEST);
				_addVertex(pos + V4, WEST);
				_addVertex(pos + V8, WEST);
			
				_addVertex(pos + V1, WEST);
				_addVertex(pos + V8, WEST);
				_addVertex(pos + V5, WEST);


				_addVertex(pos + V2, NORTH);
				_addVertex(pos + V1, NORTH);
				_addVertex(pos + V5, NORTH);
			
				_addVertex(pos + V2, NORTH);
				_addVertex(pos + V5, NORTH);
				_addVertex(pos + V6, NORTH);


				_addVertex(pos + V3, EAST);
				_addVertex(pos + V2, EAST);
				_addVertex(pos + V6, EAST);
			
				_addVertex(pos + V3, EAST);
				_addVertex(pos + V6, EAST);
				_addVertex(pos + V7, EAST);


				_addVertex(pos + V4, SOUTH);
				_addVertex(pos + V3, SOUTH);
				_addVertex(pos + V7, SOUTH);
			
				_addVertex(pos + V4, SOUTH);
				_addVertex(pos + V7, SOUTH);
				_addVertex(pos + V8, SOUTH);


				// bot
				_addVertex(pos + V5, BOT);
				_addVertex(pos + V6, BOT);
				_addVertex(pos + V7, BOT);
				
				_addVertex(pos + V5, BOT);
				_addVertex(pos + V7, BOT);
				_addVertex(pos + V8, BOT);

			}
			x += _usedBlocksize;
			counter += _LOD;
			if (counter == Chunk::CHUNKSIZE)
			{
				x = 0;
				counter = 0;
				z += _usedBlocksize;
			}
		}
	}*/