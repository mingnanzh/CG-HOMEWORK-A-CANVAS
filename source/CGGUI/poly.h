#ifndef POLY_H
#define POLY_H

#include "shape.h"
#include "line.h"

class Poly : public Shape
{
public:
        Poly();

        void paint(QPainter &painter);
};

#endif // POLY_H
