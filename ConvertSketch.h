#pragma once

#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "Pacman.h"

#include "_1Class_SimpleObject.h"


std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch, std::array<SimpleObject::Position, 4>& i_ghost_positions, Pacman& i_pacman);
