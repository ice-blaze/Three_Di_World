#include "Segment3D.h"

Segment3D::Segment3D(Segment3D const& _segment)
{
    pointA = Point3D(_segment.pointA); //because point are pointer, have to put a star befor the attribut
    pointB = Point3D(_segment.pointB); //because point are pointer, have to put a star befor the attribut
}

Segment3D::Segment3D(Point3D _a, Point3D _b)
{
    pointA = Point3D(_a);
    pointB = Point3D(_b);
}

Segment3D::Segment3D(float _x1, float _y1,float _z1,
                     float _x2, float _y2,float _z2)
{
    pointA = Point3D(_x1,_y1,_z1);
    pointB = Point3D(_x2,_y2,_z2);
}

Segment3D::~Segment3D()
{

}
