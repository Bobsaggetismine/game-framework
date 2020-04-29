#pragma once
#include <bq/common.h>
#include <bq/util/vec.h>
namespace bq {
	class block {
	protected:
		bq::v2f m_pos;
		bq::v2f m_size;
		bool m_solid = true;
		int m_damage = 0;
	public:
		
		virtual bool intersects(sf::FloatRect& other){  
			sf::FloatRect rect = { m_pos.x, m_pos.y, m_size.x, m_size.y };
			return rect.intersects(other);
		}
		virtual bool contains(float x, float y) {
			sf::FloatRect rect = { m_pos.x, m_pos.y, m_size.x, m_size.y };
			return rect.contains({ x,y });
		}
		virtual void update() = 0;
		virtual void render(sf::RenderWindow&) = 0;
		virtual void interact() = 0;
		int damage() const;
		bool solid() const;
		bq::v2f pos() const;
		bq::v2f size() const;
	};
}