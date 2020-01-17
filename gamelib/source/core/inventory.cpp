#include "bq/core/inventory.h"
#include "bq/core/logger.h"
#include "bq/resource/resource_holder.h"
bq::inventory::inventory(){
	m_sprite.setTexture(bq::resource_holder::get().textures.get("inventory.png"));
	m_sprite.setPosition( 0,0);
}

void bq::inventory::cycle_forward() {
	index++;
	if (m_items.size() == 0) {
		index = -1;
		return;
	}
	if (index >= m_items.size()) {
		index = 0;
		return;
	}
}
void bq::inventory::cycle_backward() {
	index--;
	if (m_items.size() == 0) {
		index = -1;
		return;
	}
	if (index < 0) {
		index = m_items.size() - 1;
		return;
	}
}
bq::item* bq::inventory::get_selected() {
	if (index == -1) {
		bq::logger::critical("accessing empty inventory, please check if empty first");
		return nullptr;
	}
	else {
		return m_items[index].get();
	}
}
void bq::inventory::render(sf::RenderWindow& window) {
	window.draw(m_sprite);
	
	for (auto& item : m_items) {
		item->render(window);
	}

}
void bq::inventory::update_position(float x, float y) {
	m_sprite.setPosition(x, y);
	int x_coord = m_sprite.getPosition().x + 2;
	int y_coord = m_sprite.getPosition().y + 2;
	for (auto& item : m_items) {
		item->update_pos(x_coord, y_coord);
		x_coord += 34;
	}

	
}
void bq::inventory::add_item(std::unique_ptr<bq::item> item) {
	m_items.push_back(std::move(item));

	if (index == -1) {
		index = 0;
	}

}
bool bq::inventory::empty() {
	return m_items.size() == 0;
}
void bq::inventory::drop_item() {
	m_items.erase(m_items.begin() + index);
}