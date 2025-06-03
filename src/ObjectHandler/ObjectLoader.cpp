/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectLoader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/06/03 18:45:20 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ObjectHandler/ObjectLoader.hpp>

std::map<std::string, std::vector<float> >	ObjectLoader::vertexInfo;
std::map<std::string, std::vector<float> >	ObjectLoader::indices;

void	ObjectLoader::addVertexInfo(const std::string &line)
{
	vertexInfo[line.substr(0, 2)].insert(vertexInfo[line.substr(0, 2)].end(), );
}

void	ObjectLoader::addIndiceInfo(const std::string &line)
{

}

Object ObjectLoader::loadObject(const std::string &filename)
{
	std::istream	file;
	std::string		line;

	file.open(filename.c_str(), std::ifstream::in);
	if (file.fail())
		throw(std::invalid_argument(filename + " can't be opened"));
	
	while (getline(file, line))
	{
		switch(line[0])
		{
			catch 'v':
				addVertexInfo(line);
				break;
			catch 'f':
				addIndiceInfo(line);
				break;
			catch 'o': case '#': // useless rn ig
			{
				break;
			}
			default:
			{
				if (line.find("mtllib") == 0)
					; // a parse le fichier mtl
				else
				{
					PRINT line ENDL;
					throw(std::invalid_argument(filename + " is invalid"));
				}
			}
		}
	}
}