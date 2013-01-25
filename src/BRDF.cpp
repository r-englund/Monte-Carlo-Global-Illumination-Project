#include "includes.h"

Vector3<float> DiffuseBRDF::BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection){
	/*assert(floatEquals(iNormal.Length2(),1));
	assert(floatEquals(oDirection.Length2(),1));
	assert(floatEquals(iDirection.Length2(),1));
	*/
	float i = Dot(iNormal,oDirection);
	if(i < 0)
		return Vector3<float>(0,0,0);
	return color * i;
}

Vector3<float> DiffuseBRDF::randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,Ray& oRay){
	float azimuth,elevation;
	glm::mat4x4 rot;
	glm::vec4 dir;
	glm::vec3 side(0,0,1),N(iNormal[0],iNormal[1],iNormal[2]),V(iDirection[0],iDirection[1],iDirection[2]);
		
	azimuth   = 360*(rand()/(float)(RAND_MAX));
	elevation = acos(sqrt((rand()/(double)(RAND_MAX)))) * 90;
	elevation /= 3.1415/2;

	side = glm::cross(V,N);
	

	rot = glm::rotate(rot,azimuth,N);
	rot = glm::rotate(rot,elevation,side);
	dir = glm::vec4(N,0);

	dir = rot * dir;
	dir = glm::normalize(dir);
	oRay.SetOrigin(pos);
	oRay.SetDir(Vector3<float>(dir[0],dir[1],dir[2]));
	return BRDF(pos,iDirection,iNormal,oRay.GetDir());
}

Vector3<float> PhongBRDF::BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection){
	/*assert(floatEquals(iNormal.Length2(),1));
	assert(floatEquals(oDirection.Length2(),1));
	assert(floatEquals(iDirection.Length2(),1));*/

	Vector3<float> reflection = iDirection -  iNormal *(2.0f * (Dot(iDirection, iNormal)));

	float d = Dot(oDirection,iNormal);
	d = glm::clamp(d,0.0f,1.0f);

	float s = Dot(reflection,oDirection);
	s = glm::clamp(s,0.0f,1.0f);
	s = pow(s,_specularity);
	float i = d * _kd + s * (1-_kd);
	if(i < 0)
		return Vector3<float>(0,0,0);
	return color * i;
}

Vector3<float> PhongBRDF::randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,Ray& oRay){
	//assert(floatEquals(iNormal.Length2(),1));
	//assert(floatEquals(iDirection.Length2(),1));
	
	float r = RandomGenerator::GetRandom();
	if(r<_kd){ //diffuse sample
		float azimuth,elevation;
		glm::mat4x4 rot;
		glm::vec4 dir;
		glm::vec3 side(0,0,1),N(iNormal[0],iNormal[1],iNormal[2]),V(iDirection[0],iDirection[1],iDirection[2]);
		
		azimuth   = 360*(rand()/(float)(RAND_MAX));
		elevation = acos(sqrt((rand()/(double)(RAND_MAX)))) * 90;
		elevation /= 3.1415/2;

		side = glm::cross(V,N);
	

		rot = glm::rotate(rot,azimuth,N);
		rot = glm::rotate(rot,elevation,side);
		dir = glm::vec4(N,0);

		dir = rot * dir;
		dir = glm::normalize(dir);
		oRay.SetOrigin(pos);
		oRay.SetDir(Vector3<float>(dir[0],dir[1],dir[2]));
		return BRDF(pos,iDirection,iNormal,oRay.GetDir());


	}else{ //specular sample
		float azimuth,elevation;
		glm::mat4x4 rot;
		glm::vec4 dir;
		glm::vec3 side(0,0,1),R,N(iNormal[0],iNormal[1],iNormal[2]),V(iDirection[0],iDirection[1],iDirection[2]);
		R = glm::reflect(V,N);

		azimuth   = 360*RandomGenerator::GetRandom();
		elevation = acos(pow((double)RandomGenerator::GetRandom(),1.0/(1+_specularity))) * 90;
		elevation /= 3.1415/2;

		side = glm::cross(R,N);
	

		rot = glm::rotate(rot,azimuth,R);
		rot = glm::rotate(rot,elevation,side);
		dir = glm::vec4(R,0);

		dir = rot * dir;
		dir = glm::normalize(dir);
		oRay.SetOrigin(pos);
		oRay.SetDir(Vector3<float>(dir[0],dir[1],dir[2]));
		return BRDF(pos,iDirection,iNormal,oRay.GetDir());
	}
	
	
}