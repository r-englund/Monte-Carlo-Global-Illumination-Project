#include "includes.h"

Vector3<float> DiffuseBRDF::BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection){
	assert(floatEquals(iNormal.Length2(),1));
	assert(floatEquals(oDirection.Length2(),1));
	assert(floatEquals(iDirection.Length2(),1));
	
	float i = Dot(iNormal,oDirection);
	if(i < 0)
		return Vector3<float>(0,0,0);
	return color * i;
}

Vector3<float> DiffuseBRDF::randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,Ray& oRay){
	assert(floatEquals(iNormal.Length2(),1));
	assert(floatEquals(iDirection.Length2(),1));

	float azimuth,elevation;
	azimuth   = 360*(rand()/(float)(RAND_MAX));
	elevation = acos(sqrt((rand()/(double)(RAND_MAX)))) * 90;
	elevation /= 3.1415;

	glm::vec4 dir(iNormal[0],iNormal[1],iNormal[2],0);
	glm::mat4x4 rot;
	//rot = glm::rotate(rot,azimuth,glm::vec3(iNormal[0],iNormal[1],iNormal[2]));
	rot = glm::rotate(rot,azimuth,glm::vec3(0,1,0));
	rot = glm::rotate(rot,elevation,glm::vec3(0,0,1));
	dir = rot * dir;

	dir = glm::normalize(dir);
	oRay.SetOrigin(pos);
	oRay.SetDir(Vector3<float>(dir[0],dir[1],dir[2]));
	return BRDF(pos,iDirection,iNormal,oRay.GetDir());
}

Vector3<float> PhongBRDF::BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection){
	assert(floatEquals(iNormal.Length2(),1));
	assert(floatEquals(oDirection.Length2(),1));
	assert(floatEquals(iDirection.Length2(),1));

	Vector3<float> reflection = iDirection -  iNormal *(2.0f * (Dot(iDirection, iNormal)));

	float i = Dot(reflection,oDirection);
	if(i < 0)
		return Vector3<float>(0,0,0);
	return color * i;
}

Vector3<float> PhongBRDF::randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,Ray& oRay){
	assert(floatEquals(iNormal.Length2(),1));
	assert(floatEquals(iDirection.Length2(),1));

	oRay.SetOrigin(pos);
	oRay.SetDir(iDirection -  iNormal *(2.0f * (Dot(iDirection, iNormal))));
	return BRDF(pos,iDirection,iNormal,oRay.GetDir());
}