#include <iostream>
#include <cstring>
#include <time.h>

#include "glm/glm.hpp"

#include "Vector3.h"
#include "Scene.h"
#include "ViewPlane.h"
#include "RTEngine.h"

#include "Primitive.h"
#include "Plane.h"
#include "Sphere.h"
#include "BMPWriter.h"

#include "Windows.h"


//#include <pngWriter.h>

int wWidth = 400;
int wHeight = 300;
const char* wTitle = "title";

RTEngine* renderEngine = NULL;
Vector3<float> color;

unsigned int fps = 0;
DWORD  start, stop;
DWORD  tFrame;

int main(int argc, char** argv)
{
    // create a scene
    Scene* mainScene = new Scene();
    mainScene->Init();

    // create an image plane
    ViewPlane* viewplane = new ViewPlane(wWidth, wHeight);

    // setup rendering engine
    renderEngine = new RTEngine(viewplane, mainScene);

    wWidth = renderEngine->GetViewPlane()->GetWidth();
    wHeight = renderEngine->GetViewPlane()->GetHeight();

    // count time
    start = GetTickCount();
    tFrame = GetTickCount();

    // render an image
    renderEngine->Render();

    tFrame = GetTickCount() - tFrame;

    std::cout << tFrame << " ms/frame" << std::endl;

 // code for write bmp image by using GetColor(i,j) looping for each pixel
    BMPWriter img1(wWidth, wHeight);
    BMPWriter img2(wWidth, wHeight);
    BMPWriter img3(wWidth, wHeight);
    BMPWriter img4(wWidth, wHeight);
    for(int j = 0; j < wHeight; j++)
    {
        for(int i = 0; i < wWidth; i++)
        {
            color = renderEngine->GetViewPlane()->GetColor(i,j);
            img1.setPixel(i,j, color);
			img2.setPixel(i,j, color);
			img3.setPixel(i,j, color);
			img4.setPixel(i,j, color);
        }
    }
	img2.scale();
	img3.scale(0);
	img3.scale(0);
	img3.scale(0);
	img3.scale(0);
	img3.scale(0);
	for(int i = 0;i<30;i++){
		img4.scale(0);
	}
	
    img1.save("test1.bmp");
    img2.save("test2.bmp");
    img3.save("test3.bmp");
    img4.save("test4.bmp");

    return 1;
}
