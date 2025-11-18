/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:11:36 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/18 23:28:22 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CAMERAMANAGER_HPP
# define CAMERAMANAGER_HPP

#include <Engine/Render/ShaderManager.hpp>
#include <Engine/Render/Objects/Window.hpp>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

class	Shader {};

class	CameraManager
{
	public:
		CameraManager();
		~CameraManager();
	
		static void			update();
		static void			selfUpdate();
		static void			setViewProjMatrix();
		static glm::mat4	getViewMatrix();

		static float		getYaw()	{_checkInstance(); return (_instance->_yaw);}
		static float		getPitch()	{_checkInstance(); return (_instance->_pitch);}
		static glm::vec3	getPos()	{_checkInstance(); return (_instance->_pos);}
		static double		getSensi()	{_checkInstance(); return (_instance->_sensi);}
		static double		getSpeed()	{_checkInstance(); return (_instance->_speed);}

		static void	setYaw(const float &yaw)		{_checkInstance(); _instance->_yaw = glm::mod(yaw, 360.f);}
		static void	setPitch(const float &pitch)	{_checkInstance(); _instance->_pitch = glm::clamp(pitch, -89.f, 89.f);}
		static void	setPos(const glm::vec3 &pos)	{_checkInstance(); _instance->_pos = pos;}

		static void	setFov(const float &fov)					{_checkInstance(); _instance->_fov = glm::radians(fov);}
		static void	setAspectRation(const float &aspectRation)	{_checkInstance(); _instance->_aspectRation = aspectRation;}
		static void	setFarPlane(const float &farPlane)			{_checkInstance(); _instance->_farPlane = farPlane;}
		static void	setSensi(const double &newSensi)			{_checkInstance(); _instance->_sensi = newSensi;}
		static void	setSpeed(const double &newSpeed)			{_checkInstance(); _instance->_speed = newSpeed;}

	private:
		static void	_checkInstance();

		void		_updatePos();

		static CameraManager	*_instance;

		float		_yaw = 270.f;
		float		_pitch = -89.f;
		glm::vec3	_pos = {0.f, 150.f, 0.f};

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