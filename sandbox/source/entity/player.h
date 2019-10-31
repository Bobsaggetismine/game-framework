#include <bq.h>
#include "../world/pongworld.h"
#include "../States/menu_state.h"

#include "bullet.h"


class player : public bq::entity {
	bq::animation upAnimation;
	bq::animation downAnimation;
	bq::animation leftAnimation;
	bq::animation rightAnimation;
	sf::Sprite curSprite;
	int hp = 100;
	bq::v2f interactPoint = { -11, -11 };
public:
	player();
	void update() override;
	void render(sf::RenderWindow&) override;
	void handleEvent(sf::Event&)   override;
	void input();
};