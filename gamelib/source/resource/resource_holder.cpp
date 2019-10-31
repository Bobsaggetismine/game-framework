#include "bq/resource/resource_holder.h"

bq::resource_holder& bq::resource_holder::get() {
	static resource_holder instance;
	return instance;
	
}
void bq::resource_holder::close() {
	textures.close();
	fonts.close();
	sounds.close();
}
bq::resource_holder::resource_holder():textures("png"),fonts("ttf"),sounds("wav") {}