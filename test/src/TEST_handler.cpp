#include <boost/test/auto_unit_test.hpp>

#include <bq.h>
#include "world.h"

BOOST_AUTO_TEST_CASE(test_null_return_case) {
	//these exceptions are only thrown in debug mode to eliminate if statements from release code making it more performant, expected that code will be tested in debug and not release but just in case guard this
#ifdef DEBUG
	BOOST_REQUIRE_THROW(bq::handler::get().em(), bq::illegal_state);
	BOOST_REQUIRE_THROW(bq::handler::get().world(), bq::illegal_state);
	BOOST_REQUIRE_THROW(bq::handler::get().sm(), bq::illegal_state);
	BOOST_REQUIRE_NO_THROW(bq::handler::get().cam());
#endif
}

BOOST_AUTO_TEST_CASE(test_non_null_return_case) {
	auto em = std::make_unique<bq::entity_manager>();
	auto sm = std::make_unique<bq::state_manager>();
	auto world = std::make_unique<test_world>();

	bq::handler::get().set_em(std::move(em));
	bq::handler::get().set_sm(std::move(sm));
	bq::handler::get().set_world (std::move(world));
	
	BOOST_REQUIRE_NO_THROW(bq::handler::get().em());
	BOOST_REQUIRE_NO_THROW(bq::handler::get().world());
	BOOST_REQUIRE_NO_THROW(bq::handler::get().sm());
}

