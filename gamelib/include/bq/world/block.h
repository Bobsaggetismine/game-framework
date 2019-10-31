#pragma once
#include <bq/common.h>
#include <bq/util/vec.h>
namespace bq {
	class block {
	public:
		bq::v2f pos;
		bq::v2f size;
		bool isSolid = true;
		int damage = 0;
		//these two functions are virtual so that you can override the imlementation (you have custom logic, block that is variably solid depending on what touches it, ect)
		virtual bool intersects(sf::FloatRect& other){  
			sf::FloatRect rect = { pos.x, pos.y, size.x, size.y };
			return rect.intersects(other);
		}
		virtual bool contains(float x, float y) {
			sf::FloatRect rect = { pos.x, pos.y, size.x, size.y };
			return rect.contains({ x,y });
		}
		virtual void update() = 0;
		virtual void render(sf::RenderWindow&) = 0;
		virtual void interact() = 0;
	};
}