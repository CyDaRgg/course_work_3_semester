#include"_1Class_SimpleObject.h"


SimpleObject::Position SimpleObject::get_position()
{
	return position;
}
void SimpleObject::set_position(unsigned short x, unsigned short y)
{
	position.x = x; position.y = y;
}


