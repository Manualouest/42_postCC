/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:18 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/06 09:48:43 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERMANAGER_HPP
# define SHADERMANAGER_HPP

# include <spellBook.hpp>

# include <glad/glad.h>
# include <glfw/glfw3.h>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

class	ShaderManager
{
	public:
		ShaderManager();
		~ShaderManager();

		static void	addShader(const std::string &shaderID, const std::string &path);
		static void	deleteshader(const std::string &shaderID);
		static void	bindShader(const std::string &shaderID);

		static void	setBool(const std::string &name, bool value);
		static void	setInt(const std::string &name, int value);
		static void	setFloat(const std::string &name, float value);
		static void	setMat4(const std::string &name, glm::mat4 value);
		static void	setVec3(const std::string &name, glm::vec3 value);
		static void	setVec3Array(const std::string &name, glm::vec3 *values, int nbValues);

	private:
		static void	_checkInstance();

		static ShaderManager	*_instance;

		uint						_currentId;
		std::map<std::string, uint> _shaders;
};

#endif