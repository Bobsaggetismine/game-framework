#include "pongworld.h"

#include "rock.h"
#include  "door.h"
#include "lava.h"
pongworld::pongworld() {
	std::ifstream fstream("res/world.data");
	unsigned i = 0;
	for (std::string line; std::getline(fstream, line); ++i){
		h += (32.f);
		for (unsigned y = 0; y < line.size(); ++y) {
			if(i == 0)
			w += (32.f);
			if (line[y] == '1') {
				blocks.push_back(std::make_shared<rock>((float)(i*32),(float)(y*32),32.f,32.f));
			}
			else if (line[y] == '2') {
				blocks.push_back(std::make_shared<door>("topDoor.png", (float)(i * 32), (float)(y * 32), 32.f, 32.f));
			}
			else if (line[y] == '3') {
				blocks.push_back(std::make_shared<door>("bottomDoor.png", (float)(i * 32), (float)(y * 32), 32.f, 32.f));
			}
			else if (line[y] == '4') {
				blocks.push_back(std::make_shared<lava>((float)(i * 32), (float)(y * 32), 32.f, 32.f));
			}
		}
	}
}