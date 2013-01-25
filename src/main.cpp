
#include "includes.h"

#include <fstream>

#include "Windows.h"

RTEngine* renderEngine = NULL;
Vector3<float> color;

unsigned int fps = 0;
DWORD  start, stop;
DWORD  tFrame;

bool floatEquals(float a,float b,float e){
	return abs(a-b)<e;
}

void month(char* out,int month){
	switch(month){
	case 0:
		out = "jan\0";
		break;
	case 1:
		out = "feb\0";
		break;
	case 2:
		out = "mar\0";
		break;
	case 3:
		out = "apr\0";
		break;
	case 4:
		out = "may\0";
		break;
	case 5:
		out = "jun\0";
		break;
	case 6:
		out = "jul\0";
		break;
	case 7:
		out = "aug\0";
		break;
	case 8:
		out = "sep\0";
		break;
	case 9:
		out = "oct\0";
		break;
	case 10:
		out = "nov\0";
		break;
	case 11:
		out = "dec\0";
		break;
	}
}

void filename(const char * start,const char * end,char *out) {
	time_t t = time(0);
	struct tm * now = localtime( & t );

	char* mon = (char*)malloc(sizeof(char)*4);
	month(mon,now->tm_mon);
	sprintf(out,"%s%d-%d-%d-%d-%d-%d%s",start,
									now->tm_year+1900,
									mon,
									now->tm_mday,
									now->tm_hour,
									now->tm_min,
									now->tm_sec,
									end);
}

int main(int argc, char** argv)
{
	int WIDTH = 400;
	int HEIGHT = 400;
	int SAMPLES_PER_PIXEL = 10;
	int TRACEDEPTH = 5;
	Scene* mainScene = 0;


	for(int i = 1;i<argc;i+=2){
		if(argv[i][1] == 'w'){
			WIDTH = atoi(argv[i+1]);		
		}
		if(argv[i][1] == 'h'){
			HEIGHT = atoi(argv[i+1]);		
		}
		if(argv[i][1] == 's'){
			SAMPLES_PER_PIXEL = atoi(argv[i+1]);		
		}
		if(argv[i][1] == 't'){
			TRACEDEPTH = atoi(argv[i+1]);		
		}

		if(argv[i][1] == 'S'){
			mainScene = Scene::LoadScene(argv[i+1]);		
		}
	}

	char *a,*b,*c,*d,*e;
	a = (char*)malloc(sizeof(char)*34);
	b = (char*)malloc(sizeof(char)*34);
	c = (char*)malloc(sizeof(char)*34);
	d = (char*)malloc(sizeof(char)*34);
	e = (char*)malloc(sizeof(char)*33);
	filename("img/","-test1.bmp",a);
	filename("img/","-test2.bmp",b);
	filename("img/","-test3.bmp",c);
	filename("img/","-test4.bmp",d);
	filename("img/","-info.txt",e);

	std::ofstream info(e);
	info << "Width: "  << WIDTH << std::endl;
	info << "Height: " << HEIGHT << std::endl;
	info << "Trace depth: " << TRACEDEPTH << std::endl;
	info << "Samples Per Pixel: " << SAMPLES_PER_PIXEL << std::endl;
	info << "Nummber of threads: " << omp_get_max_threads() << std::endl;
	info << "Files:" << std::endl;
	info << '\t' << a << std::endl;
	info << '\t' << b << std::endl;
	info << '\t' << c << std::endl;
	info << '\t' << d << std::endl;
	
	srand((unsigned)time(0));
    // create a scene
	if(mainScene == 0){
		mainScene = new Scene();
		mainScene->Init();
	} 
    

    // create an image plane
    ViewPlane* viewplane = new ViewPlane(WIDTH, HEIGHT);

    // setup rendering engine
    renderEngine = new RTEngine(viewplane, mainScene);
	renderEngine->setTraceDepth(TRACEDEPTH);
	renderEngine->setSamplesPerPixel(SAMPLES_PER_PIXEL);
    // count time
    start = GetTickCount();
    tFrame = GetTickCount();

    // render an image
    renderEngine->Render();

    tFrame = GetTickCount() - tFrame;

	info << "Rendering time: " << tFrame << "ms" << std::endl;

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
	
	/*img1.save(a);
    img2.save(b);
    img3.save(c);*/
    img4.save(d);

	std::cout << "closing file" << std::endl;
	info.close();
	
	std::cout << "after closing file" << std::endl;
	free(a);std::cout << "a" << std::endl;
	free(b);std::cout << "b" << std::endl;
	free(c);std::cout << "c" << std::endl;
	free(d);std::cout << "d" << std::endl;
	free(e);std::cout << "e" << std::endl;
	delete mainScene;std::cout << "mains" << std::endl;
	delete viewplane;std::cout << "viewp" << std::endl;
	delete renderEngine;std::cout << "rendere" << std::endl;


	std::cout << "DONE" << std::endl;
    return 0;
}
