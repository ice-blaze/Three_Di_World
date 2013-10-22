#include "Draw2D.h"
#include <math.h>

#define PI 3.14

Point3D Draw2D::camera = Point3D(225.000000, 225.000000, 1200.000000);
//Point3D Draw2D::camera = Point3D(0.000000, 0.000000, 0.000000);
Point2D Draw2D::center(640/2,480/2);
float Draw2D::xangle = 0;
float Draw2D::yangle = 0;
float Draw2D::zangle = 0;
float Draw2D::far = 190;
float Draw2D::near = 0.01;
float Draw2D::f = 470;
float Draw2D::dx = 1;
float Draw2D::dy = 1;


void Draw2D::drawSegment(SDL_Surface *screen,int x0, int y0, int x1, int y1, Uint8 r, Uint8 g, Uint8 b)
{
    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int sx,sy;

    if (x0 < x1)
    {
        sx = 1 ;
    }else{
        sx = -1;
    }

    if (y0 < y1){
        sy = 1;
    } else {
        sy = -1;
    }

    int err = dx-dy;

    while (true) {
        setPixel(screen,x0,y0,r,g,b);

        if (x0 == x1 && y0 == y1){
            break;
        }

        int e2 = 2*err;

        if (e2 > -dy ){
            err = err - dy;
            x0 = x0 + sx;
        }

        if (x0 == x1 && y0 == y1){
            setPixel(screen,x0,y0,r,g,b);
            break;
        }

        if (e2 <  dx){
            err = err + dx;
            y0 = y0 + sy;
        }
    }
}

bool Draw2D::modelview(Point3D &_pt)
{
    _pt = _pt-camera;
    //order is important
    _pt.rotation(Point3D(0,1,0),yangle);
    _pt.rotation(Point3D(1,0,0),xangle);
    _pt.rotation(Point3D(0,0,1),zangle);

    _pt.w = -_pt.z;

    //projection matrix source : http://www.songho.ca/opengl/gl_projectionmatrix.html
    // whithout this code near plan isnt take in consideration BUT NOT FAR !!!
    Point3D test = _pt;// test should be replace with newPoint
    test.x *= near/center.x;
    test.y *= near/center.y;
    test.z = (test.z*((-far+near)/(far-near))+((-2*far*near)/(far-near)));
//
//    test = test / test.w; // normilize
    //clip the point
//    if(test.x > _pt.w && test.x < -_pt.w &&
//       test.y > _pt.w && test.y < -_pt.w &&
//       test.z > _pt.w && test.z < -_pt.w )
//    {
//        return true;
//    }
//    if(test.x > _pt.w) { test.x =  _pt.w;}
//    if (test.x < -_pt.w) {_pt.x = -_pt.w;}
//    if (test.y > _pt.w) {_pt.y = _pt.w;}
//    if (test.y < -_pt.w) {_pt.y = -_pt.w;}
//    if (test.z > _pt.w) {_pt.z = _pt.w;}
//    if (test.z < -_pt.w) {_pt.z = -_pt.w;}

    if(test.x > _pt.w || test.x < -_pt.w ||
       test.y > _pt.w || test.y < -_pt.w ||
       test.z > _pt.w || test.z < -_pt.w )
    {
        return true;
    }
    return false;

}

Point2D Draw2D::project(const Point3D &_pt)
{
    Point3D newPoint = _pt;

//    newPoint = newPoint/newPoint.w;

    Point2D result(newPoint.x/(newPoint.z+0.1),newPoint.y/(newPoint.z+0.1));// + 0.1 prevent the 0 division
    result = result*f;
    result.x = result.x/dx;
    result.y = result.y/dy;

    return result+center;
}

void Draw2D::drawSegment(SDL_Surface *screen,Point3D _ptA, Point3D _ptB, Uint8 r, Uint8 g, Uint8 b)
{
//    Point2D ptA = _ptA.convertPerspective();
//    Point2D ptB = _ptB.convertPerspective();

        // camera pin hole

    bool ptAOut = false, ptBOut = false;

    Point3D ptA = _ptA;
    ptAOut = modelview(ptA);

    Point3D ptB = _ptB;
    ptBOut = modelview(ptB);

    if(ptAOut && ptBOut) {return;}

    if (ptAOut && !ptBOut)// A is out
    {
        char lrbtnf = 0b000000;

        if (ptA.x < 0) { lrbtnf += 0b100000;}
        if (ptA.w - ptA.x < 0) { lrbtnf += 0b010000;}
        if (ptA.y < 0) { lrbtnf += 0b001000;}
        if (ptA.w - ptA.y < 0) { lrbtnf += 0b000100;}
        if (ptA.z < 0) { lrbtnf += 0b000010;}
        if (ptA.w - ptA.z < 0) { lrbtnf += 0b000001;}

        // maybe put some if here, check on which plan the point is out and then make the project on the plane
        if(ptA.w+ptA.x<=0)
        {
            float a = (ptA.w+ptA.x)/((ptA.w+ptA.x)-(ptB.w+ptB.x));
            ptA = ptA*(1.0-a)+ptB*a;
        }
        if(ptA.w-ptA.x<=0)
        {
            float a = (ptA.w-ptA.x)/((ptA.w-ptA.x)-(ptB.w-ptB.x));
            ptA = ptA*(1.0-a)+ptB*a;
        }
        if(ptA.w+ptA.y<=0)
        {
            float a = (ptA.w+ptA.y)/((ptA.w+ptA.y)-(ptB.w+ptB.y));
            ptA = ptA*(1.0-a)+ptB*a;
        }
        if(ptA.w-ptA.y<=0)
        {
            float a = (ptA.w-ptA.y)/((ptA.w-ptA.y)-(ptB.w-ptB.y));
            ptA = ptA*(1.0-a)+ptB*a;
        }

    }
    else if (!ptAOut && ptBOut)// B is out
    {
        if(ptB.w+ptB.x<=0)
        {
            float a = (ptB.w+ptB.x)/((ptB.w+ptB.x)-(ptA.w+ptA.x));
            ptB = ptB*(1.0-a)+ptA*a;
        }
        if(ptB.w-ptB.x<=0)
        {
            float a = (ptB.w-ptB.x)/((ptB.w-ptB.x)-(ptA.w-ptA.x));
            ptB = ptB*(1.0-a)+ptA*a;
        }
        if(ptB.w-ptB.y<=0)
        {
            float a = (ptB.w-ptB.y)/((ptB.w-ptB.y)-(ptA.w-ptA.y));
            ptB = ptB*(1.0-a)+ptA*a;
        }
        if(ptB.w+ptB.y<=0)
        {
            float a = (ptB.w+ptB.y)/((ptB.w+ptB.y)-(ptA.w+ptA.y));
            ptB = ptB*(1.0-a)+ptA*a;
        }
    }

    Point2D result1 = project(ptA);
    Point2D result2 = project(ptB);

    drawSegment(screen, result1.x,result1.y,result2.x,result2.y,r,g,b);
}

//TODO have to clean up
void Draw2D::drawSegment(SDL_Surface *screen,Segment3D _segment, Uint8 r, Uint8 g, Uint8 b)
{
    drawSegment(screen,(*_segment.getPointA()),(*_segment.getPointB()),r,g,b);
}

void Draw2D::setPixel(SDL_Surface *screen,Point2D _pt, Uint8 R, Uint8 G, Uint8 B)
{
    setPixel(screen,_pt.getX(),_pt.getY(),R,G,B);
}

// reference : http://www.libsdl.org/intro.en/usingvideo.html
void Draw2D::setPixel(SDL_Surface *screen,int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
    if(y<1 || y>479 || x<1 || x>639) { return ;}
    Uint32 color = SDL_MapRGB(screen->format, R, G, B);

    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            return;
        }
    }
    switch (screen->format->BytesPerPixel) {
        case 1: { /* Assuming 8-bpp */
            Uint8 *bufp;

            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
            *bufp = color;
        }
        break;

        case 2: { /* Probably 15-bpp or 16-bpp */
            Uint16 *bufp;

            bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
            *bufp = color;
        }
        break;

        case 3: { /* Slow 24-bpp mode, usually not used */
            Uint8 *bufp;

            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
            *(bufp+screen->format->Rshift/8) = R;
            *(bufp+screen->format->Gshift/8) = G;
            *(bufp+screen->format->Bshift/8) = B;
        }
        break;

        case 4: { /* Probably 32-bpp */
            Uint32 *bufp;

            bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
            *bufp = color;
        }
        break;
    }
    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }
//    SDL_UpdateRect(screen, x, y, 1, 1);
}


void Draw2D::setWhitePixel(SDL_Surface *screen,int x, int y)\
{
    setPixel(screen, x, y, 255, 255, 255);
}

void Draw2D::drawCube(SDL_Surface *screen,Cube _cube)
{
    drawCube(screen, _cube.pt1, _cube.pt2, _cube.pt3, _cube.pt4);
}

void Draw2D::drawCube(SDL_Surface *screen,Point3D _pt1, Point3D _pt2, Point3D _pt3, Point3D _pt4)
{
    //   4----6
    //  /|   /|
    //  7----8|
    //  |1---|2
    //  |/   |/
    //  3----5

    // with the 4 points we can find the 4 others
    Point3D pt5 = _pt2+_pt3-_pt1;
    Point3D pt6 = _pt2+_pt4-_pt1;
    Point3D pt7 = _pt3+_pt4-_pt1;
    Point3D pt8 = pt5+_pt4-_pt1;

    // construct all segments
    Segment3D seg1(_pt1,_pt2);
    Segment3D seg2(_pt1,_pt3);
    Segment3D seg3(_pt1,_pt4);
    Segment3D seg4(_pt3,pt5);
    Segment3D seg5(pt5,pt8);
    Segment3D seg6(pt5,_pt2);
    Segment3D seg7(_pt3,pt7);
    Segment3D seg8(_pt2,pt6);
    Segment3D seg9(pt7,_pt4);
    Segment3D seg10(_pt4,pt6);
    Segment3D seg11(pt6,pt8);
    Segment3D seg12(pt7,pt8);

    // draw all segments
    drawSegment(screen,seg1);
    drawSegment(screen,seg2);
    drawSegment(screen,seg3);
    drawSegment(screen,seg4);
    drawSegment(screen,seg5);
    drawSegment(screen,seg6);
    drawSegment(screen,seg7);
    drawSegment(screen,seg8);
    drawSegment(screen,seg9);
    drawSegment(screen,seg10);
    drawSegment(screen,seg11);
    drawSegment(screen,seg12);
}

void Draw2D::setXangle(float _angle)
{
    xangle+=_angle;
    if(xangle>PI/2) {xangle = PI/2;}
    else if (xangle< -PI/2) {xangle = -PI/2;}
}

void Draw2D::setYangle(float _angle)
{
    yangle+=_angle;
    if(yangle>2*PI) {yangle -= 2*PI;}
    else if (yangle<0) {yangle += 2*PI;}
}

void Draw2D::setZangle(float _angle)
{
    zangle+=_angle;
    if(zangle>PI/2) {zangle = PI/2;}
    else if (zangle< -PI/2) {zangle = -PI/2;}
}
