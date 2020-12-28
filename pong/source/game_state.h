
#include <bq.h>


class game_state : public bq::state {
public:
	game_state();
	void render(bq::window&) override;
	void update() override;
	void handleEvents(bq::event&, bq::window&) override;

};