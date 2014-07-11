#include "Point.h"

bool FEqual(float f1, float f2) 
{
	return (abs(f1 - f2) < 1e-4f);
}

float Point::operator^(const Point &p)
{
	return (x_ * p.y_ - y_ * p.x_);
}

bool Point::operator>(const Point &p)
{
	return (x_ > p.x_ || (FEqual(x_, p.x_) && y_ > p.y_) );
}

bool Point::operator<(const Point &p)
{
	return (x_ < p.x_ || (FEqual(x_ , p.x_) && y_ < p.y_) );
}
	
bool Point::operator==(const Point &p)
{
	return ( FEqual(x_ , p.x_) && FEqual(y_ , p.y_));
}