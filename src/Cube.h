#ifndef CUBE_H
#define CUBE_H

#include "Point3D.h"
#include "Segment3D.h"
class Cube
{
    public:
        Cube(Point3D _pt1, Point3D _pt2, Point3D _pt3, Point3D _pt4);
        virtual ~Cube();

        void rotation(Point3D _axe,float _angle);
        void moveX(float _moveValue);
        void moveY(float _moveValue);
        void moveZ(float _moveValue);

        Point3D pt1;
        Point3D pt2;
        Point3D pt3;
        Point3D pt4;
    protected:
    private:


};

#endif // CUBE_H
