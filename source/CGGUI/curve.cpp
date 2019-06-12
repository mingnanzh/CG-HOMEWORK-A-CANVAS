#include "curve.h"

Curve::Curve()
{
}

void drawCurve(QPainter &painter, int n, vector<float> &x, vector<float> &y, string algorithm)
{
    if (algorithm == "Bezier")
    {
        for (double u = 0.0; u <= 1.0; u += 0.0001){
            int loop = n-1;
            int power = 0;
            vector<float> old_x = x;
            vector<float> old_y = y;
            while (loop > 0)
            {
                vector<float> new_x;
                vector<float> new_y;
                for(int i=0; i < loop; i++)
                {
                    new_x.push_back((1-u)*old_x[i] + u*old_x[i+1]);
                    new_y.push_back((1-u)*old_y[i] + u*old_y[i+1]);

                }
                old_x = new_x;
                old_y = new_y;
                loop--;
                power++;
            }
            painter.drawPoint(old_x[0], old_y[0]);
        }
    }
    else if (algorithm == "B-spline")
    {
        n = n-1;
        int i = 0;
        float px, py;
        while (i < n-1) {
            for (double u = 0; u<= 1; u += 0.0001) {
                px = ((u*u-2*u+1)*x[i] + (-2*u*u+2*u+1)*x[i+1] + u*u*x[i+2])/2;
                py = ((u*u-2*u+1)*y[i] + (-2*u*u+2*u+1)*y[i+1] + u*u*y[i+2])/2;
                painter.drawPoint(px, py);
            }
            i++;
        }
    }
}

void Curve::paint(QPainter &painter)
{
    drawCurve(painter, point_num, x, y, algorithm);
}
