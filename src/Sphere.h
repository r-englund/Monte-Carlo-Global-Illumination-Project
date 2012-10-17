#ifndef SPHERE_H_
#define SPHERE_H_

#include "Primitive.h"
#include <cmath>

class Sphere : public Primitive
{
    protected :
        float radius;
        Vector3<float> center;
        float radius2;
        float deradius;

    public :
        Sphere(const Vector3<float>& c, float r);
        ~Sphere(){}

        const Vector3<float>& GetCenter(){ return this->center;}
        float GetRadius(){ return this->radius;}

        virtual int GetType(){return SPHERE;};
        virtual int Intersect(const Ray& ray, float& dist);
        virtual const Vector3<float> GetNormal(const Vector3<float>& pNor);


};

#endif