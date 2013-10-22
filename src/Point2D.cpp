#include "Point2D.h"

Point2D::Point2D(float _x, float _y)
{
    x = _x;
    y = _y;
}

Point2D::Point2D(Point2D const& _point)
{
    x = _point.x;
    y = _point.y;
}

Point2D::~Point2D()
{
    //dtor
}

Point2D Point2D::operator + (Point2D _secondPoint)
{
    return Point2D(x+_secondPoint.x,y+_secondPoint.y);
}

Point2D Point2D::operator - (Point2D _secondPoint)
{
    return Point2D(x-_secondPoint.x,y-_secondPoint.y);
}

Point2D Point2D::operator * (float _mul)
{
    return Point2D(x*_mul,y*_mul);
}

Point2D Point2D::operator / (float _div)
{
    return Point2D(x/_div,y/_div);
}
