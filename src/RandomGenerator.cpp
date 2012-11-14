#include "includes.h"


std::map<int,bool> RandomGenerator::seeded;

RandomGenerator::RandomGenerator(void)
{
}


RandomGenerator::~RandomGenerator(void)
{
}

float RandomGenerator::GetRandom(){
	int thread = omp_get_thread_num();
	if(!seeded[thread]){
		seeded[thread]= true;
		srand((unsigned)time(0));
	}
	return rand() / (float) RAND_MAX;
}
