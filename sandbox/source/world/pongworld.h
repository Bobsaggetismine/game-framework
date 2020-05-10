#pragma once

class pongworld : public bq::world {
	sf::Sprite background;
	bq::astar::pathfinder m_generator;
public:
	pongworld();
	virtual std::unique_ptr<std::vector<bq::v2i>> get_path(bq::v2i, bq::v2i) override;
};