#pragma once
#include <SFML/Graphics.hpp>
#include <bq/event/event.h>

namespace bq {

	class sprite;

	enum class colour {
		BLACK
	};

	class window {
		sf::RenderWindow m_window;
	public:
		window(unsigned,unsigned,const std::string& title);
		void draw(const bq::sprite&);
		bool open();
		bq::event poll_event();
		void clear(colour);
		void show();
		void close();
		void set_view(const sf::View& view);
		void draw(const sf::RectangleShape& r);
		void draw(const sf::Text& t);

		bq::v2i get_mouse_pos();
	};
}