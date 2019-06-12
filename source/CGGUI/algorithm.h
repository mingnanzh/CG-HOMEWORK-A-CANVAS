#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <string>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct Primitive_* Primitive;
typedef struct Line_* Linee;
typedef struct Polygon_* Polygon;
typedef struct Ellipse_* Ellipse;
typedef struct Curve_* Curve;

struct Line_{
    float x1, y1, x2, y2;
    string algorithm;
    int R, G, B;
};

struct Polygon_{
    int n;
    vector<float> x;
    vector<float> y;
    string algorithm;
    int R, G, B;
};

struct Ellipse_{
    float x, y, rx, ry;
    int R, G, B;
};

struct Curve_{
    int n;
    vector<float> x;
    vector<float> y;
    string algorithm;
    int R, G, B;
};

struct Primitive_{
    int id;
    enum kind{LINE, POLYGON, ELLIPSE, CURVE} kind;

    union
    {
        Linee line;
        Polygon polygon;
        Ellipse ellipse;
        Curve curve;
    }u;

    Primitive next;
};

int sgn(float num);
QImage resetCanvas(int width, int height);
void saveCanvas(QImage &picture,string name);
void setColor(QPainter &painter, int R, int G, int B);
void drawLine(QPainter &painter, float x1, float y1, float x2, float y2, string algorithm);
void drawPolygon(QPainter &painter, int n, vector<float> &x, vector<float> &y, string algorithm);
void drawEllipse(QPainter &painter, float x, float y, float rx, float ry);
void drawCurve(QPainter &painter, int n, vector<float> &x, vector<float> &y, string algorithm);
void translate(QPainter &painter, int id, float dx, float dy);
void rotate(QPainter &painter, int id, float x, float y, float r);
void scale(QPainter &painter, int id, float x, float y, float s);
void paintevent();


#endif // ALGORITHM_H
