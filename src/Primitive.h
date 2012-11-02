#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "Ray.h"
#include <cstring>
#include "BRDF.h"


#define EPSILON         0.01

#define HIT             1
#define MISS            0
#define INSIDE          -1

#define SPHERE          10
#define PLANE           11



//
//class IPrimitive
//{
//    public :
//        virtual ~IPrimitive(){}
//        virtual int GetType() = 0;
//        virtual int Intersect(const Ray& ray, float& dist) = 0;
//        virtual const Vector3<float> GetNormal(const Vector3<float>& pNor) = 0;
//};

class Primitive //: public IPrimitive
{
    protected :
        Material* material;
        std::string name;
        bool light;

    public :
		Primitive(): name("Primitive"), light(false){ material = new DiffuseBRDF();}

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
