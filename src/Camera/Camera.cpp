/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:31:35 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 19:11:39 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Camera/Camera.hpp>

Camera::Camera(math::v3 position)
{
	Position = position;
	lockCursor = 1;
	Orientation = math::v3{float(cos(math::radians(yaw)) * cos(math::radians(pitch))), float(sin(math::radians(pitch))), float(sin(math::radians(yaw)) * cos(math::radians(pitch)))};
}

void	Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, float nWidth, float nHeight)
{
	math::mat4 view = math::mat4(1.0f);
	math::mat4 projection = math::mat4(1.0f);

	width = nWidth;
	height = nHeight;
	view = math::mat4::lookAt(Position, Position + Orientation, Up);
	projection = math::mat4::perspective(math::radians(FOVdeg), width / height, nearPlane, farPlane);

	math::mat4	tpMat = projection * view;
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uCamMatrix"), 1, GL_FALSE, &tpMat.data[0]);
}

void	Camera::moveInputs(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position = Position + Orientation * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position = Position + (math::v3::normalize(math::v3::cross(Orientation, Up)) * -1) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position = Position + (Orientation * -1) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position = Position + math::v3::normalize(math::v3::cross(Orientation, Up)) * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position = Position + Up * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		Position = Position + (Up * -1) * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.5f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}
}

void	Camera::Inputs(GLFWwindow *window)
{
	moveInputs(window);
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
	
	float rotx = sensitivity * (float)(mouseX - (float)(width / 2.0f)) / (float)width;
	float roty = sensitivity * (float)(mouseY - (float)(height / 2.0f)) / (float)height;

	yaw += rotx;
	if (yaw > 360)
		yaw -= 360;
	if (yaw < -360)
		yaw += 360;

	if (pitch - roty >= 89)
		pitch = 89;
	else if (pitch - roty <= -89)
		pitch = -89;
	else
		pitch -= roty;

	Orientation = math::v3{float(cos(math::radians(yaw)) * cos(math::radians(pitch))), float(sin(math::radians(pitch))), float(sin(math::radians(yaw)) * cos(math::radians(pitch)))};

	glfwSetCursorPos(window, width / 2, height / 2);
}
