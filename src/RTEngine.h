#ifndef RTENGINE_H_
#define RTENGINE_H_

#include <limits>
#include <iostream>
#include <queue>

#include "Ray.h"
#include "ViewPlane.h"
#include "Scene.h"

#define OMP_NUM_THREADS 8

#define SAMPLES_PER_PIXEL 150
#define TRACEDEPTH     6

#define PRIMARY         1
#define REFLECT         2
#define REFRACT         3

class RTEngine
{
    protected :
        ViewPlane* view;
        Scene* scene;
        float pdx, pdy;     //pixel space in x,y

    public :
        RTEngine();
        RTEngine(ViewPlane* vp, Scene* sce);
        ~RTEngine();

        void InitRender();
        bool Render();
        Primitive* RayTrace(const Ray& iRay, Color3& oColor, int iDepth, float iRIndex, float& oDist);

        void SetScene(Scene* sc){ this->scene = sc;}
        void SetViewPlane(ViewPlane* vp);

        Scene* GetScene(){ return this->scene;}
        ViewPlane* GetViewPlane(){ return this->view;}
};

#endif
