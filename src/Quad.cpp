#include "Quad.h"


Quad::Quad(Material *m,Vector3<float> corners[3]) : Primitive(m)
{
	corner = corners[0];
	e0 = corners[1] - corners[0];
	e1 = corners[2] - corners[0];
	normal = Cross(e0,e1);
	normal.Normalize();
	l0 = e0.Length();
	l1 = e1.Length();
	e0.Normalize();
	e1.Normalize();
}


Quad::~Quad(void)
{
}


int Quad::GetType(){
	return QUAD;
}

Vector3<float> Quad::getRandomPointOnSurface(){
	float u = RandomGenerator::GetRandom()*l0;
	float v = RandomGenerator::GetRandom()*l1;
	return corner +  e0*u + e1*v;
}

int Quad::Intersect(const Ray& ray, float& dist){
	if(this == ray.GetOriginObject())
		return MISS;
    // (p - a).n = 0 : p (intersection point), a (point on plane), n (plane normal)
    // find t : paramT which satisfies --> (p-a).n = 0 , (o + dt - a).n = 0
    // paramT = (PPoint - Origin).Normal / Normal.Direction
    float n_d = Dot(this->normal, ray.GetDir());
    Vector3<float> p_o(this->corner - ray.GetOrigin());
    if( fabs(n_d) > EPSILON)
    {
        float paramT = Dot(p_o, normal);
        paramT = paramT / n_d;
        if(paramT > 0)
        {
            if( paramT < dist)
            {
                Vector3<float> hit;
				hit[0] = ray.GetOrigin()[0];
				hit[1] = ray.GetOrigin()[1];
				hit[2] = ray.GetOrigin()[2];
				
				hit[0] += ray.GetDir()[0]*paramT;
				hit[1] += ray.GetDir()[1]*paramT;
				hit[2] += ray.GetDir()[2]*paramT;

				hit -= corner;
				float d0,d1;
				d0 = Dot(hit,e0);
				d1 = Dot(hit,e1);
				if((d0 <= l0 && d0 >= 0) && (d1 <= l1 && d1 >= 0) ){
					dist = paramT;
					return HIT;
				}
            }
        }
    }

    return MISS;


}
const Vector3<float> Quad::GetNormal(const Vector3<float>& pNor){
	return normal;
}