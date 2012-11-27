#include "includes.h"



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
    if(iDepth > TRACEDEPTH) return 0;
	assert(floatEquals(iRay.GetDir().Length2(),1));


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
	
	float localLight = 0.3;

    pInts = iRay.GetOrigin() + (iRay.GetDir() * oDist );

    if(object->IsLight())
    {
		float d = 1;
		if(object->GetType() == SPHERE){
			assert(floatEquals(iRay.GetDir().Length2(),1));
			assert(floatEquals(object->GetNormal(pInts).Length2(),1));
			if(object->GetType() == SPHERE){
				d = Dot(Vector3<float>()-iRay.GetDir() , object->GetNormal(pInts));
				d *= 0.2;
				d += 1-0.2;
			}
		}
        oColor = object->GetMaterial()->GetColor() * d;
		return object;
    }
    else
    {
        // p = o + dt;
        // trace back to light
        // find shadow and local illumination
        unsigned int numObject = this->scene->GetNumObject();
        for(unsigned int i = 0; i < numObject; i++)
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
                    Ray rayToLight = Ray(pInts, lightDir);
					rayToLight.SetOriginObject(object);
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
						Ray rayFromLight;
						float radius = dynamic_cast<Sphere *>(light)->GetRadius();
						light->GetMaterial()->randomReflection(rayToLight.GetOrigin() + rayToLight.GetDir() * tdist,rayToLight.GetDir(),rayToLight.GetDir(),rayFromLight);
						Vector3<float> posOnLight = rayFromLight.GetOrigin() + rayFromLight.GetDir() * radius;
						Vector3<float> dirToLight = posOnLight - pInts;
						dirToLight.Normalize();
						float d = Dot(dirToLight,rayFromLight.GetDir());
						oColor += light->GetMaterial()->GetColor() * 
								  object->GetMaterial()->BRDF(pInts,iRay.GetDir(),object->GetNormal(pInts),dirToLight) *
								  d*localLight;//iDepth / (float)TRACEDEPTH;
					}
				}else if(light->GetType() == QUAD){
                    Quad* quad = dynamic_cast<Quad*>(light);
					Vector3<float> dirToLight = quad->getRandomPointOnSurface() - pInts;
					
					float tdist = dirToLight.Length();
                    dirToLight *= (1.0f / tdist);
                    Ray rayToLight = Ray(pInts, dirToLight);
					rayToLight.SetOriginObject(object);
                    for(unsigned int j = 0; j < numObject; j++)
                    {
                        Primitive* tmpPrim = this->scene->GetObject(j);
                        if((tmpPrim != light) && (tmpPrim->Intersect(rayToLight, tdist)))
                        {
                            shade = 0.0f;
                            break;
                        }
                    }
					if(shade > EPSILON)
						oColor += light->GetMaterial()->GetColor() * object->GetMaterial()->BRDF(pInts,Vector3<float>()-iRay.GetDir(),object->GetNormal(pInts),dirToLight)*localLight;
				}

            }
        }
        // add reflecting
        //float reflect = object->GetMaterial()->GetReflect();
        float refract = object->GetMaterial()->GetRefract();

		if((refract > 0) && (iDepth < TRACEDEPTH) )
        {
            float rIndex = object->GetMaterial()->GetRefractInd();
			if(ret==-1)
				rIndex = 1.0/rIndex;
            float n = iRIndex / rIndex;
            Vector3<float> normal = object->GetNormal(pInts) * (float)ret;
			
            float cosI = -Dot(normal, iRay.GetDir());
            float cosT2 = 1.0f - n*n*(1.0f - cosI * cosI);
            if(cosT2 > 0.0f){
                Vector3<float> T = (iRay.GetDir()*n) + (normal*(n*cosI-sqrtf(cosT2)));
                Color3 colorRefr(0,0,0);
                float tmpDist;
				Ray ray(pInts,T);
				ray.SetOriginObject(object);
                this->RayTrace(ray, colorRefr, iDepth+1, rIndex, tmpDist);
                // Beer's law
                Color3 absorb = object->GetMaterial()->GetColor();// * 0.15 * (-tmpDist);
                Color3 transparancy(expf(absorb[0]), expf(absorb[1]), expf(absorb[2]));
                oColor += colorRefr * transparancy*(1-localLight)*(refract);
			}else{
				refract = 0;
			}
        }

        if(refract != 1)
        {
            Vector3<float> normal = object->GetNormal(pInts);

			Ray oRay;
			Color3 reflectance = object->GetMaterial()->randomReflection(pInts,iRay.GetDir(),normal,oRay);
            if(iDepth < TRACEDEPTH && (reflectance[0] != 0 || reflectance[1] != 0 || reflectance[2] != 0))
            {
                Color3 colorRefl(0,0,0);
                float tmpDist;
				Ray ray(oRay.GetOrigin(), oRay.GetDir());
				ray.SetOriginObject(object);
				if(this->RayTrace(ray, colorRefl, iDepth+1, iRIndex, tmpDist))
					oColor += reflectance*colorRefl*(1-localLight)*(1-refract);
            }
        }
        //// add refracting
        

    }
    return object;
}

void RTEngine::InitRender()
{

}


bool RTEngine::Render()
{
    unsigned int height = this->view->GetHeight();
    unsigned int width = this->view->GetWidth();
	float dpx,dpy;
	dpx = 1.0/width;
	dpy = 1.0/height;

	GetScene()->getCamera()->setAspectRatio(height/(float)width);

    for(unsigned int y = 0; y < height; y++)
    {
		std::cout << y / (0.01f * height) << "%" << std::endl;

		float py = y / (float)height;
		

		#pragma omp parallel for
        for(int x = 0; x < width; x++)
        {
			float f = RandomGenerator::GetRandom();
			float px = x / (float)width;
			Vector3<float> pColor;
            for(int i = 0;i<SAMPLES_PER_PIXEL;i++){
				float ox = dpx * rand()/(float)RAND_MAX;
				float oy = dpy * rand()/(float)RAND_MAX;

				Ray ray = GetScene()->getCamera()->RayToPixel(px+ox, py+oy);

				// tracing the ray
				float dist;
				Vector3<float> tmpColor;
				this->RayTrace(ray, tmpColor, 1, 1.0, dist);
				pColor += tmpColor;
			}
			this->view->SetColor(pColor/SAMPLES_PER_PIXEL, x, y);
			//this->view->SetColor(pColor, x, y);
        }
    }
    return true;
}

