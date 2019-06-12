#include "rect.h"
#include "line.h"

Rect::Rect()
{
}

void Rect::paint(QPainter &painter)
{
        drawLine(painter, start.x(), start.y(), start.x(), end.y(), "DDA");
        drawLine(painter, start.x(), end.y(), end.x(), end.y(), "DDA");
        drawLine(painter, end.x(), end.y(), end.x(), start.y(), "DDA");
        drawLine(painter, end.x(), start.y(), start.x(), start.y(), "DDA");
}

