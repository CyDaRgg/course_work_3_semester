#pragma once
#include<array>
#include"Ghost.h"
#include"_1Class_SimpleObject.h"

class GhostManager:public Draw
{
private:
	//The ghosts will switch between the scatter mode and the chase mode before permanently chasing Pacman.
	unsigned char current_wave; // 0 1 2 3 4 5 6 7
	unsigned short wave_timer;

	std::array<Ghost, 4> ghosts;
public:
	GhostManager();

	void update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman);
	void draw(bool i_flash, sf::RenderWindow& i_window) override;
	void reset(unsigned char i_level, const std::array<SimpleObject::Position, 4>& i_ghost_positions);

};

