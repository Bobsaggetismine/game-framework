#include "pongworld.h"
#include <bq/resource/resource_manager.h>
#include "rock.h"
#include "door.h"
#include "lava.h"
#include "robot_spawner.h"
pongworld::pongworld() {
	std::ifstream fstream("res/world.data");
	background.setTexture(bq::resource_holder::get().textures.get("background.png"));
	unsigned i = 0;
	int x = 0, j = 0;
	std::vector<bq::v2f> colisions;
	for (std::string line; std::getline(fstream, line); ++i){
		j = 0;
		h += 32;
		for (unsigned y = 0; y < line.size(); ++y) {
			if(i == 0) w += (32.f);
			if (line[y] == '1') {
				m_blocks.push_back(std::make_shared<rock>((float)(y * 32), (float)(i * 32), 32.f, 32.f));
				colisions.push_back({ ((float)j) / 32.f, ((float)x) / 32.f });
			}
			else if (line[y] == '2') {
				m_blocks.push_back(std::make_shared<door>("topDoor.png", (float)(y * 32), (float)(i * 32), 32.f, 32.f));
				colisions.push_back({ ((float)j) / 32.f, ((float)x) / 32.f });
			}
			else if (line[y] == '3') {
				m_blocks.push_back(std::make_shared<door>("bottomDoor.png", (float)(y * 32), (float)(i * 32), 32.f, 32.f));
				colisions.push_back({ ((float)j) / 32.f, ((float)x) / 32.f });
			}
			else if (line[y] == '4') {
				m_blocks.push_back(std::make_shared<lava>((float)(y * 32), (float)(i * 32), 32.f, 32.f));
				colisions.push_back({ ((float)j) / 32.f, ((float)x) / 32.f });
			}
			else if (line[y] == '5') {
				m_blocks.push_back(std::make_shared<robot_spawner>((float)(y * 32), (float)(i * 32), 32.f, 32.f));
				colisions.push_back({ ((float)j) / 32.f, ((float)x) / 32.f });
			}
			j += 32;
		}
		x += 32;
	}
	m_generator.set_size({ x / 32 , j / 32 });
	m_generator.set_diagonal(true);
	for (auto& col : colisions) {
		m_generator.add_collision({ (int)col.x, (int)col.y} );
	}
}

std::unique_ptr<std::vector<bq::v2i>> pongworld::get_path(bq::v2i start, bq::v2i end)
{
	return m_generator.pathfind({ start.x, start.y}, { end.x, end.y });
}
