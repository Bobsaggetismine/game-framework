#include <boost/test/auto_unit_test.hpp>

#include <bq.h>
#include <bq/exception/illegal_state.h>
#include <bq/state/state.h>
#include <bq/state/state_manager.h>
class test_state : public bq::state {
	void update() override{

	}
	void render(sf::RenderWindow& window) {

	}
	void handleEvents(sf::Event& evt, sf::RenderWindow& window) {

	}
};

BOOST_AUTO_TEST_CASE(test_state_manager_constructor) {
	bq::state_manager sm(std::make_unique<test_state>());
	BOOST_CHECK(sm.get_num_states() == 1);
}
BOOST_AUTO_TEST_CASE(test_state_manager_pop) {
	bq::state_manager sm(std::make_unique<test_state>());
	sm.pop();
	BOOST_CHECK(sm.get_num_states() == 0);
}
BOOST_AUTO_TEST_CASE(test_state_manager_replace_true) {

	bq::state* ts = new test_state();
	bq::state* ts1 = new test_state();

	/*

	bq::state_manager sm(std::make_unique<test_state>(ts));
	sm.push(std::make_unique<test_state>(ts1));
	BOOST_CHECK(sm.get_num_states() == 1);

	BOOST_CHECK(sm.get_current_state() == ts1);
	BOOST_CHECK(sm.get_current_state() != ts);
	*/
	delete ts;
	delete ts1;
}
BOOST_AUTO_TEST_CASE(test_state_manager_replace_false) {
	/*
	bq::state* ts = new test_state();
	bq::state* ts1 = new test_state();


	bq::state_manager sm(std::make_unique<test_state>(ts));
	sm.push(std::make_unique<test_state>(ts1), false);
	BOOST_CHECK(sm.get_num_states() == 2);

	BOOST_CHECK(sm.get_current_state() == ts1);
	sm.pop();
	BOOST_CHECK(sm.get_current_state() == ts);
	*/
}
BOOST_AUTO_TEST_CASE(test_state_manager_empty) {

	bq::state_manager sm(std::make_unique<test_state>());
	sm.pop();
	BOOST_REQUIRE_THROW(sm.update(), bq::illegal_state);
	sf::RenderWindow window;
	BOOST_REQUIRE_THROW(sm.render(window), bq::illegal_state);
}