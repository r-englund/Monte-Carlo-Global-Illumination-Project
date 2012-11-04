#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "Ray.h"

struct Camera{
	Camera(){}
	~Camera(){}
	Vector3<float> position;
	Vector3<float> direction;
	Vector3<float> upDirection;
	float focalLength;
	float width,height;

	void setAspectRatio(float ar){
		width = height / ar;
	}

	Ray RayToPixel(float x,float y)const;
};

#endif