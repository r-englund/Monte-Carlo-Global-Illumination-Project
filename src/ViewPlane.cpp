#include "ViewPlane.h"

ViewPlane::ViewPlane(unsigned int w, unsigned int h)
{
    this->width = w;
    this->height = h;
    color = new Vector3<float>[w*h];
    this->rect.l = -4;
    this->rect.r = 4;
    this->rect.b = -3;
    this->rect.t = 3;
}

ViewPlane::~ViewPlane()
{
    if(color)
    {
        delete[] color;
    }
}

void ViewPlane::SetColor(const Vector3<float>& c, unsigned int x, unsigned int y)
{
    unsigned int index = y*this->width + x;
    this->color[index] = c;

}

Vector3<float>& ViewPlane::GetColor(unsigned int x, unsigned int y)
{
    unsigned int index = y*this->width + x;
    return this->color[index];
}

Vector3<float>* ViewPlane::GetColor()
{
    return this->color;
}
