/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:49:17 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/25 14:09:29 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <Engine/Render/CameraManager.hpp>
#include <Engine/Engine.hpp>

CameraManager::CameraManager() {}

CameraManager::~CameraManager() {}

void	CameraManager::update()
{
	_direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_direction.y = sin(glm::radians(_pitch));
	_direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_front = glm::normalize(_direction);
	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front));
	_updatePos();
}

void	CameraManager::selfUpdate()
{
	_aspectRation = WWIDTH / WHEIGHT;
	setYaw(_yaw + _sensi * (Engine::getMousePosX() - (WWIDTH / 2.f)) / (float)WWIDTH);
	setPitch(_pitch - _sensi * (Engine::getMousePosY() - (WHEIGHT / 2.f)) / (float)WHEIGHT);
	update();
	_updatePos();
}

void	CameraManager::setViewProjMatrix()
{
	glm::mat4	view = this->getViewMatrix();
	glm::mat4	projections = glm::perspective(_fov, _aspectRation, 0.1f, _farPlane);

	ShaderManager::setMat4("view", view);
	ShaderManager::setMat4("proj", projections);
}

glm::mat4	CameraManager::getViewMatrix() const
{
	return (glm::lookAt(_pos, _pos + _front, _worldUp));
}

void	CameraManager::_updatePos()
{
	if (Engine::getRepeatInput(GLFW_KEY_W))
		_pos += _direction * _speed;
	if (Engine::getRepeatInput(GLFW_KEY_S))
		_pos += -_direction * _speed;
	if (Engine::getRepeatInput(GLFW_KEY_A))
		_pos += -_right * _speed;
	if (Engine::getRepeatInput(GLFW_KEY_D))
		_pos += _right * _speed;

	if (Engine::getRepeatInput(GLFW_KEY_SPACE))
		_pos += _worldUp * _speed;
	if (Engine::getRepeatInput(GLFW_KEY_LEFT_ALT))
		_pos += -_worldUp * _speed;
	
	if (Engine::getRepeatInput(GLFW_KEY_LEFT_SHIFT))
		_speed = 10.;
	else
		_speed = 0.5;
}
