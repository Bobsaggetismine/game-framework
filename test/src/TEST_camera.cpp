#include <boost/test/auto_unit_test.hpp>

#include <bq.h>


class test_entity : public bq::entity {
public:
	test_entity() {
		m_pos.x = 400;
		m_pos.y = 400;
	}
	void update() override {
		m_pos += bq::v2f(1,1);
	}
	//since this is a test entity we dont have a window to generate events or render, these functions should never get called, in this specific situation i am explicitly not calling them
	void render(sf::RenderWindow&) override {}
	void handle_event(sf::Event&)   override {}
	void damage(float) override {}
	void interact() override {}
};

BOOST_AUTO_TEST_CASE(test_camera_construction) {

	std::shared_ptr<bq::entity> e = std::make_shared<test_entity>();
	bq::camera cam(e);
	bq::v2f pos(1920, 1080);
	BOOST_CHECK(cam.m_view.getSize().x == pos.x);
	BOOST_CHECK(cam.m_view.getSize().y == pos.y);
}
BOOST_AUTO_TEST_CASE(test_camera_update) {
	std::shared_ptr<bq::entity> e = std::make_shared<test_entity>();
	bq::camera cam(e);

	for (unsigned i = 0; i < 100; ++i) {
		e->update();
		cam.update();
		BOOST_CHECK(cam.m_view.getCenter().x == e->m_pos.x);
		BOOST_CHECK(cam.m_view.getCenter().y == e->m_pos.y);
	}
}