#ifndef LINE_H
#define LINE_H

#include "shape.h"

int sgn(float num);

void drawLine(QPainter &painter, float x1, float y1, float x2, float y2, string algorithm);

class Line : public Shape
{
public:
        Line();

        void paint(QPainter &painter);
};

#endif // LINE_H
