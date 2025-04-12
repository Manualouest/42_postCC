/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shaders.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:49:40 by mbirou            #+#    #+#             */
/*   Updated: 2025/04/12 19:52:53 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <spellBook.hpp>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cerrno>

std::string get_file(const char *filename);

class Shader
{
	public:
		GLuint	ID;
		Shader(const char *vertexFile, const char *fragFile);

		void	Activate();
		void	Delete();
		void	compileErrors(unsigned int shader, const char *type);
};
