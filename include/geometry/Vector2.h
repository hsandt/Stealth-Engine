#pragma once

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iosfwd>

#include <Box2D/Common/b2Math.h>

#include "utils/infix_iterator.h"

// TEST
#include <iostream>

//struct Vector2
class Vector2
{
public:
	float coords[2] = {0, 0};  // required

	Vector2()
	{}

	Vector2(const float nx, const float ny)
	{
		coords[0] = nx;
		coords[1] = ny;
	}

	Vector2(Vector2 const &v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
	}

	Vector2 &operator=(Vector2 const &v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
		return *this;
	}

	Vector2(Vector2 const &&v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
	}

	Vector2 &operator=(Vector2 const &&v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
		return *this;
	}

	/* Conversion functions */

#ifdef B2_MATH_H
	Vector2(b2Vec2 const &b2V)
	{
		coords[0] = b2V.x;
		coords[1] = b2V.y;
	}

	operator b2Vec2() const
	{
		return { coords[0], coords[1] };
	}
#endif

	// Coordinate getter
	float const &x() const { return coords[0]; };

	float const &y() const { return coords[1]; };

	// Coordinate setter
	float &x() { return coords[0]; };

	float &y() { return coords[1]; };

	// Index getter
	float &operator[](const int i)
	{
		assert(i >= 0 && i < 2);
		return coords[i];
	}

	// Index getter const
	const float &operator[](const int i) const
	{
		assert(i >= 0 && i < 2);
		return coords[i];
	}

	// Element-wise operations
	Vector2 operator+(Vector2 const &v) const
	{
		return Vector2(coords[0] + v.coords[0], coords[1] + v.coords[1]);
	}

	Vector2 operator-(Vector2 const &v) const
	{
		return Vector2(coords[0] - v.coords[0], coords[1] - v.coords[1]);
	}

	Vector2 operator*(const float s) const
	{
		return Vector2(coords[0] * s, coords[1] * s);
	}

	Vector2 operator/(const float s) const
	{
		return Vector2(coords[0] / s, coords[1] / s);
	}

	/// Scalar product
	float operator*(Vector2 const &v) const
	{
		return (coords[0] * v.coords[0] + coords[1] * v.coords[1]);
	}

	// Element-wise in-place operations
	Vector2 &operator+=(Vector2 const &v)
	{
		coords[0] += v.coords[0];
		coords[1] += v.coords[1];
		return *this;
	}

	Vector2 &operator-=(Vector2 const &v)
	{
		coords[0] -= v.coords[0];
		coords[1] -= v.coords[1];
		return *this;
	}

	Vector2 &operator*=(const float s)
	{
		coords[0] *= s;
		coords[1] *= s;
		return *this;
	}

	Vector2 &operator/=(const float s)
	{
		coords[0] /= s;
		coords[1] /= s;
		return *this;
	}

	/// Return norm
	float Length() const
	{
		return (float) sqrt(coords[0] * coords[0] + coords[1] * coords[1]);
	}

	/// Return squared norm
	float LengthSquared() const
	{
		return coords[0] * coords[0] + coords[1] * coords[1];
	}

	Vector2 &Normalize()
	{
		float n = Length();
		if (n > 0)
		{
			coords[0] /= n;
			coords[1] /= n;
		}
		return *this;
	}

	bool operator==(Vector2 const &v) const
	{
		return coords[0] == v.coords[0] && coords[1] == v.coords[1];
	}

	bool operator!=(Vector2 const &v) const
	{
		return !(coords == v.coords);
	}

	// Comparisons with higher priority on higher index values (not used)
//    bool operator <(Vector2 const & p) const {
//        return	(v[2] != p.v[2]) ? (v[2] < p.v[2]):
//                (v[1] != p.v[1]) ? (v[1 ]< p.v[1]):
//                        (v[0] < p.v[0]);
//    }
//    bool operator >(Vector2 const & p) const {
//        return	(v[2] != p.v[2]) ? (v[2] > p.v[2]):
//                (v[1] != p.v[1]) ? (v[1] > p.v[1]):
//                        (v[0] > p.v[0]);
//    }
//
//    bool operator <=(Vector2 const & p) const {
//        return	(v[2] != p.v[2])?(v[2] < p.v[2]):
//                (v[1] != p.v[1])?(v[1] < p.v[1]):
//                        (v[0] <= p.v[0]);
//    }
//
//    bool operator >=(Vector2 const & p ) const {
//        return	(v[2] != p.v[2]) ? (v[2] > p.v[2]):
//                (v[1] != p.v[1]) ? (v[1] > p.v[1]):
//                        (v[0] >= p.v[0]);
//    }

	/// Return the distance with another vector
	float Distance(Vector2 const &v) const
	{
		return (*this - v).Length();
	}

	/// Return the squared distance with another vector
	float SquaredDistance(Vector2 const &v) const
	{
		return (*this - v).LengthSquared();
	}

}; // end class definition

// To string
inline std::ostream &operator<<(std::ostream &stream, const Vector2 &v)
{
	stream << "Vec2(";
	std::copy(v.coords, v.coords + 2, infix_ostream_iterator<float>(stream, ", "));
	return stream << ")";
}

inline float Angle(Vector2 const &p1, Vector2 const &p2)
{
	return (float) acos((p1 * p2) / (p1.Length() * p2.Length()));
}

inline Vector2 operator-(Vector2 const &p)
{
	return Vector2(-p.coords[0], -p.coords[1]);
}

inline Vector2 operator*(const float s, Vector2 const &p)
{
	return Vector2(p.coords[0] * s, p.coords[1] * s);
}

inline float Length(Vector2 const &p)
{
	return sqrt(p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1]);
}

inline float LengthSquared(Vector2 const &p)
{
	return (p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1]);
}


/// Return a normalized copy of this vector
inline Vector2 Normalized(Vector2 const &p)
{
	Vector2 p2 = p;
	p2.Normalize();
	return p2;
}

/// Return a clamped copy of this vector
inline Vector2 ClampLength(Vector2 const &p, float maxLength)
{
	float length = p.Length();
	if (length == 0)
		return Vector2(0, 0);

	Vector2 normalizedVector2 = p;
	if (length > maxLength)
	{
		normalizedVector2 *= maxLength / length;
	}
	return normalizedVector2;
}

inline float Distance(Vector2 const &p1, Vector2 const &p2)
{
	return Length(p1 - p2);
}

inline Vector2 &RotateZ(Vector2 &p, float _angle)
{
	float c = cos(_angle);
	float s = sin(_angle);
	float cx = c * p.x() - s * p.y();
	p.y() = s * p.x() + c * p.y();
	p.x() = cx;
	return p;
}
