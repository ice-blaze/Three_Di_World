// -----------------------------------------
// | Title       : three_di_world          |
// | Author      : Ice-Blaze               |
// | Start date  : 10.07.2013              |
// | Poject on a plan, a 3D linear algebra |
// -----------------------------------------

#ifndef POINT2D_H
#define POINT2D_H


class Point2D
{
    public:
        Point2D(float _x=0.0f, float _y=0.0f);
        Point2D(Point2D const& _point);
        virtual ~Point2D();

        Point2D operator + (Point2D _secondPoint);
        Point2D operator - (Point2D _secondPoint);
        Point2D operator * (float _mul);
        Point2D operator / (float _div);

        float getX() {return x;};
        float getY() {return y;};

        void setX(float _x) {x = _x;};
        void setY(float _y) {y = _y;};

        float x;
        float y;
};

#endif // POINT2D_H
