/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:57:10 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/03 16:42:23 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Render/TextureManager.hpp>

TextureManager					*TextureManager::_instance = NULL;
// std::string						TextureManager::_currentID = "";
// std::map<std::string, Texture>	TextureManager::_textures = {};


TextureManager::TextureManager()
{
	if (!_instance)
		_instance = this;
}

TextureManager::~TextureManager()
{
	for (auto texture : _textures)
		glDeleteTextures(1, &texture.second.ID);
	
	if (_ArrayID != -1)
		glDeleteTextures(1, &_ArrayID);
}

void	TextureManager::use(const std::string &textureID, const char *uniformName, const int &offset)
{
	_checkInstance();
	if (_instance->_textures.find(textureID) == _instance->_textures.end())
		throw(std::runtime_error(RED BOLD UNDL "Texture doesn't exist" CLR));
	_instance->_currentID = textureID;
	ShaderManager::setInt(uniformName, offset);
	glActiveTexture(GL_TEXTURE0 + offset);
	glBindTexture(GL_TEXTURE_2D, _instance->_textures[_instance->_currentID].ID);
}

void	TextureManager::reset(void)
{
	_checkInstance();
	glBindTexture(GL_TEXTURE_2D, 0);
}

int	TextureManager::loadImage(const std::string &textureID, const char *path)
{
	_checkInstance();

	if (_instance->_textures.find(textureID) != _instance->_textures.end())
		return (getTextureNb(textureID));
		// throw(std::runtime_error(RED BOLD UNDL "This texture already exist" CLR));

	Texture	newTexture(path);

	if (!newTexture.ID)
		throw(std::runtime_error(RED BOLD UNDL "Texture failed to load" CLR));
	_instance->_textures.insert({textureID, newTexture});
	return (getTextureNb(textureID));
}

void	TextureManager::deleteImage(const std::string &textureID)
{
	_checkInstance();
	if (_instance->_textures.find(textureID) != _instance->_textures.end())
	{
		glDeleteTextures(1, &_instance->_textures[textureID].ID);
		_instance->_textures.erase(textureID);
	}
}

Texture	TextureManager::getTexture(const std::string &textureID)
{
	_checkInstance();
	if (_instance->_textures.find(textureID) != _instance->_textures.end())
		return (_instance->_textures[textureID]);
	return (Texture{0});
}

int	TextureManager::getTextureNb(const std::string &textureID)
{
	_checkInstance();
	if (_instance->_textures.find(textureID) == _instance->_textures.end())
		return (-1);
	
	int	i;
	for (auto texture : _instance->_textures)
	{
		if (texture.first == textureID) // put the i++ bove if the texture fails to be taken by the shader
			return (i + 1);
		i ++;
	}
	return (-1);
}


void	TextureManager::useArray(const char *uniformName, const int &offset)
{
	if (_instance->_ArrayID == -1)
		throw(std::runtime_error(RED BOLD UNDL "No texture Array was created" CLR));

	ShaderManager::setInt(uniformName, offset);
	glActiveTexture(GL_TEXTURE0 + offset);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _instance->_ArrayID);
}

void	TextureManager::resetArray()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void	TextureManager::makeArray(const std::set<std::string> &textureIDs)
{
	if (_instance->_ArrayID != -1)
	{
		glDeleteTextures(1, &_instance->_ArrayID);
		_instance->_ArrayID = -1;
	}

	int											depth = 0;
	int											width = 0;
	int											height = 0;
	int											nbLayers = 0;
	std::vector<std::vector<unsigned char> >	datas = {{0}};

	for (auto ID : textureIDs)
	{
		nbLayers ++;
		width = glm::max(width, _instance->_textures[ID].width);
		height = glm::max(height, _instance->_textures[ID].height);
		datas.push_back(_instance->_textures[ID].data);
	}

	glGenTextures(1, &_instance->_ArrayID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _instance->_ArrayID);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, nbLayers + 1);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	for (auto data : datas)
	{
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, depth, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
		depth ++;
	}

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}


void	TextureManager::_checkInstance()
{
	if (!_instance)
		throw(std::runtime_error(RED BOLD UNDL "TextureManager instance not created" CLR));
}
