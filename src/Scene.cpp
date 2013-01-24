#include "includes.h"

#include <fstream>
#include <map>
#include <string>


Scene::Scene()
{
    bgColor = Color3(0,0,0);
	cam = new Camera();
}

Scene::~Scene()
{
    for(unsigned int i = 0; i < this->object.size(); i++)
    {
        if(this->object[i])
            delete this->object[i];
    }
	delete cam;
}

#if SCENE == SCENE_OUR
int Scene::Init()
{

    //sphere 1
    Sphere* s1 = new Sphere(Vector3<float>(2.0,0.8,3), 2.5f);
    s1->SetName("big Sphere1");
    s1->GetMaterial()->SetRefract(0.8f);
    s1->GetMaterial()->SetRefractInd(1.3f);
    s1->GetMaterial()->SetColor(Vector3<float>(0.2,0.2,0.2));
    s1->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(s1);

    //sphere 2
    Sphere* s2 = new Sphere(Vector3<float>(-5.5, -0.5, 7), 2.0);
    s2->SetName("small Sphere2");
    s2->GetMaterial()->SetRefract(0.0f);
    s2->GetMaterial()->SetRefractInd(1.3f);
    s2->GetMaterial()->SetColor(Vector3<float>(0.7,0.7,1.0));
    s2->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(s2);

    //light 1
    Sphere* l1 = new Sphere(Vector3<float>(0, 5, 5), 0.5);
    l1->SetName("Light1");
    l1->SetLight(true);
    l1->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.8));
    this->object.push_back(l1);

    //light 2
    Sphere* l2 = new Sphere(Vector3<float>(-3, 5, 1), 0.5);
    l2->SetName("Light2");
    l2->SetLight(true);
    l2->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.8));
    this->object.push_back(l2);

    // extra sphere
    s1 = new Sphere(Vector3<float>(-1.5, -3.8, 1), 1.5f);
    s1->SetName("extra sphere");
    s1->GetMaterial()->SetRefract(0.8f);
    s1->GetMaterial()->SetColor(Color3(1.0,0.4,0.4));
    this->object.push_back(s1);
	
	
    //ground plane
//    Primitive* plane = new Plane(Vector3<float>(0,1,0), 4.4f);
    Primitive* plane = new Plane(Vector3<float>(0,1,0), Vector3<float>(0,-4.4,0));
    plane->SetName("Floor");
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetColor(Vector3<float>(0.4,0.3,0.3));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);
    // back plane
    plane = new Plane(Vector3<float>(0, 0, -1), Vector3<float>(0,0,12));
    plane->SetName("back plane");
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);
	
    // behind us plane
    plane = new Plane(Vector3<float>(0, 0, 1), Vector3<float>(0,0,-8));
    plane->SetName("behind us plane");
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);

    // right plane
    plane = new Plane(Vector3<float>(-1, 0, 0), Vector3<float>(8,0,0));
    plane->SetName("right plane");
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
    plane->GetMaterial()->SetColor(Vector3<float>(1.0,0.1,0.1));
    this->object.push_back(plane);

    // left plane
    plane = new Plane(Vector3<float>(1, 0, 0), Vector3<float>(-8,0,0));
    plane->SetName("left plane");
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.1,1.0,0.1));
    this->object.push_back(plane);

    // ceiling plane
    plane = new Plane(Vector3<float>(0, -1, 0), Vector3<float>(0,7,0));
    plane->SetName("celing plane");
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetColor(Color3(0.4f,0.7f,0.7f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);

    {
        s1 = new Sphere(Vector3<float>(-4.5f + 5*1.5f, -4.3f + 4*1.5f, 10), 0.3f);
        s1->SetName("grid sphere");
        s1->GetMaterial()->SetRefract(0.0f);
        s1->GetMaterial()->SetColor(Color3(0.3,1.0,0.4));
        this->object.push_back(s1);
    }

    {
        s1 = new Sphere(Vector3<float>(-4.5f + 6*1.5f, -4.3f + 3*1.5f, 10), 0.3f);
        s1->SetName("grid sphere");
        s1->GetMaterial()->SetRefract(0.0f);
        s1->GetMaterial()->SetColor(Color3(0.3,1.0,0.4));
        this->object.push_back(s1);
    }

	
	cam->position = Vector3<float>(0,0,-5);
	cam->direction = Vector3<float>(0,0,1);
	cam->upDirection = Vector3<float>(0,1,0);
	cam->focalLength = 0.035;
	cam->width = 0.025;
	cam->height = 0.025;
	

    return SC_SUCCESS;
}
#endif
#if SCENE == SCENE_OUR_OLD

int Scene::Init()
{

    //sphere 1
    Sphere* s1 = new Sphere(Vector3<float>(2.0,0.8,3), 2.5f);
    s1->SetName("big Sphere1");
    s1->GetMaterial()->SetRefract(0.8f);
    s1->GetMaterial()->SetRefractInd(1.3f);
    s1->GetMaterial()->SetColor(Vector3<float>(0.2,0.2,0.2));
    s1->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(s1);

    //sphere 2
    Sphere* s2 = new Sphere(Vector3<float>(-5.5, -0.5, 7), 2.0);
    s2->SetName("small Sphere2");
    s2->GetMaterial()->SetRefract(0.0f);
    s2->GetMaterial()->SetRefractInd(1.3f);
    s2->GetMaterial()->SetColor(Vector3<float>(0.7,0.7,1.0));
    s2->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(s2);

    //light 1
    Sphere* l1 = new Sphere(Vector3<float>(0, 5, 5), 0.5);
    l1->SetName("Light1");
    l1->SetLight(true);
    l1->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.8));
    this->object.push_back(l1);

    //light 2
    Sphere* l2 = new Sphere(Vector3<float>(-3, 5, 1), 0.5);
    l2->SetName("Light2");
    l2->SetLight(true);
    l2->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.8));
    this->object.push_back(l2);

    // extra sphere
    s1 = new Sphere(Vector3<float>(-1.5, -3.8, 1), 1.5f);
    s1->SetName("extra sphere");
    s1->GetMaterial()->SetRefract(0.8f);
    s1->GetMaterial()->SetColor(Color3(1.0,0.4,0.4));
    this->object.push_back(s1);
	
	
    //ground plane
//    Primitive* plane = new Plane(Vector3<float>(0,1,0), 4.4f);
    Primitive* plane = new Plane(Vector3<float>(0,1,0), Vector3<float>(0,-4.4,0));
    plane->SetName("Floor");
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetColor(Vector3<float>(0.4,0.3,0.3));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);
    // back plane
    plane = new Plane(Vector3<float>(0.4, 0, -1), Vector3<float>(0,0,12));
    plane->SetName("back plane");
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);

    // ceiling plane
    plane = new Plane(Vector3<float>(0, -1, 0), Vector3<float>(0,7,0));
    plane->SetName("celing plane");
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetColor(Color3(0.4f,0.7f,0.7f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);

    {
        s1 = new Sphere(Vector3<float>(-4.5f + 5*1.5f, -4.3f + 4*1.5f, 10), 0.3f);
        s1->SetName("grid sphere");
        s1->GetMaterial()->SetRefract(0.0f);
        s1->GetMaterial()->SetColor(Color3(0.3,1.0,0.4));
        this->object.push_back(s1);
    }

    {
        s1 = new Sphere(Vector3<float>(-4.5f + 6*1.5f, -4.3f + 3*1.5f, 10), 0.3f);
        s1->SetName("grid sphere");
        s1->GetMaterial()->SetRefract(0.0f);
        s1->GetMaterial()->SetColor(Color3(0.3,1.0,0.4));
        this->object.push_back(s1);
    }
	
	cam->position = Vector3<float>(0,0,-5);
	cam->direction = Vector3<float>(0,0,1);
	cam->upDirection = Vector3<float>(0,1,0);
	cam->focalLength = 0.035;
	cam->width = 0.025;
	cam->height = 0.025;

    return SC_SUCCESS;
}

#endif
#if SCENE == SCENE_CORNEL
int Scene::Init(){
	//Primitive* floor	= new Plane(Vector3<float>(0,1,0) ,Vector3<float>(0,0,0));
	//Primitive* Ceiling	= new Plane(Vector3<float>(0,-1,0),Vector3<float>(0,548.8,0));
	//Primitive* back		= new Plane(Vector3<float>(0,0,-1),Vector3<float>(0,0,559.2));
	//Primitive* left	    = new Plane(Vector3<float>(1,0,0) ,Vector3<float>(0,0,0));
	//Primitive* right	= new Plane(Vector3<float>(-1,0,0),Vector3<float>(552.8,0,0));

	
	
	Vector3<float> corners[3];
	float z = 200;
	
	corners[0] = Vector3<float>(0,0,0);
	corners[1] = Vector3<float>(0,0,560);
	corners[2] = Vector3<float>(550,0,0);
	Primitive* floor	= new Quad(new DiffuseBRDF(),corners);
	
	corners[0] = Vector3<float>(550,550,560);
	corners[1] = Vector3<float>(0,550,560);
	corners[2] = Vector3<float>(550,550,0);
	Primitive* Ceiling	= new Quad(new DiffuseBRDF(),corners);

	corners[0] = Vector3<float>(0,0,0);
	corners[1] = Vector3<float>(0,550,0);
	corners[2] = Vector3<float>(0,0,560);
	Primitive* left	    = new Quad(new DiffuseBRDF(),corners);

	corners[0] = Vector3<float>(550,550,560);
	corners[1] = Vector3<float>(550,550,0);
	corners[2] = Vector3<float>(550,0,560);
	Primitive* right	= new Quad(new DiffuseBRDF(),corners);

	corners[0] = Vector3<float>(0,0,560);
	corners[1] = Vector3<float>(0,550,560);
	corners[2] = Vector3<float>(550,0,560);
	Primitive* back	= new Quad(new DiffuseBRDF(),corners);

	
	corners[0] = Vector3<float>(343,549,227);
	corners[1] = Vector3<float>(343,549,450);
	corners[2] = Vector3<float>(180,549,227);
	Primitive* light	= new Quad(new DiffuseBRDF(),corners);//new Sphere(Vector3<float>(278,548.8,229.5),116);
	
	Primitive *sphere1 = new Sphere(new PhongBRDF(50,0.2),Vector3<float>(90,82,460),82);
	Primitive *sphere2 = new Sphere(new PhongBRDF(50,0.6),Vector3<float>(330,282,350),120);
	Primitive *sphere3 = new Sphere(new PhongBRDF(50,0.0),Vector3<float>(300,100,150),100);
	//Primitive *sphere1 = new Sphere(Vector3<float>(90,82,160),82);

	this->object.push_back(floor);
	this->object.push_back(Ceiling);
	this->object.push_back(back);
	this->object.push_back(right);
	this->object.push_back(left);
	this->object.push_back(light);
	this->object.push_back(sphere1);
	this->object.push_back(sphere2);
	this->object.push_back(sphere3);
	//this->object.push_back(quad);
	
	floor->GetMaterial()->SetColor	(Color3(1,1,1));
	Ceiling->GetMaterial()->SetColor(Color3(1,1,1));
	back->GetMaterial()->SetColor	(Color3(0.2,0.2,1));
	right->GetMaterial()->SetColor	(Color3(0.2,1,0.2));
	left->GetMaterial()->SetColor	(Color3(1,0.2,0.2));
	light->GetMaterial()->SetColor	(Color3(1,1,1));
	sphere1->GetMaterial()->SetColor	(Color3(1,1,1));
	sphere2->GetMaterial()->SetColor	(Color3(1,0,1));
	sphere3->GetMaterial()->SetColor	(Color3(1,1,1));
	
    floor->GetMaterial()->SetRefract(0.0f);
    Ceiling->GetMaterial()->SetRefract(0.0f);
    back->GetMaterial()->SetRefract(0.0f);
    right->GetMaterial()->SetRefract(0.0f);
    left->GetMaterial()->SetRefract(0.0f);

    sphere1->GetMaterial()->SetRefract(0);
    sphere2->GetMaterial()->SetRefract(0.5);
    sphere3->GetMaterial()->SetRefract(0.5);
	
	sphere2->GetMaterial()->SetRefractInd(1.5);
	sphere3->GetMaterial()->SetRefractInd(1.5);

	light->SetLight(true);

	cam->position = Vector3<float>(278,273,-800);
	cam->direction = Vector3<float>(0,0,1);
	cam->upDirection = Vector3<float>(0,1,0);
	cam->focalLength = 0.035;
	cam->width = 0.025;
	cam->height = 0.025;

	return SC_SUCCESS;
}
#endif


Scene* Scene::LoadScene(const char *filename){
	Scene *scene = new Scene();
	std::map<std::string,Material *> materials;


	std::ifstream inFile;
	inFile.open(filename);
	if(!inFile.is_open()){
		std::cerr << "Could not open file"  << filename<< std::endl;
		return 0;
	}

	char line[4096];
	while(!inFile.eof()){
		char peeked = inFile.peek();
		if(peeked == '#' || peeked == '\0'){
			inFile.getline(line,256);
			continue;
		}
		else if(peeked == 'm'){ //material
			inFile.getline(line,256,' ');
			inFile.getline(line,256,' ');
			if(line[0] == 'd'){
				DiffuseBRDF *mat = new DiffuseBRDF();
				float a,b,c;
				
				char name[256];
				inFile.getline(name,256,' ');
				
				inFile.getline(line,256,' ');
				a = atof(line);
				mat->SetRefractInd(a);

				inFile.getline(line,256,' ');
				a = atof(line);
				mat->SetRefract(a);




				inFile.getline(line,256,' ');
				a = atof(line);
				inFile.getline(line,256,' ');
				b = atof(line);
				inFile.getline(line,256);
				c = atof(line);

				mat->SetColor(Color3(a,b,c));
				materials[std::string(name)] = mat;
			}
			else if(line[0] == 'p'){
				float a,b,c;
				
				char name[256];
				inFile.getline(name,256,' ');
				
				inFile.getline(line,256,' ');
				a = atof(line);
				inFile.getline(line,256,' ');
				b = atof(line);
				PhongBRDF *mat = new PhongBRDF(a,b);
				
				
				inFile.getline(line,256,' ');
				a = atof(line);
				mat->SetRefractInd(a);

				inFile.getline(line,256,' ');
				a = atof(line);
				mat->SetRefract(a);


				inFile.getline(line,256,' ');
				a = atof(line);
				inFile.getline(line,256,' ');
				b = atof(line);
				inFile.getline(line,256);
				c = atof(line);

				mat->SetColor(Color3(a,b,c));
				materials[std::string(name)] = mat;
			}
			else{
				assert("Unkown material type" && false);
			}
		}
		else if(peeked == 'q'){ //square
			
			char material[256];
			float corner1x,corner1y,corner1z,corner2x,corner2y,corner2z,corner3x,corner3y,corner3z;
			bool light;


			
			inFile.getline(line,256,' ');
			inFile.getline(material,256,' ');

			
			inFile.getline(line,256,' ');
			corner1x = atof(line);
			inFile.getline(line,256,' ');
			corner1y = atof(line);
			inFile.getline(line,256,' ');
			corner1z = atof(line);
			
			inFile.getline(line,256,' ');
			corner2x = atof(line);
			inFile.getline(line,256,' ');
			corner2y = atof(line);
			inFile.getline(line,256,' ');
			corner2z = atof(line);
			
			inFile.getline(line,256,' ');
			corner3x = atof(line);
			inFile.getline(line,256,' ');
			corner3y = atof(line);
			inFile.getline(line,256,' ');
			corner3z = atof(line);

			
			inFile.getline(line,256);
			light = line[0] == '1';

			Vector3<float> corners[3];
			corners[0] = Vector3<float>(corner1x,corner1y,corner1z);
			corners[1] = Vector3<float>(corner2x,corner2y,corner2z);
			corners[2] = Vector3<float>(corner3x,corner3y,corner3z);

			Quad *q = new Quad(materials[std::string(material)],corners);
			q->SetLight(light);
			scene->object.push_back(q);
		}
		else if(peeked == 's'){ //sphere
			char material[256];
			float centerx,centery,centerz,radius;
			bool light;


			inFile.getline(line,256,' ');
			inFile.getline(material,256,' ');

			
			inFile.getline(line,256,' ');
			centerx = atof(line);
			inFile.getline(line,256,' ');
			centery = atof(line);
			inFile.getline(line,256,' ');
			centerz = atof(line);
			
			inFile.getline(line,256,' ');
			radius = atof(line);
			
			inFile.getline(line,256);
			light = line[0] == '1';

			Sphere *s = new Sphere(materials[std::string(material)],Vector3<float>(centerx,centery,centerz),radius);
			s->SetLight(light);
			scene->object.push_back(s);
		}
		else if(peeked == 'c'){ //cam
			inFile.getline(line,256,' ');
			//posx 
			inFile.getline(line,256,' ');
			scene->cam->position[0] = atof(line);
			//posy 
			inFile.getline(line,256,' ');
			scene->cam->position[1] = atof(line);
			//posz 
			inFile.getline(line,256,' ');
			scene->cam->position[2] = atof(line);

			//dirx 
			inFile.getline(line,256,' ');
			scene->cam->direction[0] = atof(line);
			//diry 
			inFile.getline(line,256,' ');
			scene->cam->direction[1] = atof(line);
			//dirz 
			inFile.getline(line,256,' ');
			scene->cam->direction[2] = atof(line);

			//upx 
			inFile.getline(line,256,' ');
			scene->cam->upDirection[0] = atof(line);
			//upy 
			inFile.getline(line,256,' ');
			scene->cam->upDirection[1] = atof(line);
			//upz 
			inFile.getline(line,256,' ');
			scene->cam->upDirection[2] = atof(line);
			//focalLength 
			inFile.getline(line,256,' ');
			scene->cam->focalLength = atof(line);
			//width 
			inFile.getline(line,256,' ');
			scene->cam->width = atof(line);
			//height
			inFile.getline(line,256);
			scene->cam->height = atof(line);
			continue;
		}else{
			inFile.getline(line,256);
		}
	}


	return scene;
}