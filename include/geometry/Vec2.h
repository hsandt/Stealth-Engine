#pragma once

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iosfwd>

#include "utils/infix_iterator.h"

template<class FLTYPE>
struct Vec2
{
	FLTYPE coords[2] = {0, 0};

	Vec2<FLTYPE>() {}

	Vec2<FLTYPE>(const FLTYPE nx, const FLTYPE ny)
	{
		coords[0] = nx;
		coords[1] = ny;
	}

	Vec2<FLTYPE>(Vec2<FLTYPE> const &v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
	}

	Vec2<FLTYPE> &operator=(Vec2<FLTYPE> const &v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
		return *this;
	}

	/* Conversion functions */

#ifdef BOX2D_H
	Vec2<FLTYPE>(b2Vec2 const &b2V)
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
	Vec2<FLTYPE> operator+(Vec2<FLTYPE> const &v) const
	{
		return Vec2<FLTYPE>(coords[0] + v.coords[0], coords[1] + v.coords[1]);
	}

	Vec2<FLTYPE> operator-(Vec2<FLTYPE> const &v) const
	{
		return Vec2<FLTYPE>(coords[0] - v.coords[0], coords[1] - v.coords[1]);
	}

	Vec2<FLTYPE> operator*(const FLTYPE s) const
	{
		return Vec2<FLTYPE>(coords[0] * s, coords[1] * s);
	}

	Vec2<FLTYPE> operator/(const FLTYPE s) const
	{
		return Vec2<FLTYPE>(coords[0] / s, coords[1] / s);
	}

	/// Scalar product
	FLTYPE operator*(Vec2<FLTYPE> const &v) const
	{
		return (coords[0] * v.coords[0] + coords[1] * v.coords[1]);
	}

	// Element-wise in-place operations
	Vec2<FLTYPE> &operator+=(Vec2<FLTYPE> const &v)
	{
		coords[0] += v.coords[0];
		coords[1] += v.coords[1];
		return *this;
	}

	Vec2<FLTYPE> &operator-=(Vec2<FLTYPE> const &v)
	{
		coords[0] -= v.coords[0];
		coords[1] -= v.coords[1];
		return *this;
	}

	Vec2<FLTYPE> &operator*=(const FLTYPE s)
	{
		coords[0] *= s;
		coords[1] *= s;
		return *this;
	}

	Vec2<FLTYPE> &operator/=(const FLTYPE s)
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

	Vec2<FLTYPE> &Normalize()
	{
		FLTYPE n = Length();
		if (n > 0) {
			coords[0] /= n;
			coords[1] /= n;
		}
		return *this;
	}

	bool operator==(Vec2<FLTYPE> const &v) const
	{
		return coords[0] == v.coords[0] && coords[1] == v.coords[1];
	}

	bool operator!=(Vec2<FLTYPE> const &v) const
	{
		return !(coords == v.coords);
	}

	// Comparisons with higher priority on higher index values (not used)
//    bool operator <(Vec2<FLTYPE> const & p) const {
//        return	(v[2] != p.v[2]) ? (v[2] < p.v[2]):
//                (v[1] != p.v[1]) ? (v[1 ]< p.v[1]):
//                        (v[0] < p.v[0]);
//    }
//    bool operator >(Vec2<FLTYPE> const & p) const {
//        return	(v[2] != p.v[2]) ? (v[2] > p.v[2]):
//                (v[1] != p.v[1]) ? (v[1] > p.v[1]):
//                        (v[0] > p.v[0]);
//    }
//
//    bool operator <=(Vec2<FLTYPE> const & p) const {
//        return	(v[2] != p.v[2])?(v[2] < p.v[2]):
//                (v[1] != p.v[1])?(v[1] < p.v[1]):
//                        (v[0] <= p.v[0]);
//    }
//
//    bool operator >=(Vec2<FLTYPE> const & p ) const {
//        return	(v[2] != p.v[2]) ? (v[2] > p.v[2]):
//                (v[1] != p.v[1]) ? (v[1] > p.v[1]):
//                        (v[0] >= p.v[0]);
//    }

	/// Return the distance with another vector
	FLTYPE Distance(Vec2<FLTYPE> const &v) const
	{
		return (*this - v).Length();
	}

	/// Return the squared distance with another vector
	FLTYPE SquaredDistance(Vec2<FLTYPE> const &v) const
	{
		return (*this - v).LengthSquared();
	}

}; // end class definition

// To string
template<class FLTYPE>
inline std::ostream& operator<<(std::ostream &stream, const Vec2<FLTYPE> &v)
{
	stream << "Vec2(";
	std::copy(v.coords, v.coords + 2, infix_ostream_iterator<FLTYPE>(stream, ", "));
	return stream << ")";
}

template<class FLTYPE>
inline FLTYPE Angle(Vec2<FLTYPE> const &p1, Vec2<FLTYPE> const &p2)
{
	return (FLTYPE) acos((p1 * p2) / (p1.Length() * p2.Length()));
}

template<class FLTYPE>
inline Vec2<FLTYPE> operator-(Vec2<FLTYPE> const &p)
{
	return Vec2<FLTYPE>(-p.coords[0], -p.coords[1]);
}

template<class FLTYPE>
inline Vec2<FLTYPE> operator*(const FLTYPE s, Vec2<FLTYPE> const &p)
{
	return Vec2<FLTYPE>(p.coords[0] * s, p.coords[1] * s);
}

template<class FLTYPE>
inline FLTYPE Length(Vec2<FLTYPE> const &p)
{
	return sqrt(p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1]);
}

template<class FLTYPE>
inline FLTYPE LengthSquared(Vec2<FLTYPE> const &p)
{
	return (p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1]);
}

template<class FLTYPE>
inline Vec2<FLTYPE> &Normalize(Vec2<FLTYPE> &p)
{
	FLTYPE n = Length(p);
	if (n > 0.0) p /= n;
	return p;
}

template<class FLTYPE>
inline FLTYPE Distance(Vec2<FLTYPE> const &p1, Vec2<FLTYPE> const &p2)
{
	return Length(p1 - p2);
}

template<class FLTYPE>
inline Vec2<FLTYPE> &RotateZ(Vec2<FLTYPE> &p, FLTYPE _angle)
{
	FLTYPE c = cos(_angle);
	FLTYPE s = sin(_angle);
	FLTYPE cx = c * p.x() - s * p.y();
	p.y() = s * p.x() + c * p.y();
	p.x() = cx;
	return p;
}

/* Specific type shortcuts */

typedef Vec2<short> Vec2s;
typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
