#pragma once
#include"_1Class_SimpleObject.h"
#include"_1_Class_Draw.h"


class MovingObject:public SimpleObject,public Draw
{
public:
	unsigned char get_direction();
	void set_direction(unsigned char direction);

	unsigned short get_animation_timer();
	void set_animation_timer(unsigned short i_animation_timer);
	

protected:
	unsigned char direction;
	unsigned short animation_timer;

};
