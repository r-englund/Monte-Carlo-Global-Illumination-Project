#pragma once

class RandomGenerator
{
	RandomGenerator(void);
	~RandomGenerator(void);

	static std::map<int,bool> seeded;
public:
	static float GetRandom();
};

