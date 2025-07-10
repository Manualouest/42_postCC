/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectLoader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 17:15:20 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ObjectHandler/ObjectLoader.hpp>

std::map<std::string, std::vector<float> >	ObjectLoader::_vertexInfo;
ObjectLoader::info							ObjectLoader::_info = {0, 0, 0};
std::vector<std::string>					ObjectLoader::_infoTypes = {"v ", "vt", "vn", "f "};
int											ObjectLoader::_nbFaces = 0;

Object	ObjectLoader::createObject()
{
	_vertexInfo["f "].shrink_to_fit();
	int i = 0;

	VAO	_VAO = VAO(1);
	_VAO.Bind();
	VBO	_VBO = VBO(_vertexInfo["f "].data(), _vertexInfo["f "].size() * sizeof(float));

	_VAO.linkAttrib(_VBO, 0, 3, GL_FLOAT, LINELEN * sizeof(float), (void*)0);
	_VAO.linkAttrib(_VBO, 1, 2, GL_FLOAT, LINELEN * sizeof(float), (void*)(3 * sizeof(float)));
	_VAO.linkAttrib(_VBO, 2, 3, GL_FLOAT, LINELEN * sizeof(float), (void*)(5 * sizeof(float)));
	_VAO.Unbind();
	_VBO.Unbind();
	GLuint vaoID = _VAO.ID;
	GLuint vboID = _VBO.ID;
	_VAO.ID = 0;
	_VBO.ID = 0;
	return (Object(vaoID, vboID, _vertexInfo["f "], _nbFaces));
}

void	makeNormals(std::vector<float> &values, bool isquad)
{
	int		offset = isquad * (LINELEN * 3);
	float	a[3];
	float	b[3];
	float	c[3];

	a[0] = values[offset + LINELEN] - values[offset + 0];
	a[1] = values[offset + LINELEN + 1] - values[offset + 1];
	a[2] = values[offset + LINELEN + 2] - values[offset + 2];
	b[0] = values[offset + LINELEN * 2] - values[offset + 0];
	b[1] = values[offset + LINELEN * 2 + 1] - values[offset + 1];
	b[2] = values[offset + LINELEN * 2 + 2] - values[offset + 2];
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];

	float length = std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
	if (length > 0)
	{
		c[0] /= length;
		c[1] /= length;
		c[2] /= length;
	}
	else
	{
		c[0] = 0;
		c[1] = 0;
		c[2] = 0;
	}

	for (int i = 0; i < 3; ++i)
	{
		values[offset + i * LINELEN + 5] = c[0];
		values[offset + i * LINELEN + 6] = c[1];
		values[offset + i * LINELEN + 7] = c[2];
	}
}

void	makeUV(std::vector<float> &values, bool isquad)
{
	int	offset = isquad * (LINELEN * 3);
	for (int i = 0; i < 3; ++i)
	{
		if (std::abs(values[offset + i * LINELEN + 5]) > std::abs(values[offset + i * LINELEN + 6])
			&& std::abs(values[offset + i * LINELEN + 5]) > std::abs(values[offset + i * LINELEN + 7]))
		{
			values[offset + i * LINELEN + 3] = values[offset + i * LINELEN + 2];
			values[offset + i * LINELEN + 4] = values[offset + i * LINELEN + 1];
		}
		else if (std::abs(values[offset + i * LINELEN + 6]) > std::abs(values[offset + i * LINELEN + 7]))
		{
			values[offset + i * LINELEN + 3] = values[offset + i * LINELEN];
			values[offset + i * LINELEN + 4] = values[offset + i * LINELEN + 2];
		}
		else
		{
			values[offset + i * LINELEN + 3] = values[offset + i * LINELEN];
			values[offset + i * LINELEN + 4] = values[offset + i * LINELEN + 1];
		}
	}
}

std::vector<float> ObjectLoader::getInfo(std::string line)
{
	std::istringstream	stream(line);
	std::vector<float>	values;
	if (line[0] == 'v')
	{
		std::string num;
		std::getline(stream, num, ' ');
		while (std::getline(stream, num, ' '))
			values.push_back(atof(num.c_str()));
		stream.clear();
		return (values);
	}
	std::string			bloc;
	int					i = 0;
	stream >> bloc;
	while (stream >> bloc)
	{
		std::vector<float>::iterator	vInfo;
		std::istringstream				info(bloc);
		std::string						pos, tex, nor;
		
		std::getline(info, pos, '/');
		std::getline(info, tex, '/');
		std::getline(info, nor, ' ');

		try {
			if (pos.empty())
				throw(std::runtime_error(RED BOLD "Object is invalid" CLR));
			if (_vertexInfo.find("v ") == _vertexInfo.end() || atoi(pos.c_str()) - 1 < 0 || (atoi(pos.c_str()) - 1) * 3 + 3 > _vertexInfo["v "].size())
				throw(std::runtime_error(RED BOLD "Object is invalid" CLR));
			vInfo = _vertexInfo["v "].begin() + (atoi(pos.c_str()) - 1) * 3;
			values.insert(values.end(), vInfo, vInfo + 3);
			if (!tex.empty())
			{
				if (_vertexInfo.find("vt") == _vertexInfo.end() || atoi(tex.c_str()) - 1 < 0 || (atoi(tex.c_str()) - 1) * 2 + 2 > _vertexInfo["vt"].size())
					throw(std::runtime_error(RED BOLD "Object is invalid" CLR));
				vInfo = _vertexInfo["vt"].begin() + (atoi(tex.c_str()) - 1) * 2;
				values.insert(values.end(), vInfo, vInfo + 2);
			}
			else
			{
				values.push_back(-2);
				values.push_back(-2);
			}
			if (!nor.empty())
			{
				if (_vertexInfo.find("vn") == _vertexInfo.end() || atoi(nor.c_str()) - 1 < 0 || (atoi(nor.c_str()) - 1) * 3 + 3 > _vertexInfo["vn"].size())
					throw(std::runtime_error(RED BOLD "Object is invalid" CLR));
				vInfo = _vertexInfo["vn"].begin() + (atoi(nor.c_str()) - 1) * 3;
				values.insert(values.end(), vInfo, vInfo + 3);
			}
			else
			{
				values.push_back(-2);
				values.push_back(-2);
				values.push_back(-2);
			}
			values.push_back(0);
		}
		catch (std::exception &e) {
			if (std::string(e.what()).find(RED) != std::string::npos)
				throw(std::invalid_argument(e.what()));
			else
				throw(std::invalid_argument(RED BOLD "Face element is invalid" CLR));
		}
		info.clear();
		i ++;
	}
	if (i == 4)
	{
		values.insert(values.end(), values.begin(), values.begin() + LINELEN);
		values.insert(values.end(), values.begin() + (LINELEN * 2), values.begin() + (LINELEN * 3));
		if (values[5] == -2 || values[LINELEN + 5] == -2 || values[LINELEN * 2 + 5] == -2 || values[LINELEN * 3 + 5] == -2)
			makeNormals(values, true);
		if (values[3] == -2 || values[LINELEN + 5] == -2 || values[LINELEN * 2 + 3] == -2 || values[LINELEN * 3 + 3] == -2)
			makeUV(values, true);
		_nbFaces ++;
	}
	if (values[5] == -2 || values[LINELEN + 5] == -2 || values[LINELEN * 2 + 5] == -2)
		makeNormals(values, false);
	if (values[3] == -2 || values[LINELEN + 5] == -2 || values[LINELEN * 2 + 3] == -2)
		makeUV(values, false);
	_nbFaces ++;
	stream.clear();
	return (values);
}

Object ObjectLoader::loadObject(const std::string &filename)
{
	std::ifstream		file;
	std::string			line;
	std::vector<float>	info;

	if (filename.find_last_of(".obj") != filename.length() - 1)
		throw(std::invalid_argument(RED BOLD + filename + " is not a .obj >:[" CLR));
	_vertexInfo.clear();
	_nbFaces = 0;
	_info = {0, 0, 0};
	file.open(filename.c_str(), std::ifstream::in);
	if (file.fail())
		throw(std::invalid_argument(RED BOLD + filename + " can't be opened" CLR));
	
	while (getline(file, line))
	{
		switch(line[0])
		{
			case 'v': case 'f':
				if (line.substr(0, 2) == "vp" || (std::strncmp(line.c_str(), "v ", 2)
					&& std::strncmp(line.c_str(), "f ", 2) && std::strncmp(line.c_str(), "vt ", 3) && std::strncmp(line.c_str(), "vn ", 3)))
					break;
				info = getInfo(line);
				if (info.empty() || info.begin() == info.end())
					throw(std::runtime_error(RED BOLD "Object is invalid" CLR));
				_vertexInfo[line.substr(0, 2)].insert(_vertexInfo[line.substr(0, 2)].end(), info.begin(), info.end());
				break;
			default:
				break;
		}
	}
	file.close();
	if (_vertexInfo.find("f ") == _vertexInfo.end())
		throw(std::runtime_error(RED BOLD "File is Invalid" CLR));
	return (createObject());
}
