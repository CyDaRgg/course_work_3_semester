#pragma once
#include<SFML/Graphics.hpp>


class Draw
{
public:
	virtual void draw(bool, sf::RenderWindow& )=0;
};