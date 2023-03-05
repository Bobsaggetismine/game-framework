#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>
namespace bq {
	struct v2f {
		v2f(const float _x, const float _y) :x(_x), y(_y) {}
		v2f() : x(0), y(0) {}
		//break the naming convention for this project here, not using m_ because it feels weird to say vec.m_x
		float x, y;

		void operator +=(const v2f& other) { x += other.x; y += other.y; }
		//seemless operability with sf::Vector
		v2f(const sf::Vector2f& sfv): x(sfv.x), y(sfv.y) {}
		operator sf::Vector2f () const {
			return sf::Vector2f(x, y);
		}
		bool operator==(const v2f& other) {
			bool xclose = fabs((double)other.x - x) < 0.001f;
			bool yclose = fabs((double)other.y - y) < 0.001f;
			return (xclose && yclose); 
		}
		bq::v2f operator+(const v2f& other) {
			bq::v2f newVec = { 0,0 };
			newVec += other;
			newVec += *this;
			return newVec;
		}
		void normalize() {
			float mag_x = x * x;
			float mag_y = y * y;
			float mag = sqrtf(mag_y + mag_x);
			x /= mag;
			y /= mag;
		}
	};

	struct v2i {
		v2i(const int _x, const int _y) : x(_x), y(_y) {}
		v2i() : x(0), y(0) {}
		int x, y;

		void operator +=(const v2i& other) { x += other.x; y += other.y; }
		bool operator ==(const v2i& other) { return (x == other.x && y == other.y); }
		
		//seemless operability with sf::Vector
		v2i(const sf::Vector2i& sfv):x(sfv.x), y(sfv.y) {}
		operator sf::Vector2i() const {
			return sf::Vector2i(x,y);
		}
	};

	struct v4i {
		v4i(const int _x, const int _y, const int _z, const int _t) : x(_x), y(_y),z(_z),t(_t) {}
		v4i() : x(0), y(0), z(0), t(0) {}
		int x, y, z, t;

		void operator +=(const v4i& other) { x += other.x; y += other.y; z += other.z; t += other.t; }
		bool operator ==(const v4i& other) { return (x == other.x && y == other.y && z == other.z && t == other.t); }
		
	};

	bq::v2i operator +(const v2i& first, const v2i& second);
};

