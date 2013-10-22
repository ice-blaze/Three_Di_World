// -----------------------------------------
// | Title       : three_di_world          |
// | Author      : Ice-Blaze               |
// | Start date  : 10.07.2013              |
// | Poject on a plan, a 3D linear algebra |
// -----------------------------------------

#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"

class Point3D
{
    public:
        Point3D(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=1.0f);// debug ok
        Point3D(Point3D const& _point);// debug ok
        virtual ~Point3D();

        Point3D operator + (Point3D _secondPoint);
        Point3D operator - (Point3D _secondPoint);
        Point3D operator * (float _mul);
        Point3D operator / (float _div);
        Point3D operator * (float matrix[3][3]);

        float length();
        Point3D normalize();
        Point3D cross(Point3D _pt);
        Point3D mulMat43(float matrix[4][3]); // uglyname
        void rotation(Point3D _axe, float _angle);
        Point2D convertPerspective();// static matrix in it

        float getX() {return x;};
        float getY() {return y;};
        float getZ() {return z;};
        float getW() {return w;};

        void setX(float _x) {x = _x;};
        void setY(float _y) {y = _y;};
        void setZ(float _z) {z = _z;};
        void setW(float _w) {w = _w;};

//        static Point3D camera;
//        static Point3D viewerPos;
//        static Point3D theta;
//        static float f;
//        static float dx;
//        static float dy;
//        static float far;
//        static float near;

        static Point3D cameraOrtho;
        static float xangle;
        static float yangle;
        static float zangle;
        static float scale;

        float x;
        float y;
        float z;
        float w;
};

#endif // POINT3D_H
