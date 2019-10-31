#include <boost/test/auto_unit_test.hpp>

#include <bq.h>
#include <bq/world/world.h>
#include <bq/world/block.h>
class test_block : public bq::block {
public:
	test_block(float x, float y, float l, float w){
		pos = { x,y };
		size = { l,w };
	}

	bool intersects(sf::FloatRect& other) override{
		sf::FloatRect rect = { pos.x, pos.y, size.x, size.y };
		return rect.intersects(other);
	}
	bool contains(float x, float y) override {
		sf::FloatRect rect = { pos.x, pos.y, size.x, size.y };
		return rect.contains({ x,y });
	}
	void update() override{

	}
	void render(sf::RenderWindow& window) override{

	}
	void interact() override {

	}
};
class test_block2 : public bq::block {
public:
	test_block2(float x, float y, float l, float w) {
		pos = { x,y };
		size = { l,w };
	}
	bool contains(float x, float y) override {
		sf::FloatRect rect = { pos.x, pos.y, size.x, size.y };
		return rect.contains({ x,y });
	}
	void update() override {

	}
	void render(sf::RenderWindow& window) override {

	}
	void interact() override {

	}
};
//we're not going to test anything about blocks, as the onus to load the block vector from file is on the gamedev
class test_world : public bq::world {
public:
	test_world() {
		blocks.push_back(std::make_shared<test_block>(32,32,32,32));
	}
};
BOOST_AUTO_TEST_CASE(test_block_intersects) {
	test_block2 block1(32.f,32.f,32.f,32.f);
	//should intersect
	sf::FloatRect block2(0.f, 0.f, 33.f, 33.f);
	//should not
	sf::FloatRect block3(0.f, 0.f, 31.f, 31.f);

	//these should be inside block1
	bq::v2f p1(32.f,32.f);
	bq::v2f p2(63.f, 63.f);
	bq::v2f p3(63.f, 32.f);
	bq::v2f p4(32.f, 63.f);
	//this should not be
	bq::v2f p5(31.f, 31.f);
	BOOST_CHECK(block1.intersects(block2));
	BOOST_CHECK(!block1.intersects(block3));


	BOOST_CHECK(block1.contains(p1.x, p1.y));
	BOOST_CHECK(block1.contains(p2.x, p2.y));
	BOOST_CHECK(block1.contains(p3.x, p3.y));
	BOOST_CHECK(block1.contains(p4.x, p4.y));
	BOOST_CHECK(!block1.contains(p5.x, p5.y));

}
BOOST_AUTO_TEST_CASE(world_intersects_test) {
	test_world world;
	sf::FloatRect fr = {31,31,1,1};
	bq::block_collision_effects bce = world.get_collision_effects(fr);
	BOOST_CHECK( !bce.collides );
	fr = {32,32,1,1};
	bce = world.get_collision_effects(fr);
	BOOST_CHECK(bce.collides);
}
