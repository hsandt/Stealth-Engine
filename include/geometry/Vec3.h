#pragma once

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iosfwd>

#include "utils/infix_iterator.h"

template<class FLTYPE>
class Vec3
{
public:
	FLTYPE coords[3] = {0, 0, 0};

	Vec3<FLTYPE>() {}

	Vec3<FLTYPE>(const FLTYPE nx, const FLTYPE ny, const FLTYPE nz)
	{
		coords[0] = nx;
		coords[1] = ny;
		coords[2] = nz;
	}

	Vec3<FLTYPE>(Vec3<FLTYPE> const &v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
		coords[2] = v.coords[2];
	}

	Vec3<FLTYPE> &operator=(Vec3<FLTYPE> const &v)
	{
		coords[0] = v.coords[0];
		coords[1] = v.coords[1];
		coords[2] = v.coords[2];
		return *this;
	}

	// Coordinate reference getter
	FLTYPE &x() { return coords[0]; };

	FLTYPE &y() { return coords[1]; };

	FLTYPE &z() { return coords[2]; };

	// Index getter
	FLTYPE &operator[](const int i)
	{
		assert(i >= 0 && i < 3);
		return coords[i];
	}

	// Index getter const
	const FLTYPE &operator[](const int i) const
	{
		assert(i >= 0 && i < 3);
		return coords[i];
	}

	// Element-wise operations
	Vec3<FLTYPE> operator+(Vec3<FLTYPE> const &v) const
	{
		return Vec3<FLTYPE>(coords[0] + v.coords[0], coords[1] + v.coords[1], coords[2] + v.coords[2]);
	}

	Vec3<FLTYPE> operator-(Vec3<FLTYPE> const &v) const
	{
		return Vec3<FLTYPE>(coords[0] - v.coords[0], coords[1] - v.coords[1], coords[2] - v.coords[2]);
	}

	Vec3<FLTYPE> operator*(const FLTYPE s) const
	{
		return Vec3<FLTYPE>(coords[0] * s, coords[1] * s, coords[2] * s);
	}

	Vec3<FLTYPE> operator/(const FLTYPE s) const
	{
		return Vec3<FLTYPE>(coords[0] / s, coords[1] / s, coords[2] / s);
	}

	/// Scalar product
	FLTYPE operator*(Vec3<FLTYPE> const &v) const
	{
		return (coords[0] * v.coords[0] + coords[1] * v.coords[1] + coords[2] * v.coords[2]);
	}

	/// Cross product
	Vec3<FLTYPE> operator^(Vec3<FLTYPE> const &v) const
	{
		return Vec3<FLTYPE>(
				coords[1] * v.coords[2] - coords[2] * v.coords[1],
				coords[2] * v.coords[0] - coords[0] * v.coords[2],
				coords[0] * v.coords[1] - coords[1] * v.coords[0]
		);
	}

	// Element-wise in-place operations
	Vec3<FLTYPE> &operator+=(Vec3<FLTYPE> const &v)
	{
		coords[0] += v.coords[0];
		coords[1] += v.coords[1];
		coords[2] += v.coords[2];
		return *this;
	}

	Vec3<FLTYPE> &operator-=(Vec3<FLTYPE> const &v)
	{
		coords[0] -= v.coords[0];
		coords[1] -= v.coords[1];
		coords[2] -= v.coords[2];
		return *this;
	}

	Vec3<FLTYPE> &operator*=(const FLTYPE s)
	{
		coords[0] *= s;
		coords[1] *= s;
		coords[2] *= s;
		return *this;
	}

	Vec3<FLTYPE> &operator/=(const FLTYPE s)
	{
		coords[0] /= s;
		coords[1] /= s;
		coords[2] /= s;
		return *this;
	}

	/// Return norm
	FLTYPE Length() const
	{
		return (FLTYPE) sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]);
	}

	/// Return squared norm
	FLTYPE LengthSquared() const
	{
		return coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2];
	}

	Vec3<FLTYPE> &Normalize()
	{
		FLTYPE n = Length();
		if (n > 0) {
			coords[0] /= n;
			coords[1] /= n;
			coords[2] /= n;
		}
		return *this;
	}

	bool operator==(Vec3<FLTYPE> const &v) const
	{
		return coords[0] == v.coords[0] && coords[1] == v.coords[1] && coords[2] == v.coords[2];
	}

	bool operator!=(Vec3<FLTYPE> const &v) const
	{
		return !(coords == v.coords);
	}

	// Comparisons with higher priority on higher index values (not used)
//    bool operator <(Vec3<FLTYPE> const & p) const {
//        return	(v[2] != p.v[2]) ? (v[2] < p.v[2]):
//                (v[1] != p.v[1]) ? (v[1 ]< p.v[1]):
//                        (v[0] < p.v[0]);
//    }
//    bool operator >(Vec3<FLTYPE> const & p) const {
//        return	(v[2] != p.v[2]) ? (v[2] > p.v[2]):
//                (v[1] != p.v[1]) ? (v[1] > p.v[1]):
//                        (v[0] > p.v[0]);
//    }
//
//    bool operator <=(Vec3<FLTYPE> const & p) const {
//        return	(v[2] != p.v[2])?(v[2] < p.v[2]):
//                (v[1] != p.v[1])?(v[1] < p.v[1]):
//                        (v[0] <= p.v[0]);
//    }
//
//    bool operator >=(Vec3<FLTYPE> const & p ) const {
//        return	(v[2] != p.v[2]) ? (v[2] > p.v[2]):
//                (v[1] != p.v[1]) ? (v[1] > p.v[1]):
//                        (v[0] >= p.v[0]);
//    }

	/// Return the distance with another vector
	FLTYPE Distance(Vec3<FLTYPE> const &v) const
	{
		return (*this - v).Length();
	}

	/// Return the squared distance with another vector
	FLTYPE SquaredDistance(Vec3<FLTYPE> const &v) const
	{
		return (*this - v).LengthSquared();
	}

}; // end class definition

// To string
template<class FLTYPE>
std::ostream& operator<<(std::ostream &stream, const Vec3<FLTYPE> &v)
{
	stream << "Vec3(";
	std::copy(v.coords, v.coords + 3, infix_ostream_iterator<FLTYPE>(stream, ", "));
	return stream << ")";
}

template<class FLTYPE>
FLTYPE Angle(Vec3<FLTYPE> const &p1, Vec3<FLTYPE> const &p2)
{
	return (FLTYPE) acos((p1 * p2) / (p1.Length() * p2.Length()));
}

template<class FLTYPE>
Vec3<FLTYPE> operator-(Vec3<FLTYPE> const &p)
{
	return Vec3<FLTYPE>(-p.coords[0], -p.coords[1], -p.coords[2]);
}

template<class FLTYPE>
Vec3<FLTYPE> operator*(const FLTYPE s, Vec3<FLTYPE> const &p)
{
	return Vec3<FLTYPE>(p.coords[0] * s, p.coords[1] * s, p.coords[2] * s);
}

template<class FLTYPE>
FLTYPE Length(Vec3<FLTYPE> const &p)
{
	return sqrt(p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1] + p.coords[2] * p.coords[2]);
}

template<class FLTYPE>
FLTYPE LengthSquared(Vec3<FLTYPE> const &p)
{
	return (p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1] + p.coords[2] * p.coords[2]);
}

template<class FLTYPE>
Vec3<FLTYPE> &Normalize(Vec3<FLTYPE> &p)
{
	FLTYPE n = Length(p);
	if (n > 0.0) p /= n;
	return p;
}

template<class FLTYPE>
FLTYPE Distance(Vec3<FLTYPE> const &p1, Vec3<FLTYPE> const &p2)
{
	return Length(p1 - p2);
}

template<class FLTYPE>
Vec3<FLTYPE> &RotateZ(Vec3<FLTYPE> &p, FLTYPE _angle)
{
	FLTYPE c = cos(_angle);
	FLTYPE s = sin(_angle);
	FLTYPE cx = c * p.x() - s * p.y();
	p.y() = s * p.x() + c * p.y();
	p.x() = cx;
	return p;
}

typedef Vec3<short> Vec3s;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

#ifdef __GL_H__
void glVertex(Vec3<int> const & v)   { glVertex3iv(v.coords);};
void glVertex(Vec3<short> const & v) { glVertex3sv(v.coords);};
void glVertex(Vec3<float> const & v) { glVertex3fv(v.coords);};
void glVertex(Vec3<double> const & v){ glVertex3dv(v.coords);};
void glNormal(Vec3<int> const & v)   { glNormal3iv(v.coords);};
void glNormal(Vec3<short> const & v) { glNormal3sv(v.coords);};
void glNormal(Vec3<float> const & v) { glNormal3fv(v.coords);};
void glNormal(Vec3<double> const & v){ glNormal3dv(v.coords);};
void glTexCoord(Vec3<int> const & v)   { glTexCoord3iv(v.coords);};
void glTexCoord(Vec3<short> const & v) { glTexCoord3sv(v.coords);};
void glTexCoord(Vec3<float> const & v) { glTexCoord3fv(v.coords);};
void glTexCoord(Vec3<double> const & v){ glTexCoord3dv(v.coords);};
void glTranslate(Vec3<float> const & v) { glTranslatef(v.coords[0],v.coords[1],v.coords[2]);};
void glTranslate(Vec3<double> const & v){ glTranslated(v.coords[0],v.coords[1],v.coords[2]);};
void glScale(Vec3<float> const & v) { glScalef(v.coords[0],v.coords[1],v.coords[2]);};
void glScale(Vec3<double> const & v){ glScaled(v.coords[0],v.coords[1],v.coords[2]);};
#endif
