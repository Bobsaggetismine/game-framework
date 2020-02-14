#pragma once
#include <random>
#include <ctime>
namespace bq {
	class random {
		random() {
			srand(static_cast<unsigned int>(time(NULL)));
		}
		float getRandomInternal(float start, float end) {
			return start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (end - start)));
		}
	public:
		static random& get() {
			static random r;
			return r;
		}
		static float getRandom(float start, float end) {
			return get().getRandomInternal(start, end);
		}
		
	};
}

