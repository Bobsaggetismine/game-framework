#pragma once

namespace bq {

	struct buff;
	struct v2f;

	class entity {
	protected:
		size_t m_id = 0;
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
		virtual bool should_cull(const sf::View&) const;
		virtual bool intersects(sf::FloatRect&);
		void move(bq::v2f& other);
		const bq::v2f& pos() const;
		const bq::v2f& size()const;
		const size_t& id() const;
		virtual ~entity() = 0;
	};
}