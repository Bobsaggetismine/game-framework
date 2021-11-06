#include "bqpch.h"

#include <bq/util/random.h>

float bq::random::getRandomInternal(float start, float end) {
	return start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (end - start)));
}

float bq::random::getRandom(float start, float end) {
	return get().getRandomInternal(start, end);
}
bq::random::random() {
	srand(static_cast<unsigned int>(time(NULL)));
}