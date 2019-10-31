#pragma once

//sfml includes
#include <SFML/Graphics.hpp>
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
//bq includes
#include <bq/core/logger.h>
#include <bq/util/block_collision_effects.h>
#include <bq/util/noncopyable.h>
#include <bq/util/nonmoveable.h>
#include <bq/util/random.h>
#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif
#else
#define DBG_NEW new
#endif