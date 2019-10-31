#include <bq/core/camera.h>
#include <bq/core/handler.h>
void bq::camera::render(sf::RenderWindow& window) {
	window.setView(view);
}

void bq::camera::update() {
	view.setCenter( target->pos );
}

bq::camera::camera(std::shared_ptr<bq::entity> e):target(e){
	view.setSize(1920.f, 1080.f);
}
