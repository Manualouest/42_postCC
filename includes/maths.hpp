/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:29:26 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/06 15:36:55 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>

struct v3
{
	float x;
	float y;
	float z;

	v3& operator -(const v3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}

	v3& operator +(const v3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	v3& operator *(const v3& a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
		return *this;
	}

	v3& operator /(const v3& a)
	{
		x /= a.x;
		y /= a.y;
		z /= a.z;
		return *this;
	}

	v3& operator =(const v3& a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}

	v3& operator =(const std::initializer_list<float>& a)
	{
		x = *(a.begin());
		y = *(a.begin() + 1);
		z = *(a.begin() + 2);
		return *this;
	}
};

// struct mat4
// {
// 	std::vector<float>
// }