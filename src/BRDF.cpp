#include "BRDF.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Vector3<float> DiffuseBRDF::BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection){
	float i = Dot(iNormal,oDirection);
	if(i < 0)
		return Vector3<float>(0,0,0);
	return color * i;
}

Vector3<float> DiffuseBRDF::randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,Ray& oRay){
	float azimuth,elevation;
	azimuth   = 2*3.1415*(rand()/(float)(RAND_MAX));
	elevation = acos(sqrt((rand()/(double)(RAND_MAX))));

	glm::vec4 dir(iNormal[0],iNormal[1],iNormal[2],0);
	glm::mat4x4 rot;
	rot = glm::rotate(rot,elevation,glm::vec3(0,0,1));
	rot = glm::rotate(rot,azimuth,glm::vec3(iNormal[0],iNormal[1],iNormal[2]));
	dir = rot * dir;

	dir = glm::normalize(dir);
	oRay.SetOrigin(pos);
	oRay.SetDir(Vector3<float>(dir[0],dir[1],dir[2]));
	return BRDF(pos,iDirection,iNormal,oRay.GetDir());
}

Vector3<float> PhongBRDF::BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection){
	float i = Dot(iNormal,oDirection);
	if(i < 0)
		return Vector3<float>(0,0,0);
	return color * i;
}

Vector3<float> PhongBRDF::randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,Ray& oRay){
	oRay.SetOrigin(pos);
	oRay.SetDir(iDirection -  iNormal *(2.0f * (Dot(iDirection, iNormal))));
	return BRDF(pos,iDirection,iNormal,oRay.GetDir());
}