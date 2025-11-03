/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:52:17 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/26 19:42:50 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Render/ShaderManager.hpp>

ShaderManager	*ShaderManager::_instance = NULL;

ShaderManager::ShaderManager()
{
	if (!_instance)
		_instance = this;
}

ShaderManager::~ShaderManager()
{
}

static int	loadVertexShader(const char *shader)
{
	int				success;
	char			infoLog[512];
	unsigned int	res = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(res, 1, &shader, NULL);
	glCompileShader(res);
	glGetShaderiv(res, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(res, 512, NULL, infoLog);
		std::cout << shader << std::endl;
		std::cout << infoLog << std::endl;
		return (0);
	}
	return (res);
}

static int	loadFragmentShader(const char *shader)
{
	int				success;
	char			infoLog[512];
	unsigned int	res = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(res, 1, &shader, NULL);
	glCompileShader(res);
	glGetShaderiv(res, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(res, 512, NULL, infoLog);
		std::cout << shader << std::endl;
		std::cout << infoLog << std::endl;
		return (0);
	}
	return (res);
}

static int	loadShaderProgram(const char *vertex, const char *fragment)
{
	unsigned int	res;
	int				success;
	char			infoLog[512];
	int				vertexShader;
	int				fragmentShader;
	
	vertexShader = loadVertexShader(vertex);
	if (!vertexShader)
		return (0);
	fragmentShader = loadFragmentShader(fragment);
	if (!fragmentShader)
		return (0);

	res = glCreateProgram();
	glAttachShader(res, vertexShader);
	glAttachShader(res, fragmentShader);
	glLinkProgram(res);
	glGetProgramiv(res, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(res, 512, NULL, infoLog);
		std::cout << vertex << std::endl;
		std::cout << infoLog << std::endl;
		return (0);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return (res);
}

void	ShaderManager::addShader(const std::string &shaderID, const std::string &path)
{
	_checkInstance();
	
	if (_instance->_shaders.find(shaderID) != _instance->_shaders.end())
		throw(std::runtime_error(RED BOLD UNDL "This shader already exist" CLR));

	std::string		vertexCode;
	std::string		fragmentCode;
	std::ifstream	vShaderFile;
	std::ifstream	fShaderFile;

	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(path + ".vert");
		fShaderFile.open(path + ".frag");
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(...)
	{
		throw std::runtime_error("Failed to read shader");
	}

	const char	*vShaderCode = vertexCode.c_str();
	const char	*fShaderCode = fragmentCode.c_str();
	
	_instance->_currentId = loadShaderProgram(vShaderCode, fShaderCode);
	if (!_instance->_currentId)
		throw std::runtime_error("Failed to load shader program");
	_instance->_shaders.insert({shaderID, _instance->_currentId});
}

void	ShaderManager::bindShader(const std::string &shaderID)
{
	_checkInstance();
	_instance->_currentId = _instance->_shaders[shaderID];
	glUseProgram(_instance->_currentId);
}

void	ShaderManager::setBool(const std::string &name, bool value)
{
	_checkInstance();
	glUniform1i(glGetUniformLocation(_instance->_currentId, name.c_str()), (int)value);
}

void	ShaderManager::setInt(const std::string &name, int value)
{
	_checkInstance();
	glUniform1i(glGetUniformLocation(_instance->_currentId, name.c_str()), value);
}

void	ShaderManager::setFloat(const std::string &name, float value)
{
	_checkInstance();
	glUniform1f(glGetUniformLocation(_instance->_currentId, name.c_str()), value);
}

void	ShaderManager::setMat4(const std::string &name, glm::mat4 value)
{
	_checkInstance();
	glUniformMatrix4fv(glGetUniformLocation(_instance->_currentId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void	ShaderManager::setVec3(const std::string &name, glm::vec3 value)
{
	_checkInstance();
	glUniform3fv(glGetUniformLocation(_instance->_currentId, name.c_str()), 1, glm::value_ptr(value));
}

void	ShaderManager::setVec3Array(const std::string &name, glm::vec3 *values, int nbValues)
{
	_checkInstance();
	glUniform3fv(glGetUniformLocation(_instance->_currentId, name.c_str()), nbValues, glm::value_ptr(values[0]));
}

void	ShaderManager::_checkInstance()
{
	if (!_instance)
		throw(std::runtime_error(RED BOLD UNDL "ShaderManager instance not created" CLR));
}