#ifndef __BRDF_H__
#define __BRDF_H__

#include "includes.h"


class Material
{
    protected :
        Color3 color;
        float refract;
        float refractInd;

    public :
        Material(): refract(0.0f), refractInd(1.5f){color = Color3(0.2,0.2,0.2);}
        Material(const Material& mat)
        {
            this->color = mat.color;
        }
        virtual ~Material(){}

        float GetRefractInd(){ return this->refractInd;}
        float GetRefract(){ return this->refract;}
        const Color3& GetColor(){ return this->color;}

        void SetRefractInd(float rInd){ this->refractInd = rInd;}
        void SetRefract(float r){ this->refract = r;}
        void SetColor(const Color3& c){ this->color = c;}

		virtual Vector3<float> BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection) = 0;
		virtual Vector3<float> randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal, Ray& oRay) = 0;
};


class DiffuseBRDF : public Material{
public:
	DiffuseBRDF(){}
	virtual ~DiffuseBRDF(){}
	virtual Vector3<float> BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection);
	virtual Vector3<float> randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal, Ray& oRay);
};

class PhongBRDF : public Material{
	float _specularity,_kd;
public:
	PhongBRDF(float specularity = 20,float kd = 0.5){_specularity = specularity;_kd = kd;}
	virtual ~PhongBRDF(){}
	virtual Vector3<float> BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection);
	virtual Vector3<float> randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal, Ray& oRay);
};

#endif