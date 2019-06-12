#include "ellipse.h"

Elli::Elli()
{
}

void drawEllipse(QPainter &painter, float x, float y, float rx, float ry)
{
    int xc, yc;
    float p;
    int flag = (ry > rx)? 1 : 0;
    if(flag)
    {
        float temp;
        temp = rx; rx = ry; ry = temp;
    }
    xc = 0;
    yc = int(ry);
    p = float(ry * ry - rx * rx * ry + rx * rx * 0.25);
    while(rx * rx * yc > ry * ry * xc)
    {
        if(flag)
        {
            painter.drawPoint(int(x)+yc, (int(y)+xc));
            painter.drawPoint(int(x)+yc, (int(y)-xc));
            painter.drawPoint(int(x)-yc, (int(y)+xc));
            painter.drawPoint(int(x)-yc, (int(y)-xc));
        }
        else
        {
            painter.drawPoint(int(x)+xc, (int(y)+yc));
            painter.drawPoint(int(x)+xc, (int(y)-yc));
            painter.drawPoint(int(x)-xc, (int(y)+yc));
            painter.drawPoint(int(x)-xc, (int(y)-yc));
        }
        if(p > 0)
        {
            p += 2*ry*ry*xc - 2*rx*rx*yc + 2*rx*rx + 3*ry*ry;
            yc--;
        }
        else
            p += 2*ry*ry*xc + 3*ry*ry;
        xc++;
    }
    if(flag)
    {
        painter.drawPoint(int(x)+yc, (int(y)+xc));
        painter.drawPoint(int(x)+yc, (int(y)-xc));
        painter.drawPoint(int(x)-yc, (int(y)+xc));
        painter.drawPoint(int(x)-yc, (int(y)-xc));
    }
    else
    {
        painter.drawPoint(int(x)+xc, (int(y)+yc));
        painter.drawPoint(int(x)+xc, (int(y)-yc));
        painter.drawPoint(int(x)-xc, (int(y)+yc));
        painter.drawPoint(int(x)-xc, (int(y)-yc));
    }
    p = ry*ry*(xc+0.5)*(xc+0.5)+rx*rx*(yc-1)*(yc-1)-rx*rx*ry*ry;
    while (yc >= 0)
    {
        if(p < 0)
        {
            p += 2*ry*ry*xc - 2*rx*rx*yc + 2*ry*ry + 3*rx*rx;
            xc++;
        }
        else
            p += - 2*rx*rx*yc + 3*rx*rx;
        yc--;
        if(flag)
        {
            painter.drawPoint(int(x)+yc, (int(y)+xc));
            painter.drawPoint(int(x)+yc, (int(y)-xc));
            painter.drawPoint(int(x)-yc, (int(y)+xc));
            painter.drawPoint(int(x)-yc, (int(y)-xc));
        }
        else
        {
            painter.drawPoint(int(x)+xc, (int(y)+yc));
            painter.drawPoint(int(x)+xc, (int(y)-yc));
            painter.drawPoint(int(x)-xc, (int(y)+yc));
            painter.drawPoint(int(x)-xc, (int(y)-yc));
        }
    }
}

void Elli::paint(QPainter &painter)
{
    drawEllipse(painter, (start.x()+end.x())/2, (start.y()+end.y())/2, abs(end.x()-start.x())/2, abs(end.y()-start.y())/2);
}

