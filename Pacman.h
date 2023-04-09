#pragma once
#include"1_Class_MovingObject.h"
#include"MapCollision.h"

class Pacman:public MovingObject
{
public:
	Pacman();
	bool get_dead();
	void set_dead(bool i_dead);

	unsigned short get_energizer_timer();
	void set_energizer_timer(unsigned short energ_tim);

	bool get_animation_over();
	void set_animation_over(bool an_tim);
	
	void reset();
	void draw(bool i_victory, sf::RenderWindow& i_window) override;
	void update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

private:
	bool dead;
	unsigned short energizer_timer;
	bool animation_over;
};