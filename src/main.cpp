#include <iostream>
#include <cstring>
#include <time.h>

#include <glm/glm.hpp>

#include "Vector3.h"
#include "Scene.h"
#include "ViewPlane.h"
#include "RTEngine.h"

#include "Primitive.h"
#include "Plane.h"
#include "Sphere.h"

#include <pngWriter.h>

int wWidth = 800;
int wHeight = 600;
const char* wTitle = "title";

RTEngine* renderEngine = NULL;
Vector3<float> color;

unsigned int fps = 0;
time_t start, stop;
time_t tFrame;

int main(int argc, char** argv)
{
    // create a scene
    Scene* mainScene = new Scene();
    mainScene->Init();

    // create an image plane
    ViewPlane* viewplane = new ViewPlane(800, 600);

    // setup rendering engine
    renderEngine = new RTEngine(viewplane, mainScene);

    wWidth = renderEngine->GetViewPlane()->GetWidth();
    wHeight = renderEngine->GetViewPlane()->GetHeight();

    // count time
    start = time(NULL);
    tFrame = time(0);

    // render an image
    renderEngine->Render();

    tFrame = time(0) - tFrame;

    std::cout << tFrame << " sec/frame" << std::endl;

//  code for write png image by using GetColor(i,j) looping for each pixel
//    pngwriter* img = new pngwriter(wWidth, wHeight, 0, "RT.png");
//    for(int j = 0; j < wHeight; j++)
//    {
//        for(int i = 0; i < wWidth; i++)
//        {
//            color = renderEngine->GetViewPlane()->GetColor(i,j);
//            img->plot(i,j, color[0], color[1], color[2]);
//        }
//    }
//    img->close();
//    delete img;

    return 1;
}
