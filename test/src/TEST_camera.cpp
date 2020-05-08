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
	void render(sf::RenderWindow&) override {}
	void handle_event(sf::Event&)   override {}
	void damage(float) override {}
	void interact() override {}
	bool should_cull(const sf::View&) const override {return false;}
	virtual ~test_entity() override {}
};

BOOST_AUTO_TEST_CASE(test_camera_construction) {

	bq::entity* e = new test_entity();
	bq::camera cam(e);
	bq::v2f pos(1920, 1080);
	BOOST_CHECK(cam.view().getSize().x == pos.x);
	BOOST_CHECK(cam.view().getSize().y == pos.y);
	delete e;
}
BOOST_AUTO_TEST_CASE(test_camera_update) {
	bq::entity* e = new test_entity();
	bq::camera cam(e);

	for (unsigned i = 0; i < 100; ++i) {
		e->update();
		cam.update();
		BOOST_CHECK(cam.view().getCenter().x == e->pos().x);
		BOOST_CHECK(cam.view().getCenter().y == e->pos().y);
	}
	delete e;
}