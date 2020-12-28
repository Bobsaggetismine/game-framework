
#include <bq.h>


class game_state : public bq::state {
public:
	game_state();
	void render(sf::RenderWindow&) override;
	void update() override;
	void handleEvents(bq::event&, sf::RenderWindow&) override;

};