
#include "includes.h"

#include "Windows.h"

RTEngine* renderEngine = NULL;
Vector3<float> color;

unsigned int fps = 0;
DWORD  start, stop;
DWORD  tFrame;

bool floatEquals(float a,float b,float e){
	return abs(a-b)<e;
}

void filename(const char * start,const char * end,char *out) {
	time_t t = time(0);
	struct tm * now = localtime( & t );
	sprintf(out,"%s%d-%d-%d-%d-%d-%d%s",start,
									now->tm_year+1900,
									now->tm_mon,
									now->tm_mday,
									now->tm_hour,
									now->tm_min,
									now->tm_sec,
									end);
}

int main(int argc, char** argv)
{
	srand((unsigned)time(0));
    // create a scene
    Scene* mainScene = new Scene();
    mainScene->Init();

    // create an image plane
    ViewPlane* viewplane = new ViewPlane(WIDTH, HEIGHT);

    // setup rendering engine
    renderEngine = new RTEngine(viewplane, mainScene);

    // count time
    start = GetTickCount();
    tFrame = GetTickCount();

    // render an image
    renderEngine->Render();

    tFrame = GetTickCount() - tFrame;

    std::cout << tFrame << " ms/frame" << std::endl;

 // code for write bmp image by using GetColor(i,j) looping for each pixel
    BMPWriter img1(WIDTH, HEIGHT);
    BMPWriter img2(WIDTH, HEIGHT);
    BMPWriter img3(WIDTH, HEIGHT);
    BMPWriter img4(WIDTH, HEIGHT);
    for(int j = 0; j < HEIGHT; j++)
    {
        for(int i = 0; i < WIDTH; i++)
        {
            color = renderEngine->GetViewPlane()->GetColor(i,j);
            img1.setPixel(i,j, color);
			img2.setPixel(i,j, color);
			img3.setPixel(i,j, color);
			img4.setPixel(i,j, color);
        }
    }
	img2.flat();
	img3.scale(0);
	for(int i = 0;i<6;i++){
		img4.scale(0);
	}
	char *a,*b,*c,*d;
	a = (char*)malloc(sizeof(char)*33);
	b = (char*)malloc(sizeof(char)*33);
	c = (char*)malloc(sizeof(char)*33);
	d = (char*)malloc(sizeof(char)*33);
	filename("img/a","-test1.bmp",a);
	filename("img/b","-test2.bmp",b);
	filename("img/c","-test3.bmp",c);
	filename("img/d","-test4.bmp",d);
	img1.save(a);
    img2.save(b);
    img3.save(c);
    img4.save(d);
    return 1;
}
