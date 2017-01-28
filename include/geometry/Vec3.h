#pragma once

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iosfwd>

#include "utils/infix_iterator.h"

class Vector3
{
public:
	float coords[3] = {0, 0, 0};

	Vector3() {}

	Vector3(const float nx, const float ny, const float nz)
	{
		coords[0] = nx;
		coords[1] = ny;
		coords[2] = nz;
	}

	Vector3(Vector3 const &v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
		coords[2] = v.coords[2];
	}

	Vector3 &operator=(Vector3 const &v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
		coords[2] = v.coords[2];
		return *this;
	}

	// Coordinate reference getter
	float &x() { return coords[0]; };

	float &y() { return coords[1]; };

	float &z() { return coords[2]; };

	// Index getter
	inline float &operator[](const int i)
	{
		assert(i >= 0 && i < 3);
		return coords[i];
	}

	// Index getter const
	inline const float &operator[](const int i) const
	{
		assert(i >= 0 && i < 3);
		return coords[i];
	}

	// Element-wise operations
	inline Vector3 operator+(Vector3 const &v) const
	{
		return Vector3(coords[0] + v.coords[0], coords[1] + v.coords[1], coords[2] + v.coords[2]);
	}

	inline Vector3 operator-(Vector3 const &v) const
	{
		return Vector3(coords[0] - v.coords[0], coords[1] - v.coords[1], coords[2] - v.coords[2]);
	}

	inline Vector3 operator*(const float s) const
	{
		return Vector3(coords[0] * s, coords[1] * s, coords[2] * s);
	}

	inline Vector3 operator/(const float s) const
	{
		return Vector3(coords[0] / s, coords[1] / s, coords[2] / s);
	}

	/// Scalar product
	inline float operator*(Vector3 const &v) const
	{
		return (coords[0] * v.coords[0] + coords[1] * v.coords[1] + coords[2] * v.coords[2]);
	}

	/// Cross product
	inline Vector3 operator^(Vector3 const &v) const
	{
		return Vector3(
				coords[1] * v.coords[2] - coords[2] * v.coords[1],
				coords[2] * v.coords[0] - coords[0] * v.coords[2],
				coords[0] * v.coords[1] - coords[1] * v.coords[0]
		);
	}

	// Element-wise in-place operations
	inline Vector3 &operator+=(Vector3 const &v)
	{
		coords[0] += v.coords[0];
		coords[1] += v.coords[1];
		coords[2] += v.coords[2];
		return *this;
	}

	inline Vector3 &operator-=(Vector3 const &v)
	{
		coords[0] -= v.coords[0];
		coords[1] -= v.coords[1];
		coords[2] -= v.coords[2];
		return *this;
	}

	inline Vector3 &operator*=(const float s)
	{
		coords[0] *= s;
		coords[1] *= s;
		coords[2] *= s;
		return *this;
	}

	inline Vector3 &operator/=(const float s)
	{
		coords[0] /= s;
		coords[1] /= s;
		coords[2] /= s;
		return *this;
	}

	/// Return norm
	inline float Length() const
	{
		return (float) sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]);
	}

	/// Return squared norm
	inline float LengthSquared() const
	{
		return coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2];
	}

	inline Vector3 &Normalize()
	{
		float n = Length();
		if (n > 0) {
			coords[0] /= n;
			coords[1] /= n;
			coords[2] /= n;
		}
		return *this;
	}

	inline bool operator==(Vector3 const &v) const
	{
		return coords[0] == v.coords[0] && coords[1] == v.coords[1] && coords[2] == v.coords[2];
	}

	inline bool operator!=(Vector3 const &v) const
	{
		return !(coords == v.coords);
	}

	// Comparisons with higher priority on higher index values (not used)
//    inline bool operator <(Vector3 const & p) const {
//        return	(v[2] != p.v[2]) ? (v[2] < p.v[2]):
//                (v[1] != p.v[1]) ? (v[1 ]< p.v[1]):
//                        (v[0] < p.v[0]);
//    }
//    inline bool operator >(Vector3 const & p) const {
//        return	(v[2] != p.v[2]) ? (v[2] > p.v[2]):
//                (v[1] != p.v[1]) ? (v[1] > p.v[1]):
//                        (v[0] > p.v[0]);
//    }
//
//    inline bool operator <=(Vector3 const & p) const {
//        return	(v[2] != p.v[2])?(v[2] < p.v[2]):
//                (v[1] != p.v[1])?(v[1] < p.v[1]):
//                        (v[0] <= p.v[0]);
//    }
//
//    inline bool operator >=(Vector3 const & p ) const {
//        return	(v[2] != p.v[2]) ? (v[2] > p.v[2]):
//                (v[1] != p.v[1]) ? (v[1] > p.v[1]):
//                        (v[0] >= p.v[0]);
//    }

	/// Return the distance with another vector
	inline float Distance(Vector3 const &v) const
	{
		return (*this - v).Length();
	}

	/// Return the squared distance with another vector
	inline float SquaredDistance(Vector3 const &v) const
	{
		return (*this - v).LengthSquared();
	}

}; // end class definition

// To string
inline std::ostream& operator<<(std::ostream &stream, const Vector3 &v)
{
	stream << "Vector3(";
	std::copy(v.coords, v.coords + 3, infix_ostream_iterator<float>(stream, ", "));
	return stream << ")";
}

inline float Angle(Vector3 const &p1, Vector3 const &p2)
{
	return (float) acos((p1 * p2) / (p1.Length() * p2.Length()));
}

inline Vector3 operator-(Vector3 const &p)
{
	return Vector3(-p.coords[0], -p.coords[1], -p.coords[2]);
}

inline Vector3 operator*(const float s, Vector3 const &p)
{
	return Vector3(p.coords[0] * s, p.coords[1] * s, p.coords[2] * s);
}

inline float Length(Vector3 const &p)
{
	return sqrt(p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1] + p.coords[2] * p.coords[2]);
}

inline float LengthSquared(Vector3 const &p)
{
	return (p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1] + p.coords[2] * p.coords[2]);
}

inline Vector3 &Normalize(Vector3 &p)
{
	float n = Length(p);
	if (n > 0.0) p /= n;
	return p;
}

inline float Distance(Vector3 const &p1, Vector3 const &p2)
{
	return Length(p1 - p2);
}

inline Vector3 &RotateZ(Vector3 &p, float _angle)
{
	float c = (float) cos(_angle);
	float s = (float) sin(_angle);
	float cx = c * p.x() - s * p.y();
	p.y() = s * p.x() + c * p.y();
	p.x() = cx;
	return p;
}

void glVertex(Vector3 const &v);
void glNormal(Vector3 const & v);
void glTexCoord(Vector3 const & v);
void glTranslate(Vector3 const & v);
void glScale(Vector3 const & v);
