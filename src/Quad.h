#pragma once
#include "includes.h"
class Quad :
	public Primitive
{
public:
	Quad(Material *m,Vector3<float> corners[3]);
	virtual ~Quad(void);

	
    virtual int GetType();
    virtual int Intersect(const Ray& ray, float& dist);
    virtual const Vector3<float> GetNormal(const Vector3<float>& pNor);

	Vector3<float> getRandomPointOnSurface();

private:
	Vector3<float> corner;
	Vector3<float> e1;
	Vector3<float> e0;
	Vector3<float> normal;
	float l0,l1;
};

