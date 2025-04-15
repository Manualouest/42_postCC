/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:31:35 by mbirou            #+#    #+#             */
/*   Updated: 2025/04/14 19:54:37 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Camera/Camera.hpp>

Camera::Camera(glm::vec3 position)
{
	Position = position;
	lockCursor = -2;
}

void	Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char *uniform, int nWidth, int nHeight)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	width = nWidth;
	height = nHeight;
	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void	Camera::Inputs(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

	if ((lockCursor & 2) && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		
		if ((lockCursor & 1))
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPos(window, width / 2, height / 2);
		}
		else if (!(lockCursor & 1))
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		lockCursor = !(lockCursor & 1);
	}
	else if (!(lockCursor & 2) && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
		lockCursor = 2 | (lockCursor & 1);

	if (lockCursor & 1)
		return ;

	double	mouseX;
	double	mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	
	float roty = sensitivity * (float)(mouseY - (float)(height / 2)) / (float)height;
	float rotx = sensitivity * (float)(mouseX - (float)(width / 2)) / (float)width;

	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-roty), glm::normalize(glm::cross(Orientation, Up)));

	if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) || (glm::angle(newOrientation, -Up) <= glm::radians(5.0f))))
	{
		Orientation = newOrientation;
	}

	Orientation = glm::rotate(Orientation, glm::radians(-rotx), Up);

	double mouseXmove = width / 2 - (width / 2 - mouseX) / 2;
	if (mouseXmove < 1)
		mouseXmove = width / 2;
	glfwSetCursorPos(window, mouseXmove, height / 2);
}
