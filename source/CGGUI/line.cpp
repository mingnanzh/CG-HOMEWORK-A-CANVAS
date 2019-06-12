#include "line.h"

Line::Line()
{
}

int sgn(float num)
{
    if(num>0)
        return 1;
    else if (num<0)
        return -1;
    else
        return 0;
}

void drawLine(QPainter &painter, float x1, float y1, float x2, float y2, string algorithm)
{
    float px;
    float py;
    if((x1 == x2) && (y1 == y2))
    {
        painter.drawPoint(x1, y1);
        return;
    }
    if(algorithm == "DDA")
    {
        if(int(x2-x1) != 0)
        {
            float m = (y2 - y1) / (x2 - x1);
            if(abs(m) <= 1)
            {
                py=y1;
                for(px = x1; sgn(x2 - x1) * px <= sgn(x2 - x1) * x2; px += sgn(x2 - x1))
                {
                    painter.drawPoint(int(px), int(py));
                    py += sgn(x2 - x1) * m;
                }
            }
            else
            {
                px = x1;
                for(py = y1; sgn(y2 - y1) * py <= sgn(y2 - y1) * y2; py += sgn(y2 - y1))
                {
                    painter.drawPoint(int(px), int(py));
                    px += sgn(y2 - y1) * (1 / m);
                }
            }
        }
        else
        {
            px = x1;
            for(py = y1; sgn(y2 - y1) * py <= sgn(y2 - y1) * y2; py += sgn(y2 - y1))
            {
                painter.drawPoint(int(px), int(py));
            }
        }

    }
    else if(algorithm == "Bresenham"){
        float x, y, dx, dy, p;
        dx = x2 - x1;
        dy = y2 - y1;
        float flag = abs(dx) - abs(dy);

        if(flag < 0)
        {
            float temp;
            temp = y1; y1 = x1; x1 = temp;
            temp = y2; y2 = x2; x2 = temp;
        }

        dx = x2 - x1;
        dy = y2 - y1;
        p = 2 * abs(dy) - abs(dx);
        x = x1;
        y = y1;
        float X_inc = (dx > 0) ? 1 : -1;
        float Y_inc = (dy == 0) ? 0 : dy / abs(dy);

        for(int i = 0; i <= abs(dx) - 1 ; i++)
        {
            if(flag < 0)
                painter.drawPoint(int(y), int(x));
            else
                painter.drawPoint(int(x), int(y));
            if(p < 0)
                p += 2 * abs(dy);
            else
            {
                y += Y_inc;
                p += 2 * (abs(dy) - abs(dx));
            }
            x += X_inc;
        }
    }
}

void Line::paint(QPainter &painter)
{
    drawLine(painter, start.x(), start.y(), end.x(), end.y(), algorithm);
}
