#include "bqpch.h"
#include <bq/graphics/sprite.h>
#include "bq/core/item.h"
#include <bq/graphics/window.h>
#include "bq/core/inventory.h"
#include "bq/resource/resource_holder.h"
bq::inventory::inventory(){
	m_sprite.set_texture(bq::resource_holder::get().textures.get("inventory.png"));
	m_sprite.set_pos(0,0);
}

void bq::inventory::cycle_forward() {
	m_index++;
	if (m_items.size() == 0) {
		m_index = -1;
		return;
	}
	if (m_index >= m_items.size()) {
		m_index = 0;
		return;
	}
}
void bq::inventory::cycle_backward() {
	m_index--;
	if (m_items.size() == 0) {
		m_index = -1;
		return;
	}
	if (m_index < 0) {
		m_index = m_items.size() - 1;
		return;
	}
}
bq::item* bq::inventory::get_selected() const {
	if (m_index == -1) {
		bq::logger::warn("accessing empty inventory, please check if empty first");
		return nullptr;
	}
	else {
		return m_items[m_index].get();
	}
}
void bq::inventory::render(bq::window& window) const {
	window.draw(m_sprite);
	for (auto& item : m_items) {
		item->render(window);
	}
}
void bq::inventory::update_position(float x, float y) {
	m_sprite.set_pos(x, y);
	float x_coord = m_sprite.get_pos().x + 2;
	float y_coord = m_sprite.get_pos().y + 2;
	for (auto& item : m_items) {
		item->update_pos(x_coord, y_coord);
		x_coord += 34;
	}
}
void bq::inventory::add_item(std::unique_ptr<bq::item> item) {
	m_items.push_back(std::move(item));
	if (m_index == -1) {
		m_index = 0;
	}
}
bool bq::inventory::empty() const {
	return m_items.size() == 0;
}
void bq::inventory::drop_item() {
	m_items.erase(m_items.begin() + m_index);
	if (empty()) {
		m_index = -1;
	}
}