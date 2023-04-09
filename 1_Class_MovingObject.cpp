#include"1_Class_MovingObject.h"



unsigned char MovingObject::get_direction()
{
	return direction;
}
void MovingObject::set_direction(unsigned char direction)
{
	this->direction = direction;
}

unsigned short MovingObject::get_animation_timer()
{
	return animation_timer;
}
void MovingObject::set_animation_timer(unsigned short animation_timer)
{
	this->animation_timer = animation_timer;
}

