#include "Scene.h"

Scene::Scene()
{
    bgColor = Color3(0.5,0.3,0.3);
}

Scene::~Scene()
{
    for(unsigned int i = 0; i < this->object.size(); i++)
    {
        if(this->object[i])
            delete this->object[i];
    }
}

int Scene::Init()
{

    //sphere 1
    Sphere* s1 = new Sphere(Vector3<float>(2.0,0.8,3), 2.5f);
    s1->SetName("big Sphere1");
    s1->GetMaterial()->SetReflect(0.2f);
    s1->GetMaterial()->SetRefract(0.8f);
    s1->GetMaterial()->SetRefractInd(1.3f);
    s1->GetMaterial()->SetColor(Vector3<float>(0.2,0.2,0.2));
    s1->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(s1);

    //sphere 2
    Sphere* s2 = new Sphere(Vector3<float>(-5.5, -0.5, 7), 2.0);
    s2->SetName("small Sphere2");
    s2->GetMaterial()->SetReflect(0.5f);
    s2->GetMaterial()->SetRefract(0.0f);
    s2->GetMaterial()->SetRefractInd(1.3f);
    s2->GetMaterial()->SetDiffuse(0.1f);
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
    s1->GetMaterial()->SetReflect(0.0f);
    s1->GetMaterial()->SetRefract(0.8f);
    s1->GetMaterial()->SetColor(Color3(1.0,0.4,0.4));
    this->object.push_back(s1);
	
	
    //ground plane
//    Primitive* plane = new Plane(Vector3<float>(0,1,0), 4.4f);
    Primitive* plane = new Plane(Vector3<float>(0,1,0), Vector3<float>(0,-4.4,0));
    plane->SetName("Floor");
    plane->GetMaterial()->SetReflect(0.0f);
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetDiffuse(1.0f);
    plane->GetMaterial()->SetColor(Vector3<float>(0.4,0.3,0.3));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);
    // back plane
    plane = new Plane(Vector3<float>(0, 0, -1), Vector3<float>(0,0,12));
    plane->SetName("back plane");
    plane->GetMaterial()->SetReflect(0.0f);
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetSpecular(0);
    plane->GetMaterial()->SetDiffuse(0.6f);
    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);
	
    // behind us plane
    plane = new Plane(Vector3<float>(0, 0, 1), Vector3<float>(0,0,-8));
    plane->SetName("behind us plane");
    plane->GetMaterial()->SetReflect(0.0f);
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetSpecular(0);
    plane->GetMaterial()->SetDiffuse(0.6f);
    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);

    // right plane
    plane = new Plane(Vector3<float>(-1, 0, 0), Vector3<float>(8,0,0));
    plane->SetName("right plane");
    plane->GetMaterial()->SetReflect(0.0f);
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetSpecular(0);
    plane->GetMaterial()->SetDiffuse(0.6f);
    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
    plane->GetMaterial()->SetColor(Vector3<float>(1.0,0.6,0.6));
    this->object.push_back(plane);

    // left plane
    plane = new Plane(Vector3<float>(1, 0, 0), Vector3<float>(-8,0,0));
    plane->SetName("left plane");
    plane->GetMaterial()->SetReflect(0.0f);
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetSpecular(0);
    plane->GetMaterial()->SetDiffuse(0.6f);
    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,1.0,0.6));
    this->object.push_back(plane);

    // ceiling plane
    plane = new Plane(Vector3<float>(0, -1, 0), Vector3<float>(0,7,0));
    plane->SetName("celing plane");
    plane->GetMaterial()->SetReflect(0.0f);
    plane->GetMaterial()->SetRefract(0.0f);
    plane->GetMaterial()->SetSpecular(0);
    plane->GetMaterial()->SetDiffuse(0.5f);
    plane->GetMaterial()->SetColor(Color3(0.4f,0.7f,0.7f));
    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
    this->object.push_back(plane);

    {
        s1 = new Sphere(Vector3<float>(-4.5f + 5*1.5f, -4.3f + 4*1.5f, 10), 0.3f);
        s1->SetName("grid sphere");
        s1->GetMaterial()->SetReflect(0.0f);
        s1->GetMaterial()->SetRefract(0.0f);
        s1->GetMaterial()->SetSpecular(0.6f);
        s1->GetMaterial()->SetDiffuse(0.6f);
        s1->GetMaterial()->SetColor(Color3(0.3,1.0,0.4));
        this->object.push_back(s1);
    }

    {
        s1 = new Sphere(Vector3<float>(-4.5f + 6*1.5f, -4.3f + 3*1.5f, 10), 0.3f);
        s1->SetName("grid sphere");
        s1->GetMaterial()->SetReflect(0.0f);
        s1->GetMaterial()->SetRefract(0.0f);
        s1->GetMaterial()->SetSpecular(0.6f);
        s1->GetMaterial()->SetDiffuse(0.6f);
        s1->GetMaterial()->SetColor(Color3(0.3,1.0,0.4));
        this->object.push_back(s1);
    }


    return SC_SUCCESS;
}
//
//int Scene::Init_old()
//{
//
//    //sphere 1
//    Sphere* s1 = new Sphere(Vector3<float>(2.0,0.8,3), 2.5f);
//    s1->SetName("big Sphere1");
//    s1->GetMaterial()->SetReflect(0.2f);
//    s1->GetMaterial()->SetRefract(0.8f);
//    s1->GetMaterial()->SetRefractInd(1.3f);
//    s1->GetMaterial()->SetColor(Vector3<float>(0.2,0.2,0.2));
//    s1->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
//    this->object.push_back(s1);
//
//    //sphere 2
//    Sphere* s2 = new Sphere(Vector3<float>(-5.5, -0.5, 7), 2.0);
//    s2->SetName("small Sphere2");
//    s2->GetMaterial()->SetReflect(0.5f);
//    s2->GetMaterial()->SetRefract(0.0f);
//    s2->GetMaterial()->SetRefractInd(1.3f);
//    s2->GetMaterial()->SetDiffuse(0.1f);
//    s2->GetMaterial()->SetColor(Vector3<float>(0.7,0.7,1.0));
//    s2->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
//    this->object.push_back(s2);
//
//    //light 1
//    Sphere* l1 = new Sphere(Vector3<float>(0, 5, 5), 0.5);
//    l1->SetName("Light1");
//    l1->SetLight(true);
//    l1->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.8));
//    this->object.push_back(l1);
//
//    //light 2
//    Sphere* l2 = new Sphere(Vector3<float>(-3, 5, 1), 0.5);
//    l2->SetName("Light2");
//    l2->SetLight(true);
//    l2->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.8));
//    this->object.push_back(l2);
//
//    // extra sphere
//    s1 = new Sphere(Vector3<float>(-1.5, -3.8, 1), 1.5f);
//    s1->SetName("extra sphere");
//    s1->GetMaterial()->SetReflect(0.0f);
//    s1->GetMaterial()->SetRefract(0.8f);
//    s1->GetMaterial()->SetColor(Color3(1.0,0.4,0.4));
//    this->object.push_back(s1);
//	
//	
//    //ground plane
////    Primitive* plane = new Plane(Vector3<float>(0,1,0), 4.4f);
//    Primitive* plane = new Plane(Vector3<float>(0,1,0), Vector3<float>(0,-4.4,0));
//    plane->SetName("Floor");
//    plane->GetMaterial()->SetReflect(0.0f);
//    plane->GetMaterial()->SetRefract(0.0f);
//    plane->GetMaterial()->SetDiffuse(1.0f);
//    plane->GetMaterial()->SetColor(Vector3<float>(0.4,0.3,0.3));
//    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
//    this->object.push_back(plane);
//    // back plane
//    plane = new Plane(Vector3<float>(0.4, 0, -1), Vector3<float>(0,0,12));
//    plane->SetName("back plane");
//    plane->GetMaterial()->SetReflect(0.0f);
//    plane->GetMaterial()->SetRefract(0.0f);
//    plane->GetMaterial()->SetSpecular(0);
//    plane->GetMaterial()->SetDiffuse(0.6f);
//    plane->GetMaterial()->SetColor(Color3(0.5f,0.3f,0.5f));
//    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
//    this->object.push_back(plane);
//
//    // ceiling plane
//    plane = new Plane(Vector3<float>(0, -1, 0), Vector3<float>(0,7,0));
//    plane->SetName("celing plane");
//    plane->GetMaterial()->SetReflect(0.0f);
//    plane->GetMaterial()->SetRefract(0.0f);
//    plane->GetMaterial()->SetSpecular(0);
//    plane->GetMaterial()->SetDiffuse(0.5f);
//    plane->GetMaterial()->SetColor(Color3(0.4f,0.7f,0.7f));
//    plane->GetMaterial()->SetColor(Vector3<float>(0.6,0.6,0.6));
//    this->object.push_back(plane);
//
//    {
//        s1 = new Sphere(Vector3<float>(-4.5f + 5*1.5f, -4.3f + 4*1.5f, 10), 0.3f);
//        s1->SetName("grid sphere");
//        s1->GetMaterial()->SetReflect(0.0f);
//        s1->GetMaterial()->SetRefract(0.0f);
//        s1->GetMaterial()->SetSpecular(0.6f);
//        s1->GetMaterial()->SetDiffuse(0.6f);
//        s1->GetMaterial()->SetColor(Color3(0.3,1.0,0.4));
//        this->object.push_back(s1);
//    }
//
//    {
//        s1 = new Sphere(Vector3<float>(-4.5f + 6*1.5f, -4.3f + 3*1.5f, 10), 0.3f);
//        s1->SetName("grid sphere");
//        s1->GetMaterial()->SetReflect(0.0f);
//        s1->GetMaterial()->SetRefract(0.0f);
//        s1->GetMaterial()->SetSpecular(0.6f);
//        s1->GetMaterial()->SetDiffuse(0.6f);
//        s1->GetMaterial()->SetColor(Color3(0.3,1.0,0.4));
//        this->object.push_back(s1);
//    }
//
//
//    return SC_SUCCESS;
//}
