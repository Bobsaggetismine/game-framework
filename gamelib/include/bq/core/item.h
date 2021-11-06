#pragma once
#include <bq/graphics/sprite.h>

namespace bq {
	struct v2f;
	class window;
	class item {
	protected:
		bq::sprite m_sprite;
		unsigned m_uses = 5;
	public:
		virtual ~item() = 0;

		virtual void action(std::optional<sf::Keyboard::Key>, std::optional<bq::v2f>) = 0;
		void add_uses(unsigned toAdd);
		void remove_uses(unsigned toRemove);
		void render(bq::window&);
		void update_pos(float x , float y);
		unsigned uses() const;
	};
}