#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>
#include <QPainter>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

static float Pi = 3.1415926535;

class Shape
{
public:

        enum Code {
                Line,
                Line2,
                Rect,
                Poly,
                Poly2,
                Elli,
                Curve,
                Curve2,
                null
        }kind;

        Shape();

        Code getkind()
        {
            return kind;
        }

        void setStart(QPoint s)
        {
                start = s;
        }

        void setEnd(QPoint e)
        {
                end = e;
        }

        void pushpoint(QPoint p)
        {
            x.push_back(p.x());
            y.push_back(p.y());
            point_num++;
        }

        void setcolor(int r, int g, int b)
        {
            R=r;
            G=g;
            B=b;
        }

        void setalgorithm(string al)
        {
            algorithm = al;
        }

        void setid(int i)
        {
            id = i;
        }

        QPoint startPoint()
        {
                return start;
        }

        QPoint endPoint()
        {
                return end;
        }

        QColor getcolor()
        {
            return QColor(R,G,B);
        }

        int getid()
        {
            return id;
        }

        void translate(int dx, int dy)
        {
            start = QPoint(start.x()+dx, start.y()+dy);
            end = QPoint(end.x()+dx, end.y()+dy);
            for (vector<float>::iterator iter = x.begin(); iter != x.end(); iter++)
                (*iter) += dx;
            for (vector<float>::iterator iter = y.begin(); iter != y.end(); iter++)
                (*iter) += dy;
        }

        void rotate(float cx, float cy, float r)
        {
            float x1 = start.x();
            float y1 = start.y();
            float x2 = end.x();
            float y2 = end.y();
            float xx, yy;
            xx = (x1 - cx) * cos(Pi*r/180) + (y1 - cy) * sin(Pi*r/180) + cx;
            yy = (y1 - cy) * cos(Pi*r/180) - (x1 - cx) * sin(Pi*r/180) + cy;
            start = QPoint(xx, yy);
            xx = (x2 - cx) * cos(Pi*r/180) + (y2 - cy) * sin(Pi*r/180) + cx;
            yy = (y2 - cy) * cos(Pi*r/180) - (x2 - cx) * sin(Pi*r/180) + cy;
            end = QPoint(xx, yy);
            for (int i = 0; i < point_num; i++) {
                xx = (x[i] - cx) * cos(Pi*r/180) + (y[i] - cy) * sin(Pi*r/180) + cx;
                yy = (y[i] - cy) * cos(Pi*r/180) - (x[i] - cx) * sin(Pi*r/180) + cy;
                x[i] = xx;
                y[i] = yy;
            }
        }

        void scale(float cx, float cy, float s)
        {
            start = QPoint((start.x()-cx)*s+cx, (start.y()-cy)*s+cy);
            end = QPoint((end.x()-cx)*s+cx, (end.y()-cy)*s+cy);
            for (vector<float>::iterator iter = x.begin(); iter != x.end(); iter++)
                (*iter) = ((*iter) - cx) * s + cx;
            for (vector<float>::iterator iter = y.begin(); iter != y.end(); iter++)
                (*iter) = ((*iter) - cy) * s + cy;
        }

        void clip1(float xmin, float ymin, float xmax,  float ymax)
        {
            float x1 = start.x();
            float y1 = start.y();
            float x2 = end.x();
            float y2 = end.y();
            while (1)
            {
                int C1=0, C2=0;
                if (x1 < xmin)
                    C1 += 1;
                if (x1 > xmax)
                    C1 += 2;
                if (y1 < ymin)
                    C1 += 4;
                if (y1 > ymax)
                    C1 += 8;
                if (x2 < xmin)
                    C2 += 1;
                if (x2 > xmax)
                    C2 += 2;
                if (y2 < ymin)
                    C2 += 4;
                if (y2 > ymax)
                    C2 += 8;
                if ((C1&C2) != 0)
                {
                    start = QPoint(0, 0);
                    end = QPoint(0, 0);
                    break;
                }
                if (C1==0 && C2==0)
                {
                    start = QPoint(x1, y1);
                    end = QPoint(x2, y2);
                    break;
                }
                if (C1 == 0)
                {
                    float xtemp, ytemp;
                    xtemp=x1;
                    x1=x2;
                    x2=xtemp;
                    ytemp=y1;
                    y1=y2;
                    y2=ytemp;
                    int Ctemp;
                    Ctemp=C1;
                    C1=C2;
                    C2=Ctemp;
                }
                if (C1&8)
                {
                    x1 = (ymax - y1)*(x2-x1)/(y2-y1) + x1;
                    y1 = ymax;
                }
                else if(C1&4)
                {
                    x1 = (ymin - y1)*(x2-x1)/(y2-y1) + x1;
                    y1 = ymin;
                }
                else if(C1&2)
                {
                    y1 = (y2-y1)*(xmax-x1)/(x2-x1) + y1;
                    x1 = xmax;
                }
                else if(C1&1)
                {
                    y1 = (y2-y1)*(xmin-x1)/(x2-x1) + y1;
                    x1 = xmin;
                }
            }
        }

        void clip2(float xmin, float ymin, float xmax,  float ymax)
        {
            bool flag = false;
            float u1 = 0, u2 = 1;
            float p[4], q[4];
            float r;
            p[0]=start.x() - end.x();
            p[1]=end.x() - start.x();
            p[2]=start.y() - end.y();
            p[3]=end.y() - start.y();
            q[0]=start.x() - xmin;
            q[1]=xmax - start.x();
            q[2]=start.y() - ymin;
            q[3]=ymax - start.y();

            for (int i = 0; i < 4; i++) {
                r = q[i]/p[i];
                if (p[i] < 0)
                {
                    u1 = max(u1, r);
                    if (u1 > u2)
                        flag = true;
                }
                if (p[i] > 0)
                {
                    u2 = min(u2, r);
                    if (u1 > u2)
                        flag = true;
                }
                if (p[i] == 0 && q[i] < 0)
                    flag = true;
            }
            if (flag)
            {
                start = QPoint(0, 0);
                end = QPoint(0, 0);
            }
            else
            {
                float x1 = start.x() + u1*(end.x()-start.x());
                float y1 = start.y() + u1*(end.y()-start.y());
                float x2 = start.x() + u2*(end.x()-start.x());
                float y2 = start.y() + u2*(end.y()-start.y());
                start = QPoint(x1, y1);
                end = QPoint(x2, y2);
            }
        }

        void virtual paint(QPainter & painter) = 0;

protected:
        int id;
        QPoint start;
        QPoint end;
        vector<float> x;
        vector<float> y;
        int point_num=0;
        string algorithm;
        int R;
        int G;
        int B;
};

#endif // SHAPE_H
