#pragma once

namespace bq {
	class window;
	class block {
	protected:
		bq::v2f m_pos;
		bq::v2f m_size;
		bool m_solid = true;
		size_t m_damage = 0;
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
		virtual void render(bq::window&) = 0;
		virtual void interact() = 0;
		size_t damage() const;
		bool solid() const;
		bq::v2f pos() const;
		bq::v2f size() const;
	};
}