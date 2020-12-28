#pragma once


namespace bq {
	struct v2f;
	class entity;
	class window;

	class camera {
		bq::entity* m_target;
		bq::v2f m_size;
		sf::View m_view;
	public:
		
		camera(bq::entity*);

		void render(bq::window&) const;
		const sf::View& view() const;
		void update();
		void reset();
	};
}