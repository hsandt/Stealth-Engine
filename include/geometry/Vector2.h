#pragma once

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iosfwd>

#include "utils/infix_iterator.h"

struct Vector2
{
	float coords[2] = {0, 0};

	Vector2() {}

	Vector2(const FLTYPE nx, const FLTYPE ny)
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

	/* Conversion functions */

#ifdef BOX2D_H
	Vector2(b2Vec2 const &b2V)
	{
		coords[0] = b2V.x;
		coords[1] = b2V.y;
	}

	operator b2Vec2() const
	{
		return {coords[0], coords[1]};
	}
#endif

	// Coordinate reference getter
	FLTYPE &x() { return coords[0]; };

	FLTYPE &y() { return coords[1]; };

	// Index getter
	FLTYPE &operator[](const int i)
	{
		assert(i >= 0 && i < 2);
		return coords[i];
	}

	// Index getter const
	const FLTYPE &operator[](const int i) const
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

	Vector2 operator*(const FLTYPE s) const
	{
		return Vector2(coords[0] * s, coords[1] * s);
	}

	Vector2 operator/(const FLTYPE s) const
	{
		return Vector2(coords[0] / s, coords[1] / s);
	}

	/// Scalar product
	FLTYPE operator*(Vector2 const &v) const
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

	Vector2 &operator*=(const FLTYPE s)
	{
		coords[0] *= s;
		coords[1] *= s;
		return *this;
	}

	Vector2 &operator/=(const FLTYPE s)
	{
		coords[0] /= s;
		coords[1] /= s;
		return *this;
	}

	/// Return norm
	FLTYPE Length() const
	{
		return (FLTYPE) sqrt(coords[0] * coords[0] + coords[1] * coords[1]);
	}

	/// Return squared norm
	FLTYPE LengthSquared() const
	{
		return coords[0] * coords[0] + coords[1] * coords[1];
	}

	Vector2 &Normalize()
	{
		FLTYPE n = Length();
		if (n > 0) {
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
	FLTYPE Distance(Vector2 const &v) const
	{
		return (*this - v).Length();
	}

	/// Return the squared distance with another vector
	FLTYPE SquaredDistance(Vector2 const &v) const
	{
		return (*this - v).LengthSquared();
	}

}; // end class definition

// To string
inline std::ostream& operator<<(std::ostream &stream, const Vector2 &v)
{
	stream << "Vec2(";
	std::copy(v.coords, v.coords + 2, infix_ostream_iterator<FLTYPE>(stream, ", "));
	return stream << ")";
}

inline FLTYPE Angle(Vector2 const &p1, Vector2 const &p2)
{
	return (FLTYPE) acos((p1 * p2) / (p1.Length() * p2.Length()));
}

inline Vector2 operator-(Vector2 const &p)
{
	return Vector2(-p.coords[0], -p.coords[1]);
}

inline Vector2 operator*(const FLTYPE s, Vector2 const &p)
{
	return Vector2(p.coords[0] * s, p.coords[1] * s);
}

inline FLTYPE Length(Vector2 const &p)
{
	return sqrt(p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1]);
}

inline FLTYPE LengthSquared(Vector2 const &p)
{
	return (p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1]);
}

inline Vector2 &Normalize(Vector2 &p)
{
	FLTYPE n = Length(p);
	if (n > 0.0) p /= n;
	return p;
}

inline FLTYPE Distance(Vector2 const &p1, Vector2 const &p2)
{
	return Length(p1 - p2);
}

inline Vector2 &RotateZ(Vector2 &p, FLTYPE _angle)
{
	FLTYPE c = cos(_angle);
	FLTYPE s = sin(_angle);
	FLTYPE cx = c * p.x() - s * p.y();
	p.y() = s * p.x() + c * p.y();
	p.x() = cx;
	return p;
}
