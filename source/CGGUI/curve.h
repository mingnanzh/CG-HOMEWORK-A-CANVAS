#ifndef CURVE_H
#define CURVE_H

#include "shape.h"

class Curve : public Shape
{
public:
        Curve();

        void paint(QPainter &painter);

};

#endif // CURVE_H
