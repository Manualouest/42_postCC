/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:11:36 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/25 10:54:15 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CAMERAMANAGER_HPP
# define CAMERAMANAGER_HPP

#include <Engine/Render/ShaderManager.hpp>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

class	Shader {};

class	CameraManager
{
	public:
		CameraManager();
		~CameraManager();
	
		void		update();
		void		selfUpdate();
		void		setViewProjMatrix();
		glm::mat4	getViewMatrix() const;

		float		getYaw() const		{return (_yaw);}
		float		getPitch() const	{return (_pitch);}
		glm::vec3	getPos() const		{return (_pos);}
		double		getSensi() const	{return (_sensi);}
		double		getSpeed() const	{return (_speed);}

		void	setYaw(const float &yaw)		{_yaw = glm::mod(yaw, 360.f);}
		void	setPitch(const float &pitch)	{_pitch = glm::clamp(pitch, -89.f, 89.f);}
		void	setPos(const glm::vec3 &pos)	{_pos = pos;}

		void	setFov(const float &fov)					{_fov = glm::radians(fov);}
		void	setAspectRation(const float &aspectRation)	{_aspectRation = aspectRation;}
		void	setFarPlane(const float &farPlane)			{_farPlane = farPlane;}
		void	setSensi(const double &newSensi)			{_sensi = newSensi;}
		void	setSpeed(const double &newSpeed)			{_speed = newSpeed;}

	private:
		void		_updatePos();

		float		_yaw = 270.f;
		float		_pitch = 0.f;
		glm::vec3	_pos = {0.f, 0.f, 100.f};

		float	_fov = glm::radians(80.f);
		float	_aspectRation = 1; // 1080 / 1080
		float	_farPlane = 102400;
		double	_sensi = 40.;
		float	_speed = 0.5;
	
		glm::vec3	_direction;
		glm::vec3	_up = {0.f, 1.f, 0.f};
		glm::vec3	_worldUp = {0.0f, 1.0f, 0.0f};
		glm::vec3	_front;
		glm::vec3	_right;
};

#endif