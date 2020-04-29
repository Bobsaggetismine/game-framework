#pragma once
#include <bq/common.h>
#include <bq/util/vec.h>
#include <bq/core/buff.h>
namespace bq {
	class entity {
	protected:
		int m_id = 0;
		bq::v2f m_pos;
		bq::v2f m_size;
	public:
		virtual void update() = 0;
		virtual void render(sf::RenderWindow&) = 0;
		virtual void handle_event(sf::Event&) = 0;
		virtual void damage(float) = 0;
		virtual void interact() = 0;
		virtual void buff(bq::buff);
		virtual void unbuff();
		virtual bool should_cull(const sf::View&);
		virtual bool intersects(sf::FloatRect&);
		void move(bq::v2f& other);
		bq::v2f& pos();
		bq::v2f& size();
		const int id();
		virtual ~entity() = 0;
	};
}