/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:49:17 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/20 10:51:06 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <Engine/Render/CameraManager.hpp>

CameraManager	*CameraManager::_instance = NULL;

CameraManager::CameraManager()
{
	if (!_instance)
		_instance = this;
}

CameraManager::~CameraManager()
{
	_instance = NULL;
}

void	CameraManager::update()
{
	_checkInstance();

	_instance->_direction.x = cos(glm::radians(_instance->_yaw)) * cos(glm::radians(_instance->_pitch));
	_instance->_direction.y = sin(glm::radians(_instance->_pitch));
	_instance->_direction.z = sin(glm::radians(_instance->_yaw)) * cos(glm::radians(_instance->_pitch));

	_instance->_front = glm::normalize(_instance->_direction);
	_instance->_right = glm::normalize(glm::cross(_instance->_front, _instance->_worldUp));
	_instance->_up = glm::normalize(glm::cross(_instance->_right, _instance->_front));
	_instance->_updatePos();
}

void	CameraManager::selfUpdate()
{
	_checkInstance();

	setYaw(_instance->_yaw + _instance->_sensi * (Window::getMousePosX() - (WWIDTH / 2.f)) / (float)WWIDTH);
	setPitch(_instance->_pitch - _instance->_sensi * (Window::getMousePosY() - (WHEIGHT / 2.f)) / (float)WHEIGHT);
	update();
	_instance->_updatePos();
}

void	CameraManager::setViewProjMatrix()
{
	_checkInstance();

	glm::mat4	view = _instance->getViewMatrix();
	glm::mat4	projections = glm::perspective(_instance->_fov, _instance->_aspectRation, 0.1f, _instance->_farPlane);

	ShaderManager::setMat4("view", view);
	ShaderManager::setMat4("proj", projections);
}

glm::mat4	CameraManager::getViewMatrix()
{
	_checkInstance();

	return (glm::lookAt(_instance->_pos, _instance->_pos + _instance->_front, _instance->_worldUp));
}

void	CameraManager::_updatePos()
{
	if (Window::getRepeatInput(GLFW_KEY_LEFT_SHIFT))
		_speed = 100. * Window::getDeltaTime();
	else
		_speed = 1 * Window::getDeltaTime();

	if (Window::getRepeatInput(GLFW_KEY_W))
		_pos += _direction * _speed;
	if (Window::getRepeatInput(GLFW_KEY_S))
		_pos += -_direction * _speed;
	if (Window::getRepeatInput(GLFW_KEY_A))
		_pos += -_right * _speed;
	if (Window::getRepeatInput(GLFW_KEY_D))
		_pos += _right * _speed;

	if (Window::getRepeatInput(GLFW_KEY_SPACE))
		_pos += _worldUp * _speed;
	if (Window::getRepeatInput(GLFW_KEY_LEFT_ALT))
		_pos += -_worldUp * _speed;
}

void	CameraManager::_checkInstance()
{
	if (!_instance)
		throw(std::runtime_error(RED BOLD UNDL "CameraManager instance not created" CLR));
}