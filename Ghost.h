#pragma once
#include"1_Class_MovingObject.h"
#include"Pacman.h"
#include<fstream>
#include"Class_queue.h"
#include"Global.h"
#include"IsInFileNewRecord.h"
//0 - Red
//1 - Pink
//2 - Blue 
//3 - Orange

class Ghost:public MovingObject
{
public:
	Ghost(unsigned char i_id);
	void switch_mode();

	void reset(const Position& i_home, const Position& i_home_exit);
	void update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman);

	void update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position);
	float get_target_distance(unsigned char i_direction);
	bool pacman_collision(const Position& i_pacman_position);
	void draw(bool i_flash, sf::RenderWindow& i_window)override;

private:
	bool movement_mode;
	unsigned char frightened_mode;

	unsigned char id;
	bool use_door;

	unsigned char frightened_speed_timer;

	Position home;
	Position home_exit;
	Position target;
};

