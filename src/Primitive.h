#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "Ray.h"
#include <cstring>

typedef Vector3<float> Color3;

#define EPSILON         0.0001

#define HIT             1
#define MISS            0
#define INSIDE          -1

#define SPHERE          10
#define PLANE           11

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

};

class IPrimitive
{
    public :
        virtual ~IPrimitive(){}
        virtual int GetType() = 0;
        virtual int Intersect(const Ray& ray, float& dist) = 0;
        virtual const Vector3<float> GetNormal(const Vector3<float>& pNor) = 0;
};

class Primitive : public IPrimitive
{
    protected :
        Material* material;
        std::string name;
        bool light;

    public :
        Primitive(): name("Primitive"), light(false){ material = new Material();}

        virtual ~Primitive(){if(material) delete material;};

        bool IsLight(){return this->light;}
        void SetLight(bool l){ this->light = l;}

        Material* GetMaterial(){ return this->material;}
        void SetMaterial(Material* mat){ this->material= mat;}

        std::string GetName(){ return name;}
        void SetName(std::string sname){ name.assign(sname);}

        virtual int GetType() = 0;
        virtual int Intersect(const Ray& ray, float& dist) = 0;
        virtual const Vector3<float> GetNormal(const Vector3<float>& pNor) = 0;
};

#endif
