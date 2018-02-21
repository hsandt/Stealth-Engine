#include <GL/glew.h>

#include "core/math/Vector3.h"

void glVertex(Vector3 const &v) { glVertex3fv(v.coords);}
void glNormal(Vector3 const & v) { glNormal3fv(v.coords);}
void glTexCoord(Vector3 const & v) { glTexCoord3fv(v.coords);}
void glTranslate(Vector3 const & v) { glTranslatef(v.coords[0],v.coords[1],v.coords[2]);}
void glScale(Vector3 const & v) { glScalef(v.coords[0],v.coords[1],v.coords[2]);}

// uncomment if you moved conversion operator definition here (include what you need to)
//operator b2Vec3(const Vector3&) {
//	return {coords[0], coords[1], coords[2]};
//}
