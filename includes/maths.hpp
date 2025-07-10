/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:29:26 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/10 09:21:40 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <includes.hpp>
#include <cmath>

struct math
{
	struct v3 {
		float x, y, z;

		v3 operator -(const v3 &a) const
		{
			v3	res = {0, 0, 0};
			res.x = x - a.x;
			res.y = y - a.y;
			res.z = z - a.z;
			return (res);
		}

		v3 operator +(const v3 &a) const
		{
			v3	res = {0, 0, 0};
			res.x = x + a.x;
			res.y = y + a.y;
			res.z = z + a.z;
			return (res);
		}

		v3 operator *(const v3 &a) const
		{
			v3	res = {0, 0, 0};
			res.x = x * a.x;
			res.y = y * a.y;
			res.z = z * a.z;
			return (res);
		}

		v3 operator /(const v3 &a) const
		{
			v3	res = {0, 0, 0};
			res.x = x / a.x;
			res.y = y / a.y;
			res.z = z / a.z;
			return (res);
		}

		v3 operator -(const float &a) const
		{
			v3	res = {0, 0, 0};
			res.x = x - a;
			res.y = y - a;
			res.z = z - a;
			return (res);
		}

		v3 operator +(const float &a) const
		{
			v3	res = {0, 0, 0};
			res.x = x + a;
			res.y = y + a;
			res.z = z + a;
			return (res);
		}

		v3 operator *(const float &a) const
		{
			v3	res = {0, 0, 0};
			res.x = x * a;
			res.y = y * a;
			res.z = z * a;
			return (res);
		}

		v3 operator /(const float &a) const
		{
			v3	res = {0, 0, 0};
			res.x = x / a;
			res.y = y / a;
			res.z = z / a;
			return (res);
		}

		v3& operator =(const std::initializer_list<float> &a)
		{
			x = *(a.begin());
			y = *(a.begin() + 1);
			z = *(a.begin() + 2);
			return (*this);
		}

		bool operator ==(const v3 &a)
		{
			return (x == a.x && y == a.y && z == a.z);
		}

		float	sum()
		{
			return (x + y + z);
		}

		static float	dot(const v3 &a, const v3 &b)
		{
			return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
		}

		static float	clamp(const float &a, const float &minv3, const float &maxv3)
		{
			return (std::min(std::max(a, minv3), maxv3));
		}

		static float	acos(const float &a)
		{
			return (__builtin_acosf(a));
		}

		static float	angle(const v3 &a, const v3 &b)
		{
			return v3::acos(v3::clamp(v3::dot(a, b), -1, 1));
		}

		static float	length(const v3 &a)
		{
			return std::sqrt(dot(a, a));
		}

		static v3	normalize(const v3 &a)
		{
			float len = length(a);
			if (len <= 0)
				return (v3{0, 0, 0});
			float oneOverLen = 1.0f / len;
			return (v3{a.x * oneOverLen, a.y * oneOverLen, a.z * oneOverLen});
		}

		static v3	cross(const v3 &a, const v3 &b)
		{
			return (v3{a.y * b.z - a.z * b.y,
						a.z * b.x - a.x * b.z,
						a.x * b.y - a.y * b.x});
		}
	};

	struct v4
	{
		public:
        float x, y, z, w;

	    ~v4(){}
        v4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw)
	    {}
        v4() : x(0), y(0), z(0), w(0)
	    {}
        v4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	    {}
    
        v4 operator+(const v4 &v) const
	    {
	    	return v4(x + v.x, y + v.y, z + v.z, w + v.w);
	    }
        v4 operator-(const v4 &v) const
	    {
	    	return v4(x - v.x, y - v.y, z - v.z, w - v.w);
	    }
        v4 operator*(float s) const
	    {
	    	return v4(x * s, y * s, z * s, w * s);
	    }
        v4 operator/(float s) const
	    {
	    	return v4(x / s, y / s, z / s, w / s);
	    }
    
        float dot(const v4 &v) const
	    {
	    	return (x * v.x + y * v.y + z * v.z + w * v.w);
	    }
        float length() const
	    {
	    	return (std::sqrt(x * x + y * y + z * z + w * w));
	    }
        v4 normalize() const
	    {
            float len = length();
            return len > 0.0f ? *this / len : v4(0, 0, 0, 0);
        }
	};

	struct mat4
	{
    	float data[16];

    	static mat4 identity()
		{
    	    mat4 m;
    	    std::fill(m.data, m.data + 16, 0.0f);
    	    m.data[0] = m.data[5] = m.data[10] = m.data[15] = 1.0f;
    	    return (m);
    	}
		
		mat4()
		{
    	    std::fill(data, data + 16, 0.0f);
    	}
        mat4(float val)
		{
    	    std::fill(data, data + 16, 0.0f);
            this->data[0] = this->data[5] = this->data[10] = this->data[15] = val;
    	}
		mat4(const mat4 &cpy)
		{
            *this = cpy;
    	}
        mat4 &operator =(const mat4 &cpy)
        {
            for (int i = 0; i < 16; i++)
                this->data[i] = cpy.data[i];
            return (*this);
        }
		
		mat4 operator *(const mat4 &b)
		{
			mat4 result;
			for (int col = 0; col < 4; ++col)
			{
				for (int row = 0; row < 4; ++row)
				{
					result(col, row) = 0.0f;
					for (int k = 0; k < 4; ++k)
						result(col, row) += (*this)(k, row) * b(col, k);
				}
			}
			return (result);
		}

    	float &operator ()(int col, int row)
		{
			return (data[col * 4 + row]);
		}
    	const float &operator ()(int col, int row) const
		{
			return (data[col * 4 + row]);
		}

		static mat4 rotate(mat4 &mat, float angleRad, const math::v3 &axis)
		{
			return (mat * rotate(angleRad, axis));
		}

		static mat4 rotate(float angleRad, const math::v3 &axis)
		{
			math::v3 a = math::v3::normalize(axis);
			float c = cos(angleRad);
			float s = sin(angleRad);
			float oneMinusC = 1.0f - c;

			mat4 m = mat4::identity();
			m(0, 0) = c + a.x * a.x * oneMinusC;
			m(0, 1) = a.x * a.y * oneMinusC + a.z * s;
			m(0, 2) = a.x * a.z * oneMinusC - a.y * s;

			m(1, 0) = a.y * a.x * oneMinusC - a.z * s;
			m(1, 1) = c + a.y * a.y * oneMinusC;
			m(1, 2) = a.y * a.z * oneMinusC + a.x * s;

			m(2, 0) = a.z * a.x * oneMinusC + a.y * s;
			m(2, 1) = a.z * a.y * oneMinusC - a.x * s;
			m(2, 2) = c + a.z * a.z * oneMinusC;

			return (m);
		}

		static mat4 lookAt(const math::v3 &eye, const math::v3  center, const math::v3 &up)
		{
			v3 f = math::v3::normalize(center - eye);
			v3 s = math::v3::normalize(math::v3::cross(f, up));
			v3 u = math::v3::cross(s, f);

			mat4 m = mat4::identity();
			m(0, 0) = s.x; m(1, 0) = s.y; m(2, 0) = s.z;
			m(0, 1) = u.x; m(1, 1) = u.y; m(2, 1) = u.z;
			m(0, 2) = -f.x; m(1, 2) = -f.y; m(2, 2) = -f.z;
			m(3, 0) = math::v3::dot(s, eye) * -1;
			m(3, 1) = math::v3::dot(u, eye) * -1;
			m(3, 2) = math::v3::dot(f, eye);
			return (m);
		}

		static mat4 perspective(const float &fovy, const float &aspect, const float &zNear, const float &zFar)
		{
			const float tanHalfFovy = tan(fovy / 2.0f);

			math::mat4 Result(0);
			Result(0, 0) = 1.0f / (aspect * tanHalfFovy);
			Result(1, 1) = 1.0f / (tanHalfFovy);
			Result(2, 2) = - (zFar + zNear) / (zFar - zNear);
			Result(2, 3) = - 1.0f;
			Result(3, 2) = - (2.0f * zFar * zNear) / (zFar - zNear);
			return Result;
		}

		static mat4 ortho(const float &left, const float &right, const float &bottom, const float &top, const float &zNear, const float &zFar)
		{
			math::mat4 Result(1);
			Result(0, 0) = 2.0f / (right - left);
			Result(1, 1) = 2.0f / (top - bottom);
			Result(2, 2) = - 2.0f / (zFar - zNear);
			Result(3, 0) = - (right + left) / (right - left);
			Result(3, 1) = - (top + bottom) / (top - bottom);
			Result(3, 2) = - (zFar + zNear) / (zFar - zNear);
			return (Result);
		}

		static v4 getCol(const mat4 &m, int col)
		{
			return v4(m(col, 0), m(col, 1), m(col, 2), m(col, 3));
		}

		static void setCol(mat4 &m, int col, const v4 &v)
		{
			m(col, 0) = v.x;
			m(col, 1) = v.y;
			m(col, 2) = v.z;
			m(col, 3) = v.w;
		}

		static mat4 translate(const mat4 &m, const v3 &v)
		{
			mat4 result = m;

			v4 col0 = getCol(m, 0);
			v4 col1 = getCol(m, 1);
			v4 col2 = getCol(m, 2);
			v4 col3 = getCol(m, 3);

			v4 translation = col0 * v.x + col1 * v.y + col2 * v.z + col3;

			setCol(result, 3, translation);

			return (result);
		}
	};

	static float radians(float degrees)
	{
		return degrees * 0.01745329251994329576923690768489;
	}
};



