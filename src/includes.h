#ifndef __INCLUDES_H__
#define __INCLUDES_H__


#include <iostream>
#include <cstring>
#include <ctime>
#include <cassert>
#include <vector>
#include <cstdint>
#include <cmath>
#include <limits>
#include <map>
#include <omp.h>


#include <cstdlib> //Needed? it is not needed for me in vs 2010 

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//#define OMP_NUM_THREADS 8

//#define SAMPLES_PER_PIXEL 10
//#define TRACEDEPTH     5

//#define WIDTH			800
//#define HEIGHT			800

#define EPSILON         0.001

#define SCENE_OUR		1
#define SCENE_CORNEL	2
#define SCENE_OUR_OLD	3
#define SCENE SCENE_CORNEL     

bool floatEquals(float a,float b,float e = EPSILON); 

#include "RandomGenerator.h"

#include "Vector3.h"
typedef Vector3<float> Color3;
#include "Ray.h"

#include "BRDF.h"

#include "Primitive.h"
#include "Plane.h"
#include "Sphere.h"
#include "Quad.h"

#include "BMPWriter.h"
#include "Camera.h"
#include "Scene.h"
#include "ViewPlane.h"
#include "RTEngine.h"


#endif
