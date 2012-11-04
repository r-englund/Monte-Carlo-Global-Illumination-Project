#include "includes.h"

Scene::Scene()
{
    bgColor = Color3(0.5,0.3,0.3);
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
	Primitive* floor	= new Plane(Vector3<float>(0,1,0) ,Vector3<float>(0,0,0));
	Primitive* Ceiling	= new Plane(Vector3<float>(0,-1,0),Vector3<float>(0,548.8,0));
	Primitive* back		= new Plane(Vector3<float>(0,0,-1),Vector3<float>(0,0,559.2));
	Primitive* left	    = new Plane(Vector3<float>(1,0,0) ,Vector3<float>(0,0,0));
	Primitive* right	= new Plane(Vector3<float>(-1,0,0),Vector3<float>(552.8,0,0));
	Primitive* light	= new Sphere(Vector3<float>(278,548.8,229.5),116);
	
	this->object.push_back(floor);
	this->object.push_back(Ceiling);
	this->object.push_back(back);
	this->object.push_back(right);
	this->object.push_back(left);
	this->object.push_back(light);
	
	floor->GetMaterial()->SetColor	(Color3(1,1,1));
	Ceiling->GetMaterial()->SetColor(Color3(1,1,1));
	back->GetMaterial()->SetColor	(Color3(1,1,1));
	right->GetMaterial()->SetColor	(Color3(0,1,0));
	left->GetMaterial()->SetColor	(Color3(1,0,0));
	light->GetMaterial()->SetColor	(Color3(1,1,1));
	
    floor->GetMaterial()->SetRefract(0.0f);
	
    Ceiling->GetMaterial()->SetRefract(0.0f);
	
    back->GetMaterial()->SetRefract(0.0f);
	
    right->GetMaterial()->SetRefract(0.0f);
	
    left->GetMaterial()->SetRefract(0.0f);
	
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