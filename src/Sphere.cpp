#include "Sphere.h"

Sphere::Sphere(const Vector3<float>& c, float r) : Primitive()
{
    this->center = c;
    this->radius = r;
    this->radius2 = r*r;
    this->deradius = 1/r;
}

int Sphere::Intersect(const Ray& iRay, float& ioDist)
{
//    Vector3<float> oc = iRay.GetOrigin() - this->center;
//    float cos =  -Dot(oc, iRay.GetDir());
//    float det = (cos*cos) - ( Dot(oc,oc) ) + this->radius2;
//    int ret = MISS;
//    if(det > 0)
//    {
//        det = sqrt(det);
//        float i1 = cos - det;
//        float i2 = cos + det;
//        if( i2 > 0 )
//        {
//            if( i1 < 0 )
//            {
//                if( i2 < ioDist )
//                {
//                    ioDist = i2;
//                    ret = INSIDE;
//                }
//            }
//            else
//            {
//                if( i1 < ioDist)
//                {
//                    ioDist = i1;
//                    ret = HIT;
//                }
//            }
//        }
//    }
    int ret = MISS;
    Vector3<float> o_c(iRay.GetOrigin() - this->center);
    float a = Dot(iRay.GetDir(), iRay.GetDir());
    float b = Dot(o_c, iRay.GetDir()) * 2;
    float c = Dot(o_c, o_c) - this->radius2;
    float dis = b*b - 4*a*c;
    float paramT1, paramT2;
    if(dis > EPSILON)
    {
        dis = sqrtf(dis);
        paramT1 = (-b - dis)/ (2*a);    // smaller root
        paramT2 = (-b + dis)/ (2*a);    // larger root
        if(paramT2 > EPSILON)
        {
            if(paramT1 < EPSILON)       // inside sphere
            {
                if( paramT2 < ioDist )
                {
                    ioDist = paramT2;
                    ret = INSIDE;
                }
            }
            else                        // outside & hit
            {
                if( paramT1 < ioDist )
                {
                    ioDist = paramT1;
                    ret = HIT;
                }
            }
        }
    }

    return ret;
}

const Vector3<float> Sphere::GetNormal(const Vector3<float>& pNor)
{
    return (pNor - this->center) * this->deradius;
}
