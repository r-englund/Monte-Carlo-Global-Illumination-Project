#ifndef PLANE_H_
#define PLANE_H_

#include "Primitive.h"

class Plane : public Primitive
{
    protected :
        Vector3<float> Normal;
        float DistP;
        Vector3<float> PPoint;

    public :
        Plane(const Vector3<float>& normal, float d);
        Plane(const Vector3<float>& normal, const Vector3<float>& point);
        ~Plane(){}

        Plane(const Plane& plane);

        const Vector3<float>& GetNormal(){ return this->Normal;}
        float GetDistP(){ return this->DistP;}

        virtual int GetType(){ return PLANE;}
        virtual int Intersect(const Ray& ray, float& dist);
        virtual const Vector3<float> GetNormal(const Vector3<float>& pNor);

};

#endif
