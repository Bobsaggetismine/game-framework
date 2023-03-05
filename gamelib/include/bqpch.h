#pragma once


//sfml includes
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>

//stl includes
#include <stack>
#include <map>
#include <iostream>
#include <functional>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include <optional>
#include <exception>
#include <chrono>
//bq include 
//note if adding bq include: if you add a file that changes often here, you're actually harming compile performance here.
#include <bq/core/logger.h>
#include <bq/util/vec.h>
#include <bq/util/random.h>
#include <bq/util/nonmoveable.h>
#include <bq/util/noncopyable.h>
#include <bq/util/json.h>
#define INTL_HEIGHT 512
#define INTL_WIDTH 512