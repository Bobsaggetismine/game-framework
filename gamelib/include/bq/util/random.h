#pragma once
#include <random>
#include <ctime>
namespace bq {
class random {
public:
	static void init() {
		srand(static_cast<unsigned int>(time(NULL)));
	}
	static float getRandom(float start, float end) {
		return start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (end - start)));
	}
};
}

