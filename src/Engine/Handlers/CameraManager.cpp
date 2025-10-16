/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:10:48 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/16 18:12:02 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CameraManager.hpp>

CameraManager::CameraManager() {}

CameraManager::~CameraManager() {}

void		CameraManager::update(const float &deltaTime)
{
	_direction.x = cos(math::radians(_yaw) * cos(math::radians(_pitch)));
	_direction.y = sin(math::radians(_pitch));
	_direction.z = sin(math::radians(_yaw) * cos(math::radians(_pitch)));

	_front = math::v3::normalize(_direction);
	_right = math::v3::normalize(math::v3::cross(_front, _up));
	_up = math::v3::normalize(math::v3::cross(_right, _front));
}

void		CameraManager::setViewProjMatric(const Shader &shader)
{
	math::mat4	view = this->getViewMatrix();
	math::mat4	projection = math::mat4::perspective(_fov, _aspectRation, 0.1f, _farPlane);

	(void)shader; //when shaders are implemented this will go and the rest will be uncommented
	// shader.bind();
	// shader.setMat4("view", view);
	// shader.setMat4("projection", projection);
}

math::mat4	CameraManager::getViewMatrix() const
{
	return (math::mat4::lookAt(_pos, _pos + _front, _up));
}
