#include "Cube.h"

Cube::Cube(Point3D _pt1, Point3D _pt2, Point3D _pt3, Point3D _pt4)
{
    pt1 = _pt1;
    pt2 = _pt2;
    pt3 = _pt3;
    pt4 = _pt4;
}

Cube::~Cube()
{
    //dtor
}

void Cube::rotation(Point3D _axe,float _angle)
{
    // cube center
    Point3D cubeCenter = (pt2+pt3+pt4-pt1)/2;

    // translation matrix to go to the origin
    float matGoOrigin[4][3] = {{1,0,0},
                               {0,1,0},
                               {0,0,1},
                               {-cubeCenter.getX(),-cubeCenter.getY(),-cubeCenter.getZ()}};

    // translation matrix to go to the initial place of the cube
    float matGoBack [4] [3] = {{1,0,0},
                               {0,1,0},
                               {0,0,1},
                               {cubeCenter.getX(),cubeCenter.getY(),cubeCenter.getZ()}};

    // move the cube to the origin
    pt1 = pt1.mulMat43(matGoOrigin);
    pt2 = pt2.mulMat43(matGoOrigin);
    pt3 = pt3.mulMat43(matGoOrigin);
    pt4 = pt4.mulMat43(matGoOrigin);

    // rotate the cube on the axe given in parameters
    pt1.rotation(_axe,_angle);
    pt2.rotation(_axe,_angle);
    pt3.rotation(_axe,_angle);
    pt4.rotation(_axe,_angle);

    // move the cube to his inital place
    pt1 = pt1.mulMat43(matGoBack);
    pt2 = pt2.mulMat43(matGoBack);
    pt3 = pt3.mulMat43(matGoBack);
    pt4 = pt4.mulMat43(matGoBack);
}

//------------------------ MOVE ZONE ------------------------
// the move value will change the same attributs on all points
void Cube::moveX(float _moveValue)
{
    pt1.setX(pt1.getX()+_moveValue);
    pt2.setX(pt2.getX()+_moveValue);
    pt3.setX(pt3.getX()+_moveValue);
    pt4.setX(pt4.getX()+_moveValue);
}

void Cube::moveY(float _moveValue)
{
    pt1.setY(pt1.getY()+_moveValue);
    pt2.setY(pt2.getY()+_moveValue);
    pt3.setY(pt3.getY()+_moveValue);
    pt4.setY(pt4.getY()+_moveValue);
}

void Cube::moveZ(float _moveValue)
{
    pt1.setZ(pt1.getZ()+_moveValue);
    pt2.setZ(pt2.getZ()+_moveValue);
    pt3.setZ(pt3.getZ()+_moveValue);
    pt4.setZ(pt4.getZ()+_moveValue);
}
