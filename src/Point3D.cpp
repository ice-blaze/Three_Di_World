#include "Point3D.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <ostream>
#include <vector>
#include <iomanip>
#include <cstdlib>

#include <cstdio>
#include <string.h>
//Point3D Point3D::camera = Point3D(-95.000000, 84.000000, 1239.000000);
//Point3D Point3D::camera = Point3D(-95.000000, 84.000000, 57.000000);
//Point3D Point3D::viewerPos = Point3D(-338.000000, 10.000000, -86.000000);
//Point3D Point3D::theta = Point3D(-2.986966, -7.847618, 5.838755);

//float Point3D::f = 470;
//float Point3D::dx = 1;
//float Point3D::dy = 1;
//float Point3D::far = -190;
//float Point3D::near = 1;

// orthographic part
Point3D Point3D::cameraOrtho = Point3D(0, 0, 0);
float Point3D::xangle = 0; // ortho : -3.14/2.2;
float Point3D::yangle = 0;
float Point3D::zangle = 0;// ortho  : 0.6;
float Point3D::scale = 0.5;


Point3D::Point3D(float _x, float _y, float _z,float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

Point3D::Point3D(Point3D const& _point)
{
    x = _point.x;
    y = _point.y;
    z = _point.z;
    w = _point.w;
}

Point3D::~Point3D()
{
    //dtor
}

Point3D Point3D::operator + (Point3D _secondPoint)
{
    return Point3D(x+_secondPoint.x,y+_secondPoint.y,z+_secondPoint.z);
}

Point3D Point3D::operator - (Point3D _secondPoint)
{
    return Point3D(x-_secondPoint.x,y-_secondPoint.y,z-_secondPoint.z);
}

Point3D Point3D::operator * (float _mul)
{
    return Point3D(x*_mul,y*_mul,z*_mul);
}

Point3D Point3D::operator / (float _div)
{
    return Point3D(x/_div,y/_div,z/_div);
}

Point3D Point3D::operator * (float _matrix[3][3])
{
    float newX = x*_matrix[0][0]+y*_matrix[0][1]+z*_matrix[0][2];
    float newY = x*_matrix[1][0]+y*_matrix[1][1]+z*_matrix[1][2];
    float newZ = x*_matrix[2][0]+y*_matrix[2][1]+z*_matrix[2][2];

    return Point3D(newX,newY,newZ);
}

Point3D Point3D::mulMat43(float matrix[4][3])
{
    // should have some explaination
    float newX = x*matrix[0][0]+y*matrix[1][0]+z*matrix[2][0]+matrix[3][0];
    float newY = x*matrix[0][1]+y*matrix[1][1]+z*matrix[2][1]+matrix[3][1];
    float newZ = x*matrix[0][2]+y*matrix[1][2]+z*matrix[2][2]+matrix[3][2];

    return Point3D(newX,newY,newZ);
}

void Point3D::rotation(Point3D _axe, float _angle)
{
    float norme_axe = sqrt(_axe.getX()*_axe.getX()+_axe.getY()*_axe.getY()+_axe.getZ()*_axe.getZ());
    float uX = _axe.getX()/norme_axe;
    float uY = _axe.getY()/norme_axe;
    float uZ = _axe.getZ()/norme_axe;

    float mat[3][3] = {{ uX*uX+(1-uX*uX)*(float)cos(_angle) , uX*uY*(1-(float)cos(_angle))-uZ*(float)sin(_angle) , uX*uZ*(1-(float)cos(_angle))+uY*(float)sin(_angle) },
                       { uX*uY*(1-(float)cos(_angle))+uZ*(float)sin(_angle) , uY*uY+(1-uY*uY)*(float)cos(_angle) , uY*uZ*(1-(float)cos(_angle))-uX*(float)sin(_angle) },
                       { uX*uZ*(1-(float)cos(_angle))-uY*(float)sin(_angle) , uY*uZ*(1-(float)cos(_angle))+uX*(float)sin(_angle) , uZ*uZ+(1-uZ*uZ)*(float)cos(_angle) }};

    // multiplication between the matrix and the point (or vector)
    (*this) = (*this)*mat;
}

float Point3D::length()
{
    return sqrt(x*x+y*y+z*z);
}

Point3D Point3D::normalize()
{
    float length = this->length();
    return Point3D(x/length,y/length,z/length);
}

Point3D Point3D::cross(Point3D _pt)
{
    float newX = y*_pt.z - z*_pt.y;
    float newY = z*_pt.x - x*_pt.z;
    float newZ = x*_pt.y - y*_pt.x;

    return Point3D(newX,newY,newZ);
}

Point3D mult44(Point3D _pt, float _mat[4][4])
{
//    float x = _pt.x*_mat[0][0]+_pt.y*_mat[0][1]+_pt.z*_mat[0][2]+_mat[0][3];
//    float y = _pt.x*_mat[1][0]+_pt.y*_mat[1][1]+_pt.z*_mat[1][2]+_mat[1][3];
//    float z = _pt.x*_mat[2][0]+_pt.y*_mat[2][1]+_pt.z*_mat[2][2]+_mat[2][3];

    float x = _pt.x*_mat[0][0]+_pt.y*_mat[1][0]+_pt.z*_mat[2][0]+_mat[3][0];
    float y = _pt.x*_mat[0][1]+_pt.y*_mat[1][1]+_pt.z*_mat[2][1]+_mat[3][1];
    float z = _pt.x*_mat[0][2]+_pt.y*_mat[1][2]+_pt.z*_mat[2][2]+_mat[3][2];
    return Point3D(x,y,z);
}

float degtorad(const float &angle) { return 3.14 * angle / 180.0; }

Point2D Point3D::convertPerspective()
{
//    Point3D newPoint = *this;
//    newPoint = newPoint+cameraOrtho;
//    newPoint.rotation(Point3D(1,0,0),xangle);
//    newPoint.rotation(Point3D(0,1,0),yangle);
//    newPoint.rotation(Point3D(0,0,1),zangle);
//
//    return Point2D(scale*newPoint.x+640/2,scale*newPoint.z+480/2);

//    // camera pin hole
//    Point3D newPoint = *this;
//
//    newPoint = newPoint-camera;
//    newPoint.rotation(Point3D(0,1,0),yangle);
//    newPoint.rotation(Point3D(1,0,0),xangle);
//    newPoint.rotation(Point3D(0,0,1),zangle);
//
//
////    Point3D theta2 = theta;
//
//
////    Point3D d(cos(theta2.y)*(sin(theta2.z)*newPoint.y+cos(theta2.z)*newPoint.x)-sin(theta2.y)*newPoint.z,
////              sin(theta2.x)*(cos(theta2.y)*newPoint.z+sin(theta2.y)*(sin(theta2.z)+cos(theta2.z)*newPoint.x))+cos(theta2.x)*(cos(theta2.z)*newPoint.y-sin(theta2.z)*newPoint.x),
////              sin(theta2.x)*(cos(theta2.y)*newPoint.z+sin(theta2.y)*(sin(theta2.z)+cos(theta2.z)*newPoint.x))-sin(theta2.x)*(cos(theta2.z)*newPoint.y-sin(theta2.z)*newPoint.x));
//
////    Point3D d = newPoint;
////
////    return Point2D((viewerPos.z/d.z)*d.x-viewerPos.x,
////                   (viewerPos.z/d.z)*d.y-viewerPos.y);
//
//    float w = -newPoint.z;
//
//    Point3D test = newPoint;// test should be replace with newPoint
//
//    test.x *= near/(640/2);
//    test.y *= near/(480/2);
//    test.z = (test.z*((-far+near)/(far-near))+((-2*far*near)/(far-near)));
//
//    if(test.x > w || test.x < -w || test.y > w || test.y < -w || test.z > w || test.z < -w )
//    {
//        return Point2D();
//    }
//
//    newPoint = newPoint/w;
//
//    // f = scale
//    // dx can mirror the x axe
//    // dy can mirror the y axe
//    // center : center the origin in the middle of the screen
//    Point2D result(newPoint.x/(newPoint.z+0.1),newPoint.y/(newPoint.z+0.1));
//    result = result*f;
//    result.x = result.x/dx;
//    result.y = result.y/dy;
//    Point2D center(640/2,480/2);
//
//    return result+center;


// --------------- not that good -------------------
//    int width = 640, height = 480;
//	float aspectRatio = float(width) / height;
//
//	float l = -aspectRatio, r = aspectRatio;
//
//    float mat[4][4] = {0};
//	float scale = 1.0 / tan(degtorad(fov * 0.5));
//    mat[0][0] = mat[1][1] = scale;
//	mat[2][2] = - far / (far - near);
//	mat[3][2] = - far * near / (far - near);
//	mat[2][3] = - 1;
//	mat[3][3] = 0;
//
//	Point3D newPoint = mult44(*this,mat);
//
//    if (newPoint.x < l || newPoint.x > r || newPoint.y < b || newPoint.y > t) return Point2D();
//
//    float px = std::min(float((newPoint.x - l) / (r - l) * width), float(width - 1));
//    float py = std::min(float((1 - (newPoint.y - b) / (t - b)) * height), float(height - 1));
//
//
//	return Point2D(px,py);
//    Point3D eye = camera;
//    Point3D target = viewerPos;
//    Point3D up = theta;
//
//    Point3D zaxis = target - eye;    // The "look-at" vector.
//    zaxis = zaxis.normalize();
//    Point3D xaxis = up.cross(zaxis);// The "right" vector.
//    xaxis = xaxis.normalize();
//    Point3D yaxis = zaxis.cross(xaxis);     // The "up" vector.
//
//    // Create a 4x4 orientation matrix from the right, up, and at vectors
//    float orientation[4][4] = {
//        {xaxis.x, yaxis.x, zaxis.x, 0},
//        {xaxis.y, yaxis.y, zaxis.y, 0},
//        {xaxis.z, yaxis.z, zaxis.z, 0},
//        {  0,       0,       0,     1}
//    };
//
//    // Create a 4x4 translation matrix by negating the eye position.
//    float translation[4][4] = {
//          {1,      0,      0,     0},
//          {0,      1,      0,     0},
//          {0,      0,      1,     0},
//        {-eye.x, -eye.y, -eye.z,  1}
//    };
//
//    float newMat[4][4];
//    newMat[0][0] = translation[0][0]*orientation[0][1]+translation[0][1]*orientation[1][0]+translation[0][2]*orientation[2][0]+translation[0][3]*orientation[3][0];
//    newMat[0][0] = translation[0][0]*orientation[0][1]+translation[0][1]*orientation[1][0]+translation[0][2]*orientation[2][0]+translation[0][3]*orientation[3][0];
//
    return Point2D();

}
