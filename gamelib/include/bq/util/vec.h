#pragma once
#include <SFML/System/Vector2.hpp>
namespace bq {
	struct v2f {
		v2f(const float _x, const float _y) :x(_x), y(_y) {}
		v2f() : x(0), y(0) {}
		float x, y;

		void operator +=(const v2f& other) { x += other.x; y += other.y; }
		//seemless operability with sf::Vector
		v2f(const sf::Vector2f& sfv): x(sfv.x), y(sfv.y) {}
		operator sf::Vector2f () {
			return sf::Vector2f(x, y);
		}
	};

	struct v2i {
		v2i(const int _x, const int _y) : x(_x), y(_y) {}
		v2i() : x(0), y(0) {}
		int x, y;

		void operator +=(const v2i& other) { x += other.x; y += other.y; }

		//seemless operability with sf::Vector
		v2i(const sf::Vector2i& sfv):x(sfv.x), y(sfv.y) {}
		operator sf::Vector2i() {
			return sf::Vector2i(x,y);
		}
	};
};

