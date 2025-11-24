/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:55:29 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/24 19:06:33 by mbirou           ###   ########.fr       */
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

	return ((res + 1) / 2 * 200);
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
	{
		upload();
		return ;
	}

	ShaderManager::setMat4("model", _matrice);

	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, _nbVertices);
	// glBindVertexArray(0);
}

void	Chunk::unload()
{
	if (!_generated)
		return ;

	_uploaded = false;
	if (_VBO)
		glDeleteBuffers(1, &_VBO);
	_VBO = 0;
	if (_EBO)
		glDeleteVertexArrays(1, &_EBO);
	_EBO = 0;
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
	if (_EBO)
		glDeleteVertexArrays(1, &_EBO);
	_EBO = 0;
	if (_VAO)
		glDeleteVertexArrays(1, &_VAO);
	_VAO = 0;

	// _RawChunk.clear();
	_strips.clear();
	_strips.shrink_to_fit();
	_vertices.clear();
	_vertices.shrink_to_fit();
	_nbVertices = 0;
}

void	Chunk::generate(const glm::vec2 &pos, const float &blocksize, const float &chunksize, const float &targetSize)
{
	if (_generated)
		return;

	Chunk::BLOCKSIZE = blocksize;
	Chunk::CHUNKSIZE = chunksize / blocksize;

	_usedBlocksize = targetSize;
	_LOD = _usedBlocksize / Chunk::BLOCKSIZE;

	_pos = pos;
	_matrice = glm::translate(glm::mat4(1.f), {pos.x, 0, pos.y});

	// _RawChunk.resize(Chunk::CHUNKSIZE * Chunk::CHUNKSIZE, 0);
	_strips.resize(Chunk::CHUNKSIZE * Chunk::CHUNKSIZE);

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
	for (int y = 0; y < Chunk::CHUNKSIZE; ++y)
	{
		for (int x = 0; x < Chunk::CHUNKSIZE; ++x)
		{
			// ========================== For 2D Noise
			float	height = Increment(calcNoise({x * Chunk::BLOCKSIZE + _pos.x, y * Chunk::BLOCKSIZE + _pos.y}, 0.005, 1, 6) * 100, Chunk::BLOCKSIZE * 100) / 100;
			// _RawChunk[y * Chunk::CHUNKSIZE + x] = height; // Old one
			_strips[y * Chunk::CHUNKSIZE + x].push_back({height, height, 0});

		
			// ========================== For 3D Noise
			// int slicePos = y * Chunk::CHUNKSIZE + x;
			// int	currentType = -1;
			// for (int z = 254; z >= 0; --z)
			// {
			// 	int	type = getBlockType(glm::vec3({x * Chunk::BLOCKSIZE + _pos.x, y * Chunk::BLOCKSIZE + _pos.y, z * Chunk::BLOCKSIZE})); // the noise function
			// 	if (type != currentType)
			// 	{
			// 		currentType = type;
			// 		_strips[slicePos].insert(_strips[slicePos].begin(), Strip{z * Chunk::BLOCKSIZE, Chunk::BLOCKSIZE, type});
			// 	}
			// 	else
			// 		_strips[slicePos][0].size += Chunk::BLOCKSIZE;
			// }
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


float	calFaceSize(const Strip &strip, const std::vector<Strip> &oppositeStrip)
{
	int		i = 0;
	int		ii = 0;
	int		lastSize = 0;

	while (i < oppositeStrip.size() && oppositeStrip[i].height < strip.height)
		i ++;
	
	if (oppositeStrip[i].height - oppositeStrip[i].size > strip.height)
		i --;
	if (i == 0)
		return (0);

	if (oppositeStrip[i].height < strip.height - strip.size)
		return (strip.size);

	while (ii < strip.size)
	{
		if (strip.height - ii <= oppositeStrip[i].height)
		{
			while (ii < strip.size && strip.height - ii <= oppositeStrip[i].height)
		}
		ii ++;
	}
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


// ============ old ones, extruded upward
// offsets for the cube's edges: NO MORE MAGIC VECTORS
// glm::dvec3 V1 = glm::dvec3(0, _usedBlocksize, _usedBlocksize);
// glm::dvec3 V2 = glm::dvec3(_usedBlocksize, _usedBlocksize, _usedBlocksize);
// glm::dvec3 V3 = glm::dvec3(_usedBlocksize, _usedBlocksize, 0);
// glm::dvec3 V4 = glm::dvec3(0, _usedBlocksize, 0);
// glm::dvec3 V5 = glm::dvec3(0, 0, _usedBlocksize);
// glm::dvec3 V6 = glm::dvec3(_usedBlocksize, 0, _usedBlocksize);
// glm::dvec3 V7 = glm::dvec3(_usedBlocksize, 0, 0);
// glm::dvec3 V8 = glm::dvec3(0, 0, 0);

void	Chunk::_genVertices()
{
	glm::dvec3 V1 = glm::dvec3(0, 0, _usedBlocksize);
	glm::dvec3 V2 = glm::dvec3(_usedBlocksize, 0, _usedBlocksize);
	glm::dvec3 V3 = glm::dvec3(_usedBlocksize, 0, 0);
	glm::dvec3 V4 = glm::dvec3(0, 0, 0);
	glm::dvec3 V5 = glm::dvec3(0, -_usedBlocksize, _usedBlocksize);
	glm::dvec3 V6 = glm::dvec3(_usedBlocksize, -_usedBlocksize, _usedBlocksize);
	glm::dvec3 V7 = glm::dvec3(_usedBlocksize, -_usedBlocksize, 0);
	glm::dvec3 V8 = glm::dvec3(0, -_usedBlocksize, 0);

	_vertices.clear();
	_vertices.shrink_to_fit();
	_nbVertices = 0;

	glm::vec3	faceMod = {0, 0, 0};

	for (float y = 0; y < Chunk::CHUNKSIZE / _LOD; y += 1)
	{
		for (float x = 0; x < Chunk::CHUNKSIZE / _LOD; x += 1)
		{
			for (Strip &strip : _strips[y * _LOD * Chunk::CHUNKSIZE + x * _LOD])
			{
				glm::dvec3 pos = glm::dvec3(
					x * _usedBlocksize,
					strip.height * _usedBlocksize,
					y * _usedBlocksize
				);

				// top face
				_addVertex(pos + V1, TOP);
				_addVertex(pos + V2, TOP);
				_addVertex(pos + V3, TOP);

				_addVertex(pos + V1, TOP);
				_addVertex(pos + V3, TOP);
				_addVertex(pos + V4, TOP);




				// =========== side faces ===========

				if (x == 0)
					faceMod.y = 0;
				else
					faceMod.y = calFaceSize(strip, _strips[y * _LOD * Chunk::CHUNKSIZE + (x - 1) * _LOD]) * _usedBlocksize;

				_addVertex(pos + V1, WEST);
				_addVertex(pos + V4, WEST);
				_addVertex(pos + V8, WEST);
			
				_addVertex(pos + V1, WEST);
				_addVertex(pos + V8, WEST);
				_addVertex(pos + V5, WEST);




				if (y == 0)
					faceMod.y = 0;
				else
					faceMod.y = calFaceSize(strip, _strips[(y - 1) * _LOD * Chunk::CHUNKSIZE + x * _LOD]) * _usedBlocksize;

				_addVertex(pos + V2, NORTH);
				_addVertex(pos + V1, NORTH);
				_addVertex(pos + V5, NORTH);
			
				_addVertex(pos + V2, NORTH);
				_addVertex(pos + V5, NORTH);
				_addVertex(pos + V6, NORTH);




				if (x + 1 >= Chunk::CHUNKSIZE / _LOD)
					faceMod.y = 0;
				else
					faceMod.y = calFaceSize(strip, _strips[y * _LOD * Chunk::CHUNKSIZE + (x + 1) * _LOD]) * _usedBlocksize;

				_addVertex(pos + V3, EAST);
				_addVertex(pos + V2, EAST);
				_addVertex(pos + V6, EAST);
			
				_addVertex(pos + V3, EAST);
				_addVertex(pos + V6, EAST);
				_addVertex(pos + V7, EAST);




				if (y + 1 >= Chunk::CHUNKSIZE / _LOD)
					faceMod.y = 0;
				else
					faceMod.y = calFaceSize(strip, _strips[(y + 1) * _LOD * Chunk::CHUNKSIZE + x * _LOD]) * _usedBlocksize;

				_addVertex(pos + V4, SOUTH);
				_addVertex(pos + V3, SOUTH);
				_addVertex(pos + V7, SOUTH);
			
				_addVertex(pos + V4, SOUTH);
				_addVertex(pos + V7, SOUTH);
				_addVertex(pos + V8, SOUTH);




			}

			
		}
	}

	_nbVertices = _vertices.size();
}



/*
============================ Old one, was not using the strips


for (float y = 0; y < Chunk::CHUNKSIZE / _LOD; y += 1)
	{
		for (float x = 0; x < Chunk::CHUNKSIZE / _LOD; x += 1)
		{
			glm::dvec3 pos = glm::dvec3(
				x * _usedBlocksize,
				glm::floor(_RawChunk[y * _LOD * Chunk::CHUNKSIZE + x * _LOD] / _usedBlocksize) * _usedBlocksize,
				y * _usedBlocksize
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


			// // bot
			// _addVertex(pos + V5, BOT);
			// _addVertex(pos + V6, BOT);
			// _addVertex(pos + V7, BOT);
			
			// _addVertex(pos + V5, BOT);
			// _addVertex(pos + V7, BOT);
			// _addVertex(pos + V8, BOT);
		}
	}


*/