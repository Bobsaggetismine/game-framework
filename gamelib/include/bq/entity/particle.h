#pragma once




namespace bq {
	struct v2f;
	class entity;
	class particle : public bq::entity {
		sf::Clock m_life_timer;
		sf::Sprite m_sprite;
		bq::v2f m_movement = { 2,2 };
		float m_life = 0;
	public:
		particle(float, float, float);
		void render(sf::RenderWindow&) override;
		void update() override;
		void handle_event(sf::Event&) override;
		void damage(float) override;
		bool should_cull(const sf::View&) const override;
		bool intersects(sf::FloatRect&) override;
		void interact() override;
	};
}
