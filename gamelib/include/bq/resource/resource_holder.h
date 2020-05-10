#pragma once
#include <bq/resource/resource_manager.h>
namespace bq  {


	class resource_holder : public bq::noncopyable, public bq::nonmoveable {
		resource_holder();
		~resource_holder();
	public:
		
		static resource_holder& get();
		
		resource_manager<sf::Texture>        textures;
		resource_manager<sf::Font>			 fonts;
		resource_manager<sf::SoundBuffer>	 sounds;
	};
}