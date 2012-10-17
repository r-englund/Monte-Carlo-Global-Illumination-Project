#ifndef VIEWPLANE_H_
#define VIEWPLANE_H_

#include "Vector3.h"

typedef struct _rect
{
    float l;
    float r;
    float b;
    float t;
}Rect;


class ViewPlane
{

    private :
        // width , height  : number of pixels
        unsigned int width;
        unsigned int height;
        // screen coordinate
        Rect rect;
        Vector3<float>* color;

    public :
        ViewPlane(unsigned int w = 800, unsigned int h = 600);
        ~ViewPlane();

        unsigned int GetWidth(){ return this->width;}
        unsigned int GetHeight(){ return this->height;}

        void SetColor(const Vector3<float>& c, unsigned int x, unsigned int y);
        Vector3<float>& GetColor(unsigned int x, unsigned int y);
        Vector3<float>* GetColor();

        const Rect& GetCoordinate(){ return this->rect;}

};

#endif
