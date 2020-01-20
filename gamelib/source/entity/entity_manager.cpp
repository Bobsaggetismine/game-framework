#include <bq/entity/entity_manager.h>
#include <bq/core/handler.h>

bq::entity_manager::entity_manager() {}

void bq::entity_manager::add(std::shared_ptr<entity> e) {
	entities.push_back(e);
}
void bq::entity_manager::markAdd(std::shared_ptr<entity> e) {
	marked_to_add.push_back(e);
}
void bq::entity_manager::remove(std::shared_ptr<entity> e) {
	marked_to_remove.push_back(e);
}
void bq::entity_manager::remove_marked() {
	for (std::shared_ptr<entity> e : marked_to_remove) {
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			if ((e) == (*it)) {
				entities.erase(it);
				break;
			}
		}
	}
	marked_to_remove.clear();
}
void bq::entity_manager::add_marked() {
	for (auto e : marked_to_add) {
		entities.push_back(e);
	}
	marked_to_add.clear();
}
void bq::entity_manager::update() {
#ifdef _DEBUG
	if (entities.size() == 0) {
		bq::logger::warn("Entitites vector is empty - entity_manager::update()");
	}
	else {
		if(static_cast<int>(bq::random::getRandom(1,100)) == 2) bq::logger::info("Entities: " + std::to_string(entities.size()));
	}
#endif
	for (std::shared_ptr<entity> e : entities) {
		if (e->shouldCull(bq::handler::get().m_cam->view)) {
			marked_to_remove.push_back(e);
		}
		else e->update();
	}
	remove_marked();
	add_marked();
}
void bq::entity_manager::render(sf::RenderWindow& window) {
	for (std::shared_ptr<entity> e : entities) {
		e->render(window);
	}
}
void bq::entity_manager::handleEvent(sf::Event& evt) {
	for (std::shared_ptr<entity> e : entities) {
		e->handleEvent(evt);
	}
}

std::shared_ptr<bq::entity> bq::entity_manager::intersects(sf::FloatRect& other, int requester_id, bool find_same_type)
{
	for (auto& e : entities) {
		if (e->intersects(other)) {
			if (requester_id == e->id && !find_same_type) {
				continue;
			}
			return e;
		}
	}
	return nullptr;
}
