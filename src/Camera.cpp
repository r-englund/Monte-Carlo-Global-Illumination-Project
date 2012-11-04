#include "includes.h"

Ray Camera::RayToPixel(float x,float y)const{
	assert(floatEquals(direction.Length2(),1));
	assert(floatEquals(upDirection.Length2(),1));
	assert(Dot(upDirection,direction) == 0);
	assert(focalLength != 0);
	assert(width != 0);
	assert(height != 0);

	Vector3<float> side = Cross(upDirection,direction);
	Vector3<float> pixel = position + direction * focalLength;
	pixel += side * (0.5*width*(2*x-1));
	pixel += upDirection * (0.5*height*(2*y-1));

	Vector3<float> dir = pixel-position;
	dir.Normalize();

	Ray r;
	r.SetOrigin(position);
	r.SetDir(dir);

	return r;

}