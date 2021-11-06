#pragma once

namespace bq {
	class random {
		random();
		float getRandomInternal(float start, float end);
	public:
		static random& get() {
			static random r;
			return r;
		}
		static float getRandom(float start, float end);
		
	};
}

