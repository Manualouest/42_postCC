/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectLoader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:56 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 13:25:20 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ObjectHandler/Object.hpp>

// # define GETINFO(_info) {_info.a, _info.b, _info.c}

class ObjectLoader
{
	public:
		static Object loadObject(const std::string &filename);
	
	private:
		ObjectLoader();
		~ObjectLoader();

		static void					addVertexInfo(const std::string &line);
		static void					presetVectors(const std::string &filename);
		static std::vector<float>	getInfo(std::string line);
		static Object				createObject();

		static std::map<std::string, std::vector<float> >	_vertexInfo;
		static struct info {float a; float b; float c;}		_info;
		static std::vector<std::string>						_infoTypes;
		static int											_nbFaces;
};
