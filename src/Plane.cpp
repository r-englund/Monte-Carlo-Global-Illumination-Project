#include "includes.h"

Plane::Plane(Material *m,const Vector3<float>& normal, float d) : Primitive(m)
{
    this->Normal = normal;
    this->DistP = d;
}

Plane::Plane(Material *m,const Vector3<float>& normal, const Vector3<float>& point) : Primitive(m)
{
    this->Normal = normal;
    this->PPoint = point;
}


Plane::Plane(const Plane& plane) : Primitive(plane.material)
{
    this->Normal = plane.Normal;
    this->DistP = plane.DistP;
    this->PPoint = plane.PPoint;
}

int Plane::Intersect(const Ray& iRay, float& ioDist)
{
	if(this == iRay.GetOriginObject())
		return MISS;
    // (p - a).n = 0 : p (intersection point), a (point on plane), n (plane normal)
    // find t : paramT which satisfies --> (p-a).n = 0 , (o + dt - a).n = 0
    // paramT = (PPoint - Origin).Normal / Normal.Direction
    float n_d = Dot(this->Normal, iRay.GetDir());
    Vector3<float> p_o(this->PPoint - iRay.GetOrigin());
    if( fabs(n_d) > EPSILON)
    {
        float paramT = Dot(p_o, this->Normal);
        paramT = paramT / n_d;
        if(paramT > 0)
        {
            if( paramT < ioDist)
            {
                ioDist = paramT;
                return HIT;
            }
        }
    }

    return MISS;
}

const Vector3<float> Plane::GetNormal(const Vector3<float>& pNor)
{
    return this->Normal;
}
