/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectLoader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 13:26:49 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ObjectHandler/ObjectLoader.hpp>

std::map<std::string, std::vector<float> >	ObjectLoader::_vertexInfo;
ObjectLoader::info							ObjectLoader::_info = {0, 0, 0};
std::vector<std::string>					ObjectLoader::_infoTypes = {"v ", "vt", "vn", "f "};
int											ObjectLoader::_nbFaces = 0;

void	ObjectLoader::presetVectors(const std::string &filename)
{
	std::ifstream	file;
	std::string		line;
	std::string		typeRead = "";
	int				nbType = 0;

	file.open(filename.c_str(), std::ifstream::in);
	if (file.fail())
		throw(std::invalid_argument(filename + " can't be opened"));
	while (getline(file, line))
	{
		if (std::find(_infoTypes.begin(), _infoTypes.end(), line.substr(0, 2)) == _infoTypes.end())
			continue;
		if (typeRead == "")
			typeRead = line.substr(0, 2);
		if (typeRead != line.substr(0, 2))
		{
			if (_vertexInfo.find(typeRead) != _vertexInfo.end())
				throw(std::invalid_argument(filename + " is unusable"));
			_vertexInfo.insert({typeRead, {}});
			_vertexInfo[typeRead].reserve(nbType);
			typeRead = line.substr(0, 2);
			nbType = 0;
		}
		nbType ++;
	}
	if (_vertexInfo.find(typeRead) != _vertexInfo.end())
		throw(std::invalid_argument(filename + " is unusable"));
	_vertexInfo.insert({typeRead, {}});
	_vertexInfo[typeRead].reserve(nbType);
	file.close();
}

Object	ObjectLoader::createObject()
{

	int i = 0;
	// for (std::vector<float>::iterator it = _vertexInfo["v "].begin(); it != _vertexInfo["v "].end(); ++it)
	// {
	// 	if (i == 3)
	// 	{
	// 		NEWL;
	// 		i = 0;
	// 	}
	// 	PRINT *it << "; ";
	// 	++i;
	// }
	// NEWL;
	// NEWL;
	// PRINT "NOW VT:" ENDL;
	// i = 0;
	// for (std::vector<float>::iterator it = _vertexInfo["vt"].begin(); it != _vertexInfo["vt"].end(); ++it)
	// {
	// 	if (i == 2)
	// 	{
	// 		NEWL;
	// 		i = 0;
	// 	}
	// 	PRINT *it << "; ";
	// 	++i;
	// }
	// NEWL;
	// NEWL;
	// PRINT "NOW VN:" ENDL;
	// i = 0;
	// for (std::vector<float>::iterator it = _vertexInfo["vn"].begin(); it != _vertexInfo["vn"].end(); ++it)
	// {
	// 	if (i == 3)
	// 	{
	// 		NEWL;
	// 		i = 0;
	// 	}
	// 	PRINT *it << "; ";
	// 	++i;
	// }
	// NEWL;
	// NEWL;
	// PRINT "NOW F:" ENDL;

	// i = 0;
	// for (std::vector<float>::iterator it = _vertexInfo["f "].begin(); it != _vertexInfo["f "].end(); ++it)
	// {
	// 	if (i == 8)
	// 	{
	// 		NEWL;
	// 		i = 0;
	// 	}
	// 	PRINT *it << "; ";
	// 	++i;
	// }

	VAO	_VAO = VAO(1);
	_VAO.Bind();
	VBO	_VBO = VBO(_vertexInfo["f "].data(), _vertexInfo["f "].size() * sizeof(float));

	_VAO.linkAttrib(_VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	_VAO.linkAttrib(_VBO, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	_VAO.linkAttrib(_VBO, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	_VAO.Unbind();
	_VBO.Unbind();
	return (Object(_VAO, _VBO, _vertexInfo["f "], _nbFaces));
}

void	makeNormals(std::vector<float> &values, bool isquad)
{
	int		offset = isquad * 24;
	float	a[3];
	float	b[3];
	float	c[3];

	a[0] = values[offset + 8] - values[offset + 0];
	a[1] = values[offset + 9] - values[offset + 1];
	a[2] = values[offset + 10] - values[offset + 2];
	b[0] = values[offset + 16] - values[offset + 0];
	b[1] = values[offset + 17] - values[offset + 1];
	b[2] = values[offset + 18] - values[offset + 2];
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
		values[offset + i * 8 + 5] = c[0];
		values[offset + i * 8 + 6] = c[1];
		values[offset + i * 8 + 7] = c[2];
	}
}

void	makeUV(std::vector<float> &values, bool isquad)
{
	int	offset = isquad * 24;
	for (int i = 0; i < 3; ++i)
	{
		if (std::abs(values[offset + i * 8 + 5]) > std::abs(values[offset + i * 8 + 6])
			&& std::abs(values[offset + i * 8 + 5]) > std::abs(values[offset + i * 8 + 7]))
		{
			values[offset + i * 8 + 3] = values[offset + i * 8 + 2];
			values[offset + i * 8 + 4] = values[offset + i * 8 + 1];
		}
		else if (std::abs(values[offset + i * 8 + 6]) > std::abs(values[offset + i * 8 + 7]))
		{
			values[offset + i * 8 + 3] = values[offset + i * 8];
			values[offset + i * 8 + 4] = values[offset + i * 8 + 2];
		}
		else
		{
			values[offset + i * 8 + 3] = values[offset + i * 8];
			values[offset + i * 8 + 4] = values[offset + i * 8 + 1];
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
			vInfo = _vertexInfo["v "].begin() + (atoi(pos.c_str()) - 1) * 3;
			values.insert(values.end(), vInfo, vInfo + 3);
			if (!tex.empty())
			{
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
				vInfo = _vertexInfo["vn"].begin() + (atoi(nor.c_str()) - 1) * 3;
				values.insert(values.end(), vInfo, vInfo + 3);
			}
			else
			{
				values.push_back(-2);
				values.push_back(-2);
				values.push_back(-2);
			}
		}
		catch (std::exception &e) {
			throw(std::invalid_argument("Face element is invalid"));
		}

		info.clear();
		i ++;
	}
	if (i == 4)
	{
		values.insert(values.end(), values.begin(), values.begin() + 8);
		values.insert(values.end(), values.begin() + 16, values.begin() + 24);
		if (values[5] == -2 || values[13] == -2 || values[21] == -2 || values[29] == -2)
			makeNormals(values, true);
		if (values[3] == -2 || values[11] == -2 || values[19] == -2 || values[27] == -2)
			makeUV(values, true);
		_nbFaces ++;
	}
	if (values[5] == -2 || values[13] == -2 || values[21] == -2)
		makeNormals(values, false);
	if (values[3] == -2 || values[11] == -2 || values[19] == -2)
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

	// if (filename.find_last_of(".obj") != filename.length() - 4)
	// 	throw(std::invalid_argument(filename + " is not a .obj >:["));
	_vertexInfo.clear();
	_nbFaces = 0;
	_info = {0, 0, 0};
	// presetVectors(filename);
	file.open(filename.c_str(), std::ifstream::in);
	if (file.fail())
		throw(std::invalid_argument(filename + " can't be opened"));
	
	while (getline(file, line))
	{
		switch(line[0])
		{
			case 'v': case 'f':
				if (line.substr(0, 2) == "vp")
					break;
				info = getInfo(line);
				_vertexInfo[line.substr(0, 2)].insert(_vertexInfo[line.substr(0, 2)].end(), info.begin(), info.end());
				break;
			case 'o': case '#': case 's': // useless rn ig
				break;
			default:
			{
				if (line.find("mtllib") == 0)
					; // a parse le fichier mtl
				else
				{
					PRINT line ENDL;
					// throw(std::invalid_argument(filename + " is invalid"));
				}
			}
		}
	}
	file.close();
	return (createObject());
}
