/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:06:19 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/07 17:42:18 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_HPP
# define MODEL_HPP

# include <Engine/Render/ShaderManager.hpp>
# include <Engine/Render/TextureManager.hpp>
# include <spellBook.hpp>

# include <iostream>
# include <vector>
# include <map>
# include <set>
# include <fstream>
# include <sstream>
# include <algorithm>

# include <glad/glad.h>
# include <glfw/glfw3.h>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

# define GLM_ENABLE_EXPERIMENTAL TRUE
# include <glm/gtx/euler_angles.hpp>
# include <glm/gtx/norm.hpp>


// ---- These Masks are also used for the normals.
# define X_MASK 0b0111111111111111111111000000000000000000000000000000000000000000 // ┳> value is multiplied by 1~~~~
# define Y_MASK 0b0000000000000000000000111111111111111111111000000000000000000000 // ┣> giving a range of [-~;~]
# define Z_MASK 0b0000000000000000000000000000000000000000000111111111111111111111 // ┗> with 0.~~~~ precision
# define POS_MASK 0b0000000000000000000000000000000000000000000011111111111111111111
// 		┗> For the normals the values go from -1 to 1 with 0.000001 precision

# define N_MASK 0b1111111111000000000000000000000000000000000000000000000000000000 // -> normal index in the big table of the 900 different pre-baked values (allows 12d turns)
# define T_MASK 0b0000000000111111000000000000000000000000000000000000000000000000 // -> 32 textures in the atlas (can be increased)
# define TX_MASK 0b0000000000000000111111111111111111111111000000000000000000000000 // ┳> value multiplied by 100000000
# define TY_MASK 0b0000000000000000000000000000000000000000111111111111111111111111 // ┗> with max [-15;15] and 0.00000001 precision
# define TPOS_MASK 0b0000000000000000000000000000000000000000011111111111111111111111 // ┗> with max [-15;15] and 0.00000001 precision

# define X_OFFSET 42 // -> the offsets for the masks above
# define Y_OFFSET 21 // -> the offsets for the masks above
# define POS_SIZE 20 // -> the offsets for the masks above
# define TPOS_SIZE 23 // -> the offsets for the masks above

# define N_OFFSET 54 // -> the offsets for the masks above
# define T_OFFSET 48 // -> the offsets for the masks above
# define TX_OFFSET 24 // -> the offsets for the masks above


struct	Model
{
	Model(){;}
	Model(const std::string &path);

	void	draw();
	void	unload();
	void	upload();
	void	remove();

	void	translate(const glm::dvec3 &amount);
	void	setPos(const glm::dvec3 &newValue);
	void	rotate(const glm::dvec3 &amount);
	void	setOrientation(const glm::dvec3 &newValue);
	void	setOrientation(const glm::dquat &newValue);
	void	scale(const glm::dvec3 &amount);
	void	setScale(const glm::dvec3 &newValue);

	glm::dvec3	getPos() const {return (_pos);}

	void	requestTextures() {TextureManager::requestTextures(_usedTextures);}
	void	removeRequests() {TextureManager::deleteTextures(_usedTextures);}

	bool					uploaded;
	std::vector<uint64_t>	vertices;
	uint					nbVertices;

	static glm::vec3	normals[900];
	static float		normalsLength[900];
	static void			sendNormals() {ShaderManager::setVec3Array("normals", normals, 900);};

	private:
		void	redoMatrix();
		void	addVertexInfo(std::stringstream &sline, const char &kind);
		void	addVertex(uint vertexIndex, int textureID, glm::vec2 texture, int normal);
		void	computeUvs(int indexes[4][3], glm::vec2 text[4], int nbElem);
		void	addFace(std::stringstream &line);
		void	loadMtl(std::stringstream &sline, const std::string &path);
		void	readFile(const std::string &path);

		std::vector<glm::vec3>	_rawVertices;
		std::vector<uint>		_rawNormals;
		std::vector<glm::vec2>	_rawTextures;
	
		std::map<std::string, int>	_textures;
		int							_currentTexture;

		std::set<std::string>	_usedTextures;

		GLuint	_VAO = 0, _VBO = 0;

		glm::dmat4	_matrix;
		glm::dquat	_orientation;
		glm::dvec3	_pos;
		glm::dvec3	_scale;
};


constexpr void		computeNormals()
{
	int			i = 0;
	glm::vec3	normal = glm::vec3{0, 0, 0};
	bool		addNum = true;

	for (float a = 0; a < 360; a += 12)
	{
		for (float b = 0; b < 360; b += 12)
		{
			normal.x = cos(glm::radians(a)) * cos(glm::radians(b));
			normal.y = sin(glm::radians(b));
			normal.z = sin(glm::radians(a)) * cos(glm::radians(b));

			for (int ii = 0; ii < i; ii += 3)
			{
				if (normal == Model::normals[ii])
				{
					addNum = false;
					break;
				}
			}
			if (addNum)
			{
				Model::normals[i] = normal;
				Model::normalsLength[i] = glm::length2(normal);
				i ++;
			}
			addNum = true;
		}
	}
}

#endif