#pragma once
#include<SFML/Graphics.hpp>

class SimpleObject
{
public:
	class Position
	{
	public:
		Position() :x(0), y(0) {}
		bool operator==(const Position& i_position)
		{
			return this->x == i_position.x && this->y == i_position.y;
		}

		short x;
		short y;
	};

	 Position get_position();
	 void set_position(unsigned short x, unsigned short y);
	 
protected:
	Position position;
};