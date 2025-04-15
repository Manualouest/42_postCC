/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:25:12 by mbirou            #+#    #+#             */
/*   Updated: 2025/04/14 19:59:16 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <Shaders/Shaders.hpp>

class Camera
{
	public:
		glm::vec3	Position;
		glm::vec3	Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3	Up = glm::vec3(0.0f, 1.0f, 0.0f);

		int		width;
		int		height;
		float	speed = 0.1f;
		float	sensitivity = 50.0f;
		int		lockCursor : 2;

		Camera(glm::vec3 position);
		void	Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char *uniform, int nWidth, int nHeight);
		void	Inputs(GLFWwindow *window);
};