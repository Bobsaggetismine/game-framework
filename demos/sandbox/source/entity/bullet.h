#pragma once

class bullet : public bq::entity {
	bq::sprite sprite;
	bq::v2f speed;
	bool m_dead = false;
	sf::Sound sound;
	int m_damage = 20;
public:
	void update() override;
	void render(bq::window&)override;
	void handle_event(bq::event&) override;
	virtual bool should_cull(const sf::View&) const override;
	void damage(float) override;
	bullet(bq::v2f,bq::v2f);
	virtual ~bullet() override;
	bool intersects(sf::FloatRect&) override;
	virtual void interact() override;
};