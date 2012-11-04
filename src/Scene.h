#ifndef SCENE_H_
#define SCENE_H_

#include "includes.h"

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
		Camera* getCamera(){return cam;}

    private :
        // objects in the scene
        std::vector<Primitive*> object;
        // background color
        Color3 bgColor;
		Camera *cam;
};

#endif
