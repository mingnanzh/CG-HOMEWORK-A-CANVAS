#include "poly.h"

Poly::Poly()
{
}

void Poly::paint(QPainter &painter)
{
    int n = point_num;
    for(int i = 0; i < n-1; i++)
        drawLine(painter, x[i], y[i], x[i+1], y[i+1], algorithm);
    drawLine(painter, x[n-1], y[n-1], x[0], y[0], algorithm);
}

