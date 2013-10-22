#ifndef SEGMENT3D_H
#define SEGMENT3D_H

#include "Point3D.h"

class Segment3D
{
    public:
        Segment3D(Segment3D const& _segment);// debug ok
        Segment3D(Point3D _a, Point3D _b);// debug ok
        Segment3D(float _x1=0.0f, float _y1=0.0f,float _z1=0.0f,
                  float _x2=0.0f, float _y2=0.0f,float _z2=0.0f);// debug ok
        virtual ~Segment3D();

        Point3D* getPointA() {return &pointA;};// debug ok
        Point3D* getPointB() {return &pointB;};// debug ok

    protected:
    private:
        Point3D pointA;
        Point3D pointB;

};

#endif // SEGMENT3D_H
