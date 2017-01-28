#include <GL/glew.h>

#include "geometry/Vec3.h"

void glVertex(Vec3<int> const &v) { glVertex3iv(v.coords);}
void glVertex(Vec3<short> const &v) { glVertex3sv(v.coords);}
void glVertex(Vec3<float> const &v) { glVertex3fv(v.coords);}
void glVertex(Vec3<double> const &v) { glVertex3dv(v.coords);}
void glNormal(Vec3<int> const &v) { glNormal3iv(v.coords);}
void glNormal(Vec3<short> const &v) { glNormal3sv(v.coords);}
void glNormal(Vec3<float> const & v) { glNormal3fv(v.coords);}
void glNormal(Vec3<double> const & v){ glNormal3dv(v.coords);}
void glTexCoord(Vec3<int> const & v)   { glTexCoord3iv(v.coords);}
void glTexCoord(Vec3<short> const & v) { glTexCoord3sv(v.coords);}
void glTexCoord(Vec3<float> const & v) { glTexCoord3fv(v.coords);}
void glTexCoord(Vec3<double> const & v){ glTexCoord3dv(v.coords);}
void glTranslate(Vec3<float> const & v) { glTranslatef(v.coords[0],v.coords[1],v.coords[2]);}
void glTranslate(Vec3<double> const & v){ glTranslated(v.coords[0],v.coords[1],v.coords[2]);}
void glScale(Vec3<float> const & v) { glScalef(v.coords[0],v.coords[1],v.coords[2]);}
void glScale(Vec3<double> const & v){ glScaled(v.coords[0],v.coords[1],v.coords[2]);}
