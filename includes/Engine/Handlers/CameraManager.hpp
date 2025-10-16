/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:10:26 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/16 18:11:23 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.hpp>

class	Shader {};

class	CameraManager
{
	public:
		CameraManager();
		~CameraManager();
	
		void		update(const float &deltaTime);
		void		setViewProjMatric(const Shader &shader);
		math::mat4	getViewMatrix() const;

		float		getYaw() const {return (_yaw);};
		float		getPitch() const {return (_pitch);};
		math::v3	getPos() const {return (_pos);};

		void	setYaw(const float &yaw) {_yaw = yaw;};
		void	setPitch(const float &pitch) {_pitch = pitch;};
		void	setPos(const math::v3 &pos) {_pos = pos;};

		void	setFov(const float &fov) {_fov = math::radians(fov);};
		void	setAspectRation(const float &aspectRation) {_aspectRation = aspectRation;};
		void	setFarPlane(const float &farPlane) {_farPlane = farPlane;};

	private:
		float		_fov = math::radians(80);
		float		_aspectRation = 1.653846154; // 860 / 520
		float		_farPlane = 1024;
		float		_yaw = 0.f;
		float		_pitch = 0.f;
	
		math::v3	_pos = {0.f, 0.f, 0.f};
		math::v3	_direction;
		math::v3	_up = {0.f, 1.f, 0.f};
		math::v3	_front;
		math::v3	_right;
		
};