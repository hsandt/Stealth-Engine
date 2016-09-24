#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iosfwd>

#include "utils/infix_iterator.h"

#include "geometry/Vec3.h"

template<typename FLTYPE>
Vec3<FLTYPE> Vec3<FLTYPE>::operator+(Vec3<FLTYPE> const &v) const
{
	return Vec3<FLTYPE>(coords[0] + v.coords[0], coords[1] + v.coords[1], coords[2] + v.coords[2]);
}

template<typename FLTYPE>
Vec3<FLTYPE> Vec3<FLTYPE>::operator-(const Vec3<FLTYPE> &v) const {
    return Vec3<FLTYPE>(coords[0] - v.coords[0], coords[1] - v.coords[1], coords[2] - v.coords[2]);
}

template<typename FLTYPE>
Vec3<FLTYPE> Vec3<FLTYPE>::operator*(const FLTYPE s) const {
    return Vec3<FLTYPE>(coords[0] * s, coords[1] * s, coords[2] * s);
}

template<typename FLTYPE>
Vec3<FLTYPE> Vec3<FLTYPE>::operator/(const FLTYPE s) const {
    return Vec3<FLTYPE>(coords[0] / s, coords[1] / s, coords[2] / s);
}

template<typename FLTYPE>
Vec3<FLTYPE> Vec3<FLTYPE>::operator^(const Vec3<FLTYPE> &v) const {
    return Vec3<FLTYPE>(
            coords[1] * v.coords[2] - coords[2] * v.coords[1],
            coords[2] * v.coords[0] - coords[0] * v.coords[2],
            coords[0] * v.coords[1] - coords[1] * v.coords[0]
    );
}

template<typename FLTYPE>
Vec3<FLTYPE> &Vec3<FLTYPE>::operator+=(const Vec3<FLTYPE> &v) {
    coords[0] += v.coords[0];
    coords[1] += v.coords[1];
    coords[2] += v.coords[2];
    return *this;
}

template<typename FLTYPE>
Vec3<FLTYPE> &Vec3<FLTYPE>::operator-=(const Vec3<FLTYPE> &v) {
    coords[0] -= v.coords[0];
    coords[1] -= v.coords[1];
    coords[2] -= v.coords[2];
    return *this;
}

template<typename FLTYPE>
Vec3<FLTYPE> &Vec3<FLTYPE>::operator*=(const FLTYPE s) {
    coords[0] *= s;
    coords[1] *= s;
    coords[2] *= s;
    return *this;
}

template<typename FLTYPE>
Vec3<FLTYPE> &Vec3<FLTYPE>::operator/=(const FLTYPE s) {
    coords[0] /= s;
    coords[1] /= s;
    coords[2] /= s;
    return *this;
}

template<typename FLTYPE>
FLTYPE Vec3<FLTYPE>::Length() const {
    return (FLTYPE) sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]);
}

template<typename FLTYPE>
FLTYPE Vec3<FLTYPE>::LengthSquared() const {
    return coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2];
}

template<typename FLTYPE>
Vec3<FLTYPE> &Vec3<FLTYPE>::Normalize() {
    FLTYPE n = Length();
    if (n > 0) {
        coords[0] /= n;
        coords[1] /= n;
        coords[2] /= n;
    }
    return *this;
}

template<typename FLTYPE>
bool Vec3<FLTYPE>::operator==(const Vec3<FLTYPE> &v) const {
    return coords[0] == v.coords[0] && coords[1] == v.coords[1] && coords[2] == v.coords[2];
}

template<typename FLTYPE>
bool Vec3<FLTYPE>::operator!=(const Vec3<FLTYPE> &v) const {
    return !(coords == v.coords);
}

template<typename FLTYPE>
FLTYPE Vec3<FLTYPE>::Distance(const Vec3<FLTYPE> &v) const {
    return (*this - v).Length();
}

template<typename FLTYPE>
FLTYPE Vec3<FLTYPE>::SquaredDistance(const Vec3<FLTYPE> &v) const {
    return (*this - v).LengthSquared();
}

template<typename FLTYPE>
FLTYPE Vec3<FLTYPE>::operator*(const Vec3<FLTYPE> &v) const {
    return (coords[0] * v.coords[0] + coords[1] * v.coords[1] + coords[2] * v.coords[2]);
}

template<class FLTYPE>
std::ostream &operator<<(std::ostream &stream, const Vec3<FLTYPE> &v) {
    stream << "Vec3(";
    std::copy(v.coords, v.coords + 3, infix_ostream_iterator<FLTYPE>(stream, ", "));
    return stream << ")";
}

template<class FLTYPE>
FLTYPE Angle(Vec3<FLTYPE> const &p1, Vec3<FLTYPE> const &p2) {
    return (FLTYPE) acos((p1 * p2) / (p1.Length() * p2.Length()));
}

template<class FLTYPE>
Vec3<FLTYPE> operator-(Vec3<FLTYPE> const &p) {
    return Vec3<FLTYPE>(-p.coords[0], -p.coords[1], -p.coords[2]);
}

template<class FLTYPE>
Vec3<FLTYPE> operator*(const FLTYPE s, Vec3<FLTYPE> const &p) {
    return Vec3<FLTYPE>(p.coords[0] * s, p.coords[1] * s, p.coords[2] * s);
}

template<class FLTYPE>
Vec3<FLTYPE> operator*(Vec3<FLTYPE> const &p, const FLTYPE s) {
    return s * p;
}

template<class FLTYPE>
FLTYPE Length(Vec3<FLTYPE> const &p) {
    return sqrt(p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1] + p.coords[2] * p.coords[2]);
}

template<class FLTYPE>
FLTYPE LengthSquared(Vec3<FLTYPE> const &p) {
    return (p.coords[0] * p.coords[0] + p.coords[1] * p.coords[1] + p.coords[2] * p.coords[2]);
}

template<class FLTYPE>
Vec3<FLTYPE> &Normalize(Vec3<FLTYPE> &p) {
    FLTYPE n = Length(p);
    if (n > 0.0) p /= n;
    return p;
}

template<class FLTYPE>
FLTYPE Distance(Vec3<FLTYPE> const &p1, Vec3<FLTYPE> const &p2) {
    return Length(p1 - p2);
}

template<class FLTYPE>
Vec3<FLTYPE> &RotateZ(Vec3<FLTYPE> &p, FLTYPE _angle) {
    FLTYPE c = cos(_angle);
    FLTYPE s = sin(_angle);
    FLTYPE cx = c * p.x() - s * p.y();
    p.y() = s * p.x() + c * p.y();
    p.x() = cx;
    return p;
}

