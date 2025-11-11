/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:57:10 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/08 15:47:18 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Render/TextureManager.hpp>

TextureManager					*TextureManager::_instance = NULL;

TextureManager::TextureManager()
{
	if (!_instance)
		_instance = this;
}

TextureManager::~TextureManager()
{
	_checkInstance();
	
	for (auto texture : _instance->_textures)
		glDeleteTextures(1, &texture.second.ID);
	
	_instance->_textures.clear();

	for (auto array : _instance->_arrays)
		glDeleteTextures(1, &array.second);
	
	_instance->_arrays.clear();

	_instance = NULL;

	PRINT DSTR BOLD "TextureManager Destroyed" CENDL;
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

void	TextureManager::loadImage(const std::string &textureID, const char *path)
{
	_checkInstance();

	if (_instance->_textures.find(textureID) != _instance->_textures.end())
		throw(std::runtime_error(RED BOLD UNDL "The texture already exist" CLR));

	Texture	newTexture(path);

	if (!newTexture.ID)
		throw(std::runtime_error(RED BOLD UNDL "Texture failed to load" CLR));
	_instance->_textures.insert({textureID, newTexture});
}

void	TextureManager::deleteTexture(const std::string &textureID)
{
	_checkInstance();

	if (_instance->_textures.find(textureID) != _instance->_textures.end())
	{
		glDeleteTextures(1, &_instance->_textures[textureID].ID);
		_instance->_textures.erase(textureID);
	}
}

void	TextureManager::deleteTextures(const std::vector<std::string> &textureIDs)
{
	_checkInstance();

	for (auto textureID : textureIDs)
		deleteTexture(textureID);
}


Texture	TextureManager::getTexture(const std::string &textureID)
{
	_checkInstance();

	if (_instance->_textures.find(textureID) != _instance->_textures.end())
		return (_instance->_textures[textureID]);
	return (Texture{0});
}

void	TextureManager::useArray(const std::string &arrayID, const char *uniformName, const int &offset)
{
	_checkInstance();

	if (_instance->_arrays.find(arrayID) == _instance->_arrays.end())
		throw(std::runtime_error(RED BOLD UNDL "No texture Array was created" CLR));

	ShaderManager::setInt(uniformName, offset);
	glActiveTexture(GL_TEXTURE0 + offset);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _instance->_arrays[arrayID]);
}

void	TextureManager::resetArray()
{
	_checkInstance();

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void	TextureManager::deleteArray(const std::string &arrayID)
{
	_checkInstance();

	if (_instance->_arrays.find(arrayID) != _instance->_arrays.end())
	{
		glDeleteTextures(1, &_instance->_arrays[arrayID]);
		_instance->_arrays.erase(arrayID);
	}
}

void	TextureManager::makeArray(const std::string &arrayID, const std::vector<std::string> &textureIDs)
{
	_checkInstance();

	if (_instance->_arrays.find(arrayID) != _instance->_arrays.end())
		throw(std::runtime_error(RED BOLD UNDL "This array already exists" CLR));

	_instance->_arrays.insert(std::make_pair(arrayID, -1));

	int	depth = 0;
	int	width = 0;
	int	height = 0;
	int	nbLayers = 0;

	for (auto ID : textureIDs)
	{
		nbLayers ++;
		width = glm::max(width, _instance->_textures[ID].width);
		height = glm::max(height, _instance->_textures[ID].height);
	}

	glGenTextures(1, &_instance->_arrays[arrayID]);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _instance->_arrays[arrayID]);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, nbLayers + 1);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (auto ID : textureIDs)
	{
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, depth, _instance->_textures[ID].width, _instance->_textures[ID].height,
						1, GL_RGBA, GL_UNSIGNED_BYTE, _instance->_textures[ID].data.data());
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
