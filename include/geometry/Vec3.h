#pragma once

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iosfwd>
#include <GL/glew.h>

#include "utils/infix_iterator.h"

// REFACTOR: put definitions in cpp to avoid multiple definition
// (despite header guard, since we have different compilation units)

template<typename FLTYPE>
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
	Vec3<FLTYPE> operator+(Vec3<FLTYPE> const &v) const;

	Vec3<FLTYPE> operator-(Vec3<FLTYPE> const &v) const;

	Vec3<FLTYPE> operator*(const FLTYPE s) const;

	Vec3<FLTYPE> operator/(const FLTYPE s) const;

	/// Scalar product
	FLTYPE operator*(Vec3<FLTYPE> const &v) const;

	/// Cross product
	Vec3<FLTYPE> operator^(Vec3<FLTYPE> const &v) const;

	// Element-wise in-place operations
	Vec3<FLTYPE> &operator+=(Vec3<FLTYPE> const &v);

	Vec3<FLTYPE> &operator-=(Vec3<FLTYPE> const &v);

	Vec3<FLTYPE> &operator*=(const FLTYPE s);

	Vec3<FLTYPE> &operator/=(const FLTYPE s);

	/// Return norm
	FLTYPE Length() const;

	/// Return squared norm
	FLTYPE LengthSquared() const;

	Vec3<FLTYPE> &Normalize();

	bool operator==(Vec3<FLTYPE> const &v) const;

	bool operator!=(Vec3<FLTYPE> const &v) const;

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
	FLTYPE Distance(Vec3<FLTYPE> const &v) const;

	/// Return the squared distance with another vector
	FLTYPE SquaredDistance(Vec3<FLTYPE> const &v) const;

}; // end class definition

// To string
template<class FLTYPE>
std::ostream& operator<<(std::ostream &stream, const Vec3<FLTYPE> &v);



template<class FLTYPE>
FLTYPE Angle(Vec3<FLTYPE> const &p1, Vec3<FLTYPE> const &p2);

template<class FLTYPE>
Vec3<FLTYPE> operator-(Vec3<FLTYPE> const &p);

template<class FLTYPE>
Vec3<FLTYPE> operator*(const FLTYPE s, Vec3<FLTYPE> const &p);

template<class FLTYPE>
Vec3<FLTYPE> operator*(Vec3<FLTYPE> const &p, const FLTYPE s);

template<class FLTYPE>
FLTYPE Length(Vec3<FLTYPE> const &p);

template<class FLTYPE>
FLTYPE LengthSquared(Vec3<FLTYPE> const &p);

template<class FLTYPE>
Vec3<FLTYPE> &Normalize(Vec3<FLTYPE> &p);

template<class FLTYPE>
FLTYPE Distance(Vec3<FLTYPE> const &p1, Vec3<FLTYPE> const &p2);

template<class FLTYPE>
Vec3<FLTYPE> &RotateZ(Vec3<FLTYPE> &p, FLTYPE _angle);



typedef Vec3<short> Vec3s;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

inline void glVertex(Vec3<int> const &v) { glVertex3iv(v.coords);}
inline void glVertex(Vec3<short> const &v) { glVertex3sv(v.coords);}
inline void glVertex(Vec3<float> const &v) { glVertex3fv(v.coords);}
inline void glVertex(Vec3<double> const &v) { glVertex3dv(v.coords);}
inline void glNormal(Vec3<int> const &v) { glNormal3iv(v.coords);}
inline void glNormal(Vec3<short> const &v) { glNormal3sv(v.coords);}
inline void glNormal(Vec3<float> const & v) { glNormal3fv(v.coords);}
inline void glNormal(Vec3<double> const & v){ glNormal3dv(v.coords);}
inline void glTexCoord(Vec3<int> const & v)   { glTexCoord3iv(v.coords);}
inline void glTexCoord(Vec3<short> const & v) { glTexCoord3sv(v.coords);}
inline void glTexCoord(Vec3<float> const & v) { glTexCoord3fv(v.coords);}
inline void glTexCoord(Vec3<double> const & v){ glTexCoord3dv(v.coords);}
inline void glTranslate(Vec3<float> const & v) { glTranslatef(v.coords[0],v.coords[1],v.coords[2]);}
inline void glTranslate(Vec3<double> const & v){ glTranslated(v.coords[0],v.coords[1],v.coords[2]);}
inline void glScale(Vec3<float> const & v) { glScalef(v.coords[0],v.coords[1],v.coords[2]);}
inline void glScale(Vec3<double> const & v){ glScaled(v.coords[0],v.coords[1],v.coords[2]);}
