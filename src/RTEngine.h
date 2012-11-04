#ifndef RTENGINE_H_
#define RTENGINE_H_

#include "includes.h"

class ViewPlane;
class Scene;
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
