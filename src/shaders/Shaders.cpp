/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shaders.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:55:22 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 17:15:26 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Shaders/Shaders.hpp>

std::string get_file(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in.fail())
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(std::runtime_error(RED BOLD "Shader failed to open" CLR));
}

Shader::Shader(const char *vertexFile, const char *fragFile)
{
	std::string vertexCode = get_file(vertexFile);
	std::string fragCode = get_file(fragFile);

	const char *vertexSource = vertexCode.c_str();
	const char *fragSource = fragCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");


	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	Delete();
}

void	Shader::Activate()
{
	glUseProgram(ID);
}

void	Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char *type)
{
	GLint	hasCompiled;
	char	infoLog[1024];
	if (std::strcmp(type, "PROGRAM"))
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			throw(std::runtime_error(RED BOLD "SHADER_COMPILATION_ERROR for:" + std::string(type) + "\n" + infoLog + CLR));
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			throw(std::runtime_error(RED BOLD "SHADER_LINKING_ERROR for:" + std::string(type) + "\n" + infoLog + CLR));
		}
	}
}
