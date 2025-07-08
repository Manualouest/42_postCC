/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:29:26 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/08 18:02:51 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>

struct v3
{
	float x, y, z;

	v3 operator -(const v3& a)
	{
		v3	res = {0, 0, 0};
		res.x = x - a.x;
		res.y = y - a.y;
		res.z = z - a.z;
		return (res);
	}

	v3 operator +(const v3& a)
	{
		v3	res = {0, 0, 0};
		res.x = x + a.x;
		res.y = y + a.y;
		res.z = z + a.z;
		return (res);
	}

	v3 operator *(const v3& a)
	{
		v3	res = {0, 0, 0};
		res.x = x * a.x;
		res.y = y * a.y;
		res.z = z * a.z;
		return (res);
	}

	v3 operator /(const v3& a)
	{
		v3	res = {0, 0, 0};
		res.x = x / a.x;
		res.y = y / a.y;
		res.z = z / a.z;
		return (res);
	}

	v3& operator =(const v3& a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		return (*this);
	}

	v3& operator =(const std::initializer_list<float>& a)
	{
		x = *(a.begin());
		y = *(a.begin() + 1);
		z = *(a.begin() + 2);
		return (*this);
	}

	bool operator ==(const v3& a)
	{
		return (x == a.x && y == a.y && z == a.z);
	}

	float	sum()
	{
		return (x + y+ z);
	}
};
