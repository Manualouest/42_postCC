/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectLoader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/05 19:08:23 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ObjectHandler/ObjectLoader.hpp>

std::map<std::string, std::vector<float> >	ObjectLoader::_vertexInfo;
ObjectLoader::info							ObjectLoader::_info;
std::vector<std::string>					ObjectLoader::_infoTypes = {"v ", "vt", "vn", "f "};

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
	VAO	_VAO = VAO(1);
	_VAO.Bind();
	VBO	_VBO = VBO(_vertexInfo["f "].data(), _vertexInfo["f "].size() * sizeof(float));

	_VAO.linkAttrib(_VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	_VAO.linkAttrib(_VBO, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	_VAO.linkAttrib(_VBO, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	_VAO.Unbind();
	_VBO.Unbind();
	return (Object(_VAO, _VBO, _vertexInfo["f "]));
}

std::vector<float> ObjectLoader::getInfo(std::string line)
{
	std::istringstream	stream(line);
	if (line[0] == 'v')
	{
		float dummy, a, b, c;
		stream >> dummy >> a >> b >> c;
		stream.clear();
		return {a, b, c};
	}
	std::vector<float>	values;
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
			if (!nor.empty())
			{
				vInfo = _vertexInfo["vn"].begin() + (atoi(nor.c_str()) - 1) * 3;
				values.insert(values.end(), vInfo, vInfo + 3);
			}
		}
		catch (std::exception &e) {
			throw(std::invalid_argument("Face element is invalid"));
		}

		info.clear();
	}
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
	presetVectors(filename);
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
