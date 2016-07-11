#pragma once

#include <assert.h>
#include <cmath>

template <class FLTYPE> class Vec3
{
private:
public:

	FLTYPE v[3];

	Vec3<FLTYPE> ( void ) { }

	// Coordinate reference getter
    FLTYPE &x() { return v[0]; };
    FLTYPE &y() { return v[1]; };
    FLTYPE &z() { return v[2]; };

    // Index getter
    inline FLTYPE & operator [] (const int i)
    {
        assert(i>=0 && i<3);
        return v[i];
    }
	// Index getter const
    inline const FLTYPE & operator [] (const int i) const {
        assert(i>=0 && i<3);
        return v[i];
    }

    // FIXME: an inline constructor with nothing
    // is likely to initialize with garbage values
    inline Vec3<FLTYPE> ( const FLTYPE nx, const FLTYPE ny, const FLTYPE nz ){
        v[0] = nx; v[1] = ny; v[2] = nz;
    }
    inline Vec3<FLTYPE> ( Vec3<FLTYPE> const & p)  {
        v[0]= p.v[0];    v[1]= p.v[1];    v[2]= p.v[2];
    }
    inline Vec3<FLTYPE> & operator =( Vec3<FLTYPE> const & p){
        v[0]= p.v[0]; v[1]= p.v[1]; v[2]= p.v[2];
        return *this;
    }
    inline Vec3<FLTYPE> operator + ( Vec3<FLTYPE> const & p) const {
        return Vec3<FLTYPE>( v[0]+p.v[0], v[1]+p.v[1], v[2]+p.v[2] );
    }
    inline Vec3<FLTYPE> operator - ( Vec3<FLTYPE> const & p) const {
        return Vec3<FLTYPE>( v[0]-p.v[0], v[1]-p.v[1], v[2]-p.v[2] );
    }
    inline Vec3<FLTYPE> operator * ( const FLTYPE s ) const {
        return Vec3<FLTYPE>( v[0] * s, v[1] * s, v[2] * s );
    }
    inline Vec3<FLTYPE> operator / ( const FLTYPE s ) const {
        return Vec3<FLTYPE>( v[0] / s, v[1] / s, v[2] / s );
    }
    inline FLTYPE operator * ( Vec3<FLTYPE> const & p ) const {
        return ( v[0]*p.v[0] + v[1]*p.v[1] + v[2]*p.v[2] );
    }
    inline Vec3<FLTYPE> operator ^ ( Vec3<FLTYPE> const & p ) const {
        return Vec3<FLTYPE>(
                v[1]*p.v[2] - v[2]*p.v[1],
                v[2]*p.v[0] - v[0]*p.v[2],
                v[0]*p.v[1] - v[1]*p.v[0]
        );
    }
    inline Vec3<FLTYPE> & operator += ( Vec3<FLTYPE> const & p){
        v[0] += p.v[0];    v[1] += p.v[1];     v[2] += p.v[2];
        return *this;
    }
    inline Vec3<FLTYPE> & operator -= ( Vec3<FLTYPE> const & p){
        v[0] -= p.v[0];    v[1] -= p.v[1];     v[2] -= p.v[2];
        return *this;
    }
    inline Vec3<FLTYPE> & operator *= ( const FLTYPE s ){
        v[0] *= s;    v[1] *= s;    v[2] *= s;
        return *this;
    }
    inline Vec3<FLTYPE> & operator /= ( const FLTYPE s ){
        v[0] /= s;    v[1] /= s;    v[2] /= s;
        return *this;
    }
    inline FLTYPE Length( void ) const {
        return (FLTYPE)(sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] ));
    }
    inline FLTYPE LengthSquared( void ) const{
        return ( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    }
    inline Vec3<FLTYPE> & Scale( const FLTYPE sx, const FLTYPE sy, const FLTYPE sz );

    inline Vec3<FLTYPE> & Normalize( void ){
        FLTYPE n = (FLTYPE)(sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
        if(n>0.0) {	v[0] /= n;	v[1] /= n;	v[2] /= n;  }
        return *this;
    }
    inline bool operator == ( Vec3<FLTYPE> const & p ) const {
        return (v[0]==p.v[0] && v[1]==p.v[1] && v[2]==p.v[2]);
    }
    inline bool operator != ( Vec3<FLTYPE> const & p ) const {
        return ( (v[0]!=p.v[0]) || (v[1]!=p.v[1]) || (v[2]!=p.v[2]));
    }
    inline bool operator <  ( Vec3<FLTYPE> const & p ) const {
        return	(v[2]!=p.v[2])?(v[2]<p.v[2]):
                (v[1]!=p.v[1])?(v[1]<p.v[1]):
                        (v[0]<p.v[0]);
    }
    inline bool operator >  ( Vec3<FLTYPE> const & p ) const {
        return	(v[2]!=p.v[2])?(v[2]>p.v[2]):
                (v[1]!=p.v[1])?(v[1]>p.v[1]):
                        (v[0]>p.v[0]);
    }

    inline bool operator <= ( Vec3<FLTYPE> const & p ) const {
        return	(v[2]!=p.v[2])?(v[2]< p.v[2]):
                (v[1]!=p.v[1])?(v[1]< p.v[1]):
                        (v[0]<=p.v[0]);
    }

    inline bool operator >= ( Vec3<FLTYPE> const & p ) const {
        return	(v[2]!=p.v[2])?(v[2]> p.v[2]):
                (v[1]!=p.v[1])?(v[1]> p.v[1]):
                        (v[0]>=p.v[0]);
    }
    inline FLTYPE Distance( Vec3<FLTYPE> const & p ) const{
        return (*this-p).Length();
    }

    inline FLTYPE SquaredDistance( Vec3<FLTYPE> const & p ) const {
        return (*this-p).LengthSquared();
    }

}; // end class definition


template <class FLTYPE>
inline FLTYPE Angle( Vec3<FLTYPE> const & p1, Vec3<FLTYPE> const & p2 ){
    return (FLTYPE) acos( (p1*p2)/(p1.Length()*p2.Length()) );
}

template <class FLTYPE>
inline Vec3<FLTYPE> operator - ( Vec3<FLTYPE> const & p ){
    return Vec3<FLTYPE>( -p.v[0], -p.v[1], -p.v[2] );
}

template <class FLTYPE>
inline Vec3<FLTYPE> operator * ( const FLTYPE s, Vec3<FLTYPE> const & p ){
    return Vec3<FLTYPE>( p.v[0] * s, p.v[1] * s, p.v[2] * s );
}

template <class FLTYPE>
inline FLTYPE Length( Vec3<FLTYPE> const & p ){
    return sqrt( p.v[0]*p.v[0] + p.v[1]*p.v[1] + p.v[2]*p.v[2] );
}

template <class FLTYPE>
inline FLTYPE LengthSquared( Vec3<FLTYPE> const & p ){
    return ( p.v[0]*p.v[0] + p.v[1]*p.v[1] + p.v[2]*p.v[2] );
}

template <class FLTYPE>
inline Vec3<FLTYPE> & Normalize( Vec3<FLTYPE> & p ){
    FLTYPE n = sqrt( p.v[0]*p.v[0] + p.v[1]*p.v[1] + p.v[2]*p.v[2] );
    if(n>0.0) p/=n;
    return p;
}

template <class FLTYPE>
inline FLTYPE Distance( Vec3<FLTYPE> const & p1,Vec3<FLTYPE> const & p2 ){
    return Length(p1-p2);
}

template <class FLTYPE>
inline Vec3<FLTYPE> & RotateZ( Vec3<FLTYPE> & p, FLTYPE _angle){
    FLTYPE c=cos(_angle);
    FLTYPE s=sin(_angle);
    FLTYPE cx=c*p.x()-s*p.y();
    p.y()= s*p.x()+c*p.y();
    p.x()= cx;
    return p;
}

typedef Vec3<short>  Point3s;
typedef Vec3<int>	   Point3i;
typedef Vec3<float>  Point3f;
typedef Vec3<double> Point3d;

#ifdef __GL_H__
        inline void glVertex(Vec3<int> const & p)   { glVertex3iv(p.v);};
        inline void glVertex(Vec3<short> const & p) { glVertex3sv(p.v);};
        inline void glVertex(Vec3<float> const & p) { glVertex3fv(p.v);};
        inline void glVertex(Vec3<double> const & p){ glVertex3dv(p.v);};
        inline void glNormal(Vec3<int> const & p)   { glNormal3iv(p.v);};
        inline void glNormal(Vec3<short> const & p) { glNormal3sv(p.v);};
        inline void glNormal(Vec3<float> const & p) { glNormal3fv(p.v);};
        inline void glNormal(Vec3<double> const & p){ glNormal3dv(p.v);};
        inline void glTexCoord(Vec3<int> const & p)   { glTexCoord3iv(p.v);};
        inline void glTexCoord(Vec3<short> const & p) { glTexCoord3sv(p.v);};
        inline void glTexCoord(Vec3<float> const & p) { glTexCoord3fv(p.v);};
        inline void glTexCoord(Vec3<double> const & p){ glTexCoord3dv(p.v);};
        inline void glTranslate(Vec3<float> const & p) { glTranslatef(p.v[0],p.v[1],p.v[2]);};
        inline void glTranslate(Vec3<double> const & p){ glTranslated(p.v[0],p.v[1],p.v[2]);};
        inline void glScale(Vec3<float> const & p) { glScalef(p.v[0],p.v[1],p.v[2]);};
        inline void glScale(Vec3<double> const & p){ glScaled(p.v[0],p.v[1],p.v[2]);};
        #endif
