#include "RTEngine.h"



RTEngine::RTEngine()
{

}

RTEngine::RTEngine(ViewPlane* vp, Scene* sce)
{
    this->view = vp;
    this->scene = sce;

    const Rect coord = this->view->GetCoordinate();
    pdx = (coord.r - coord.l) / this->view->GetWidth();
    pdy = (coord.t - coord.b) / this->view->GetHeight();
}

RTEngine::~RTEngine()
{

}

void RTEngine::SetViewPlane(ViewPlane* vp)
{
    this->view = vp;

    const Rect coord = this->view->GetCoordinate();
    pdx = (coord.r - coord.l) / this->view->GetWidth();
    pdy = (coord.t - coord.b) / this->view->GetHeight();
}

Primitive* RTEngine::RayTrace(const Ray& iRay, Color3& oColor, int iDepth, float iRIndex, float& oDist)
{
    if(iDepth > TRACEDEPTH) return 0; // TRACEDEPTH = 6

    oDist = std::numeric_limits<float>::max();
    Vector3<float> pInts;
    Primitive* object = NULL;
    int ret;
    // find nearest intersection object.
    for(unsigned int i = 0; i < this->scene->GetNumObject(); i++)
    {
        Primitive* tmpObj = this->scene->GetObject(i);
        int tmpRet = tmpObj->Intersect(iRay, oDist);
        if(tmpRet)
        {
            object = tmpObj;
            ret = tmpRet;
        }
    }
    // no hit
    if(!object)
    {
        oColor = this->scene->GetBGColor();
        return 0;
    }

    if(object->IsLight())
    {
        oColor = object->GetMaterial()->GetColor();
		return object;
    }
    else
    {
        // p = o + dt;
        pInts = iRay.GetOrigin() + (iRay.GetDir() * oDist );
        // trace back to light
        // find shadow and local illumination
        unsigned int numObject = this->scene->GetNumObject();
        for(unsigned int i = 0; i < numObject ; i++)
        {
            Primitive* light = this->scene->GetObject(i);
            if(light->IsLight())
            {
                // calculate shadow
                float shade = 1.0f;
                if(light->GetType() == SPHERE)
                {
                    // setup a ray to light then find intersection point between the ray
                    // if the intersection is found along the ray, then it is shadow.
                    Vector3<float> lightDir = ((Sphere*)light)->GetCenter() - pInts;
                    float tdist = lightDir.Length();
                    lightDir *= (1.0f / tdist);
                    Ray rayToLight = Ray(pInts + lightDir*EPSILON, lightDir);
                    for(unsigned int j = 0; j < numObject; j++)
                    {
                        Primitive* tmpPrim = this->scene->GetObject(j);
                        if((tmpPrim != light) && (tmpPrim->Intersect(rayToLight, tdist)))
                        {
                            shade = 0.0f;
                            break;
                        }
                    }
					if(shade > EPSILON){
						oColor = light->GetMaterial()->GetColor() * object->GetMaterial()->BRDF(pInts,iRay.GetDir(),object->GetNormal(pInts),rayToLight.GetDir());
					}
                }

            }
        }
        // add reflecting
        float reflect = object->GetMaterial()->GetReflect();
        if(true)
        {
            Vector3<float> normal = object->GetNormal(pInts);
            //Vector3<float> reflectRay = iRay.GetDir() -  normal *(2.0f * (Dot(iRay.GetDir(), normal)));
			Ray oRay;
			Color3 reflectance = object->GetMaterial()->randomReflection(pInts,iRay.GetDir(),normal,oRay);
            if(iDepth < TRACEDEPTH)
            {
                Color3 colorRefl(0,0,0);
                float tmpDist;
              //  this->RayTrace(Ray(pInts + reflectRay*EPSILON, reflectRay), colorRefl, iDepth+1, iRIndex, tmpDist);
				this->RayTrace(Ray(oRay.GetOrigin() + oRay.GetDir()*EPSILON, oRay.GetDir()), colorRefl, iDepth+1, iRIndex, tmpDist);
				oColor += reflectance*colorRefl;
                //oColor +=  (object->GetMaterial()->GetColor() * colorRefl) * reflect;
            }
        }
        //// add refracting
        float refract = object->GetMaterial()->GetRefract();
        if((refract > 0) && (iDepth < TRACEDEPTH) )
        {
            float rIndex = object->GetMaterial()->GetRefractInd();
            float n = iRIndex / rIndex;
            Vector3<float> normal = object->GetNormal(pInts) * (float)ret;
            float cosI = -Dot(normal, iRay.GetDir());
            float cosT2 = 1.0f - n*n*(1.0f - cosI * cosI);
            if(cosT2 > 0.0f)
            {
                Vector3<float> T = (iRay.GetDir()*n) + (normal*(n*cosI-sqrtf(cosT2)));
                Color3 colorRefr(0,0,0);
                float tmpDist;
                this->RayTrace(Ray(pInts + T*EPSILON,T), colorRefr, iDepth+1, rIndex, tmpDist);
                // Beer's law
                Color3 absorb = object->GetMaterial()->GetColor() * 0.15 * (-tmpDist);
                Color3 transparancy(expf(absorb[0]), expf(absorb[1]), expf(absorb[2]));
                oColor += colorRefr * transparancy;
            }
        }

    }
    return object;
}

void RTEngine::InitRender()
{

}

bool RTEngine::Render()
{
    Vector3<float> camera(0,0,-5);
    unsigned int height = this->view->GetHeight();
    unsigned int width = this->view->GetWidth();
    const Rect coord = this->view->GetCoordinate();
   // float psx, psy;
    // psy, psx : running variable for each pixel
    // it is a position on an image plane
    // notice that it runs from bottom left
 //   psy = coord.b;
    for(unsigned int y = 0; y < height; y++)
    {
		std::cout << y / (0.01f * height) << "%" << std::endl;
		#pragma omp parallel for
        for(int x = 0; x < width; x++)
        {
			Vector3<float> pColor;
            for(int i = 0;i<SAMPLES_PER_PIXEL;i++){
				float rx = rand()/(float)RAND_MAX;
				float ry = rand()/(float)RAND_MAX;
				float psx = coord.l + (rx+x)*pdx;
				float psy = coord.b + (ry+y)*pdy;
				// setting up a ray
				Vector3<float> dir = Vector3<float>(psx, psy, 0.0) - camera;
				dir.Normalize();
				Ray ray(camera,dir);
				// tracing the ray
				float dist;
				Vector3<float> tmpColor;
				this->RayTrace(ray, tmpColor, 1, 1.0, dist);
				pColor += tmpColor;
			}
			this->view->SetColor(pColor/SAMPLES_PER_PIXEL, x, y);
			//std::cout << "Pixel " << x << " " << y  << " done!" << std::endl;
           // psx += pdx;
        }
      //  psy += pdy;
    }
    return true;
}

