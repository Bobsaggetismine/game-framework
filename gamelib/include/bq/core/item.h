#pragma once
#include <optional>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
namespace bq {
	class item {
	protected:
		sf::Sprite m_sprite;
		int m_uses = 5;
	public:

		virtual void action(std::optional<sf::Keyboard::Key>) = 0;
		int uses();
		void add_uses(int toAdd);
		void remove_uses(int toRemove);
		void render(sf::RenderWindow&);
		void update_pos(float x , float y);
	};
}