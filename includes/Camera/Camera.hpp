/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:25:12 by mbirou            #+#    #+#             */
/*   Updated: 2025/06/01 14:36:17 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Shaders/Shaders.hpp>

class Camera
{
	public:
		glm::vec3	Position;
		glm::vec3	Orientation = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3	Up = glm::vec3(0.0f, 1.0f, 0.0f);

		float	width;
		float	height;
		float	speed = 0.1f;
		float	sensitivity = 50.0f;
		int		lockCursor : 2;

		Camera(glm::vec3 position);
		void	Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char *uniform, float nWidth, float nHeight);
		void	Inputs(GLFWwindow *window);
};