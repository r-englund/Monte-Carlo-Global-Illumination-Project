#ifndef __BRDF_H__
#define __BRDF_H__

#include "Vector3.h"
#include "Ray.h"

typedef Vector3<float> Color3;

class Material
{
    protected :
        Color3 color;
        float diffuse;
        float reflect;
        float specular;
        float refract;
        float refractInd;

    public :
        Material(): diffuse(0.2f), reflect(0.0f), specular(0.8f), refract(0.0f), refractInd(1.5f){color = Color3(0.2,0.2,0.2);}
        Material(const Material& mat)
        {
            this->color = mat.color;
            this->diffuse = mat.diffuse;
            this->reflect = mat.reflect;
        }
        ~Material(){}

        float GetRefractInd(){ return this->refractInd;}
        float GetRefract(){ return this->refract;}
        float GetSpecular(){ return this->specular;}
        float GetDiffuse(){ return this->diffuse;}
        float GetReflect(){ return this->reflect;}
        const Color3& GetColor(){ return this->color;}

        void SetRefractInd(float rInd){ this->refractInd = rInd;}
        void SetRefract(float r){ this->refract = r;}
        void SetSpecular(float s){ this->specular = s;}
        void SetDiffuse(float d){ this->diffuse = d;}
        void SetReflect(float r){ this->reflect = r;}
        void SetColor(const Color3& c){ this->color = c;}

		virtual Vector3<float> BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection) = 0;
		virtual Vector3<float> randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal, Ray& oRay) = 0;
};


class DiffuseBRDF : public Material{
public:
	DiffuseBRDF(){}
	virtual Vector3<float> BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection);
	virtual Vector3<float> randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal, Ray& oRay);
};

class PhongBRDF : public Material{
public:
	PhongBRDF(){}
	virtual Vector3<float> BRDF(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal,const Vector3<float>& oDirection);
	virtual Vector3<float> randomReflection(const Vector3<float>& pos,const Vector3<float>& iDirection,const Vector3<float>& iNormal, Ray& oRay);
};

#endif