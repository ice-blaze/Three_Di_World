#ifndef DRAW2D_H
#define DRAW2D_H

#include "Segment3D.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Cube.h"
#include "SDL.h"

class Draw2D
{
    public:
        static void drawSegment(SDL_Surface *screen,int x0, int y0, int x1, int y1, Uint8 r=255, Uint8 g=255, Uint8 b=255);
        static void drawSegment(SDL_Surface *screen,Point3D _ptA, Point3D _ptB, Uint8 r=255, Uint8 g=255, Uint8 b=255);
        static void drawSegment(SDL_Surface *screen,Segment3D _segment, Uint8 r=255, Uint8 g=255, Uint8 b=255);
        static void drawCube(SDL_Surface *screen,Point3D _pt1, Point3D _pt2, Point3D _pt3, Point3D _pt4);
        static void drawCube(SDL_Surface *screen,Cube _cube);
        static void setPixel(SDL_Surface *screen, int x, int y, Uint8 R=255, Uint8 G=255, Uint8 B=255);
        static void setPixel(SDL_Surface *screen, Point2D _pt, Uint8 R=255, Uint8 G=255, Uint8 B=255);
        static void setWhitePixel(SDL_Surface *screen, int x, int y);

        static bool modelview(Point3D &_pt);
        static Point2D project(const Point3D &_pt);
        static Point3D camera;
        static Point2D center;
        static float xangle;
        static float yangle;
        static float zangle;
        static float near;
        static float far;
        static float f;
        static float dx;
        static float dy;

        static void setXangle(float _angle);
        static void setYangle(float _angle);
        static void setZangle(float _angle);
};

#endif // DRAW2D_H
