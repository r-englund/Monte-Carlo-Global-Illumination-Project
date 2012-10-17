#ifndef RAY_H_
#define RAY_H_

#include "Vector3.h"

//template <typename T>
class Ray
{
    protected :
        Vector3<float> origin;
        Vector3<float> dir;
    public :
        Ray():origin(Vector3<float>()), dir(Vector3<float>()){}
        Ray(const Vector3<float>& o, const Vector3<float>& d):origin(o), dir(d){}
        ~Ray(){}

        void SetOrigin(const Vector3<float>& newOrigin){ this->origin = newOrigin;}
        void SetDir(const Vector3<float>& newDir){ this->dir = newDir;}

        const Vector3<float>& GetOrigin() const{ return this->origin; }
        const Vector3<float>& GetDir() const{ return this->dir; }

        const Ray& operator=(const Ray& ray)
        {
            if(this != &ray)
            {
                this->origin = ray.origin;
                this->dir = ray.dir;
            }
            return *this;
        }

};


#endif
