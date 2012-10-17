#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <iostream>
#include "Vector3.h"
#include "Primitive.h"
#include "Plane.h"
#include "Sphere.h"


#define SC_SUCCESS          0

class Scene
{
    public :
        Scene();
        ~Scene();

        int Init();
        unsigned int GetNumObject(){ return object.size();}
        Primitive* GetObject(unsigned int index){ return object[index];}

        const Color3& GetBGColor(){ return this->bgColor;}

    private :
        // objects in the scene
        std::vector<Primitive*> object;
        // background color
        Color3 bgColor;
};

#endif
