/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:11:24 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/07 20:38:21 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Render/Objects/Model.hpp>

glm::vec3	Model::normals[900] = {{0, 0, 0}};
float		Model::normalsLength[900] = {0};


#include <fstream>

std::ofstream	ofs("test.txt");

Model::Model(const std::string &path)
{
	uploaded = false;
	_pos = glm::dvec3{0, 0, 0};
	_orientation = glm::dquat({0.f, 0.f, 0.f});
	_scale = glm::dvec3{1, 1, 1};
	redoMatrix();
	if (path.find_last_of(".obj") != path.length() - 1)
		throw(std::runtime_error(RED BOLD UNDL "Format supported is .obj"));
	readFile(path);
}

void	Model::draw()
{
	if (!uploaded)
		upload();

	ShaderManager::setMat4("model", _matrix);

	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, nbVertices);
	glBindVertexArray(0);
}

void	Model::unload()
{
	uploaded = false;
	if (_VBO)
		glDeleteBuffers(1, &_VBO);
	_VBO = 0;
	if (_VAO)
		glDeleteVertexArrays(1, &_VAO);
	_VAO = 0;
}

void	Model::upload()
{
	if (_VAO <= 0)
		glGenVertexArrays(1, &_VAO);
	if (_VBO <= 0)
    	glGenBuffers(1, &_VBO);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(uint64_t), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribLPointer(0, 1, GL_DOUBLE, sizeof(uint64_t) * 2, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribLPointer(1, 1, GL_DOUBLE, sizeof(uint64_t) * 2, (void*)(1 * sizeof(uint64_t)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);	

	uploaded = true;
}

void	Model::remove()
{
	if (_VBO)
		glDeleteBuffers(1, &_VBO);
	_VBO = 0;
	if (_VAO)
		glDeleteVertexArrays(1, &_VAO);
	_VAO = 0;

	vertices.clear();
	vertices.shrink_to_fit();
	nbVertices = 0;
}

void	Model::translate(const glm::dvec3 &amount)
{
	_pos += amount;
	redoMatrix();
}

void	Model::setPos(const glm::dvec3 &newValue)
{
	_pos = newValue;
	redoMatrix();
}

void	Model::rotate(const glm::dvec3 &amount)
{
	glm::dquat	newOrient{1, amount.x / 2., amount.y / 2., amount.z / 2.};

	_orientation = glm::normalize(newOrient * _orientation);
	redoMatrix();
}

void	Model::setOrientation(const glm::dvec3 &newValue)
{
	_orientation = glm::normalize(glm::dquat{1, newValue.x / 2., newValue.y / 2., newValue.z / 2.});
	redoMatrix();
}


void	Model::setOrientation(const glm::dquat &newValue)
{
	_orientation = glm::normalize(newValue);
	redoMatrix();
}

void	Model::scale(const glm::dvec3 &amount)
{
	_scale = _scale + amount;
	redoMatrix();
}

void	Model::setScale(const glm::dvec3 &newValue)
{
	_scale = newValue;
	redoMatrix();
}

void	Model::redoMatrix()
{
	_matrix = glm::dmat4(1);

	_matrix = glm::translate(_matrix, _pos);
	_matrix *= glm::mat4_cast(_orientation);
	_matrix = glm::scale(_matrix, _scale);
}

static int	getCosineSimilarity(const glm::vec3 &values)
{
	int		bestIndex = 0;
	float	bestMatch = -1;
	float	cosineSimilarity = 0;

	for (int i = 0; i < 900; ++i)
	{
		cosineSimilarity = glm::dot(values, Model::normals[i]) / (glm::length2(values) * Model::normalsLength[i]);
		if (cosineSimilarity > bestMatch)
		{
			bestMatch = cosineSimilarity;
			bestIndex = i;
		}
		if (bestMatch == 1)
			return (bestIndex);
	}
	return (bestIndex);
}

void	Model::addVertexInfo(std::stringstream &sline, const char &kind)
{
	glm::vec3	values;
	char		sep;

	switch (kind)
	{
		case ' ':
			sline >> values.x >> values.y >> values.z;
			_rawVertices.push_back(values);
			break;
		case 't':
			sline >> sep;
			sline >> values.x >> values.y;
			// ofs AND sline.str() AND ": " AND values.x AND ", " AND values.y ENDL;
			_rawTextures.push_back(glm::vec2{values.x, values.y});
			break;
		case 'n':
			sline >> sep;
			sline >> values.x >> values.y >> values.z;
			_rawNormals.push_back(getCosineSimilarity(values));
			break;
	}
}

void printvec3(const glm::vec3 &vec)
{
	ofs << vec.x AND ", " AND vec.y AND ", " AND vec.z;
}

#include <bitset>
void	Model::addVertex(uint vertexIndex, int textureID = 0, glm::vec2 texture = glm::vec2{0}, int normal = 0)
{
	(void)texture;
	
	vertices.push_back((((uint64_t)(((_rawVertices[vertexIndex].x < 0) << (POS_SIZE)) | (((uint64_t)glm::abs(_rawVertices[vertexIndex].x * 100000)) & POS_MASK)) << X_OFFSET) & (X_MASK))
					 | (((uint64_t)(((_rawVertices[vertexIndex].y < 0) << (POS_SIZE)) | (((uint64_t)glm::abs(_rawVertices[vertexIndex].y * 100000)) & POS_MASK)) << Y_OFFSET) & (Y_MASK))
					 | (((uint64_t)(((_rawVertices[vertexIndex].z < 0) << (POS_SIZE)) | (((uint64_t)glm::abs(_rawVertices[vertexIndex].z * 100000)) & POS_MASK))) & (Z_MASK)));

	vertices.push_back((((uint64_t)normal << N_OFFSET) & N_MASK)
					 | (((uint64_t)textureID << T_OFFSET) & T_MASK)
					 | (((uint64_t)(((texture.x < 0) << (TPOS_SIZE)) | (((uint64_t)glm::abs(texture.x * 1000000.0f)) & TPOS_MASK)) << TX_OFFSET) & (TX_MASK))
					 | (((uint64_t)(((texture.y < 0) << (TPOS_SIZE)) | (((uint64_t)glm::abs(texture.y * 1000000.0f)) & TPOS_MASK))) & (TY_MASK)));

	// std::bitset<24> x((((((uint64_t)glm::abs(texture.x * 1000000.0f)) & TPOS_MASK))) & (TX_MASK));
	// std::bitset<24> y((((((uint64_t)glm::abs(texture.y * 1000000.0f)) & TPOS_MASK))) & (TY_MASK));
	// uint64_t xy = (((((((uint64_t)glm::abs(texture.x * 1000000.0f)) & TPOS_MASK)) << TX_OFFSET) & (TX_MASK)) | ((((((uint64_t)glm::abs(texture.y * 1000000.0f)) & TPOS_MASK))) & (TY_MASK)));

	// ofs AND x AND "; " AND y AND ": " AND xy ENDL;

	// float tx = float((xy >> TX_OFFSET) & TPOS_MASK) / 1000000.0;
	// float ty = float(xy & TPOS_MASK) / 1000000.0;;

	// ofs AND "	" AND texture.x AND "; " AND texture.y AND "| " AND tx AND "; " AND ty ENDL;

}

void	Model::computeUvs(int indexes[4][3], glm::vec2 text[4], int nbElem)
{
	glm::vec3	normals[3];

	for (int i = 0; i < 3; ++i)
		normals[i] = glm::abs(Model::normals[indexes[i][2]]);

	for (int i = 0; i < 3; ++i)
	{
		if (normals[i].x > normals[i].y && normals[i].x > normals[i].z)
		{
			text[i].x = _rawVertices[indexes[i][0]].z;
			text[i].y = _rawVertices[indexes[i][0]].y;
		}
		else if (normals[i].y > normals[i].z)
		{
			text[i].x = _rawVertices[indexes[i][0]].x;
			text[i].y = _rawVertices[indexes[i][0]].z;
		}
		else
		{
			text[i].x = _rawVertices[indexes[i][0]].x;
			text[i].y = _rawVertices[indexes[i][0]].y;
		}
	}
}

void	Model::addFace(std::stringstream &sline)
{
	std::string	bloc;
	uint		index;
	int			indexes[4][3] = {{-1}};
	glm::vec2 	text[4] = {glm::vec2{0}};
	int			i = 0;

	while (sline >> bloc)
	{
		std::istringstream	info(bloc);
		std::string			infos[3];

		std::getline(info, infos[0], '/');
		std::getline(info, infos[1], '/');
		std::getline(info, infos[2], ' ');

		if (infos[0].empty())
			throw(std::runtime_error(RED BOLD UNDL "Object is Invalid" CLR));
		indexes[i][0] = atoi(infos[0].c_str()) - 1;

		if (!infos[1].empty())
			indexes[i][1] = atoi(infos[1].c_str()) - 1;

		if (!infos[2].empty())
			indexes[i][2] = atoi(infos[2].c_str()) - 1;

		i ++;
	}

	if (indexes[0][2] == -1 || indexes[1][2] == -1 || indexes[2][2] == -1 || (i == 4 && indexes[3][2] == -1))
	{
		indexes[0][2] = indexes[1][2] = indexes[2][2] = getCosineSimilarity(glm::normalize(glm::cross(_rawVertices[indexes[1][0]] - _rawVertices[indexes[0][0]], _rawVertices[indexes[2][0]] - _rawVertices[indexes[0][0]])));
		if (i == 4)
			indexes[3][2] = indexes[0][2];
	}

	if (indexes[0][1] == -1 || indexes[1][1] == -1 || indexes[2][1] == -1 || (i == 4 && indexes[3][1] == -1))
		computeUvs(indexes, text, i);
	else
	{
		text[0] = _rawTextures[indexes[0][1]];
		text[1] = _rawTextures[indexes[1][1]];
		text[2] = _rawTextures[indexes[2][1]];
		if (i == 4)
			text[3] = _rawTextures[indexes[3][1]];
		// ofs AND sline.str() AND "; " AND "(" AND indexes[0][1] AND "; " AND text[0].x AND ":" AND text[0].y AND "), " AND "(" AND indexes[1][1] AND "; "  AND text[1].x AND ":" AND text[1].y AND "), "
		// 		 AND "(" AND indexes[2][1] AND "; "  AND text[2].x AND ":" AND text[2].y AND ")" ENDL;
	}

	addVertex(indexes[0][0], _currentTexture, text[0], indexes[0][2]);
	addVertex(indexes[1][0], _currentTexture, text[1], indexes[1][2]);
	addVertex(indexes[2][0], _currentTexture, text[2], indexes[2][2]);

	if (i == 4)
	{
		addVertex(indexes[0][0], _currentTexture, text[0], indexes[0][2]);
		addVertex(indexes[2][0], _currentTexture, text[2], indexes[2][2]);
		addVertex(indexes[3][0], _currentTexture, text[3], indexes[3][2]);
	}
}

std::string	genPath(const std::string &name, const std::string &path)
{
	std::string	newPath;
	if (path.find_last_of('/') != std::string::npos)
		newPath = path.substr(0, path.find_last_of('/') + 1);
	newPath.append(name.substr(name[0] == ' '));
	newPath.erase(std::find_if(newPath.rbegin(), newPath.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), newPath.end());
	return (newPath);
}

void	Model::loadMtl(std::stringstream &sline, const std::string &path)
{
	std::string		words;
	std::ifstream	mtlFile;
	std::string		line;
	std::string		currentMtl = "";

	sline >> words;
	std::getline(sline, words);
	
	// PRINT "hey" CENDL;

	// PRINT words AND ", " AND words.empty() CENDL;
	if (words.empty())
		throw(std::runtime_error(RED BOLD UNDL "Object's MtlFile is invalid." CLR));
	mtlFile.open(genPath(words, path));
	if (mtlFile.fail())
		throw(std::runtime_error(RED BOLD UNDL "Object's MtlFile could not be opened." CLR));

	while(std::getline(mtlFile, line))
	{
		std::stringstream	mtlLine(line);

		mtlLine >> words;
		if (words == "newmtl")
		{
			std::getline(mtlLine, words);
			currentMtl = words;
			_textures.insert({words, -1});
		}
		else if (words == "map_Kd")
		{
			if (currentMtl.empty())
				throw(std::runtime_error(RED BOLD UNDL "MtlFile is invalid." CLR));
			std::getline(mtlLine, words);
			_usedTextures.insert(words);
			_textures[currentMtl] = TextureManager::loadImage(words, genPath(words, path).c_str());
		}
	}
}

void	Model::readFile(const std::string &path)
{
	std::ifstream		file(path);
	std::string			line;

	int	i= 0;

	if (file.fail())
		throw(std::runtime_error(RED BOLD UNDL "Obj File failed to open" CLR));
	while (getline(file, line))
	{
		std::stringstream	sline(line);
		std::string			texture;
		char				p = 0;

		i++;
		sline >> p;
		switch (p)
		{
			case 'v':
				addVertexInfo(sline, line[1]);
				break;
			case 'f':
				addFace(sline);
				break;
			case 'm':
				// PRINT sline.str() AND "; " AND i CENDL;
				loadMtl(sline, path);
				break;
			case 'u':
				sline >> texture;
				std::getline(sline, texture);
				_currentTexture = _textures[texture];
				break;
			default:
				break;
		}
	}

	nbVertices = vertices.size();
	_rawVertices.clear();
	_rawTextures.clear();
	_rawNormals.clear();
	_rawVertices.shrink_to_fit();
	_rawTextures.shrink_to_fit();
	_rawNormals.shrink_to_fit();
}
