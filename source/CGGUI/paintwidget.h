#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QtGui>
#include <QDebug>
#include <QWidget>
#include <QFileDialog>
#include "shape.h"
#include "line.h"
#include "rect.h"
#include "poly.h"
#include "ellipse.h"
#include "curve.h"

class PaintWidget : public QWidget
{
        Q_OBJECT

public:
        PaintWidget(QWidget *parent = 0);

signals:
        void changecenterx(int x);
        void changecentery(int y);
        void changexmin(int x);
        void changexmax(int x);
        void changeymin(int y);
        void changeymax(int y);

public slots:
        void setCurrentShape(Shape::Code s)
        {
            if(s != currShapeCode) {
                currShapeCode = s;
            }
            stop = true;
            select = false;
            selectfirst = false;
            selectsecond = false;
            ready=false;
        }

        void settargetid(int i)
        {
            targetid = i;
        }

        void setdx(int x)
        {
            dx = x;
        }

        void setdy(int y)
        {
            dy = -y;
        }

        void savefile()
        {
            QString filename = QFileDialog::getSaveFileName(this,
                tr("Save Canvas"), "",
                tr("BMP Image (*.bmp);; PNG Image (*.png);; JPG Image (*jpg);; All Files (*.*)"));
            QPixmap pixmap(this->size());
            this->render(&pixmap);
            pixmap.save(filename);
        }

        void clearall()
        {
            shapeList.clear();
            shapenum = 0;
            perm = true;
            stop = true;
            select = false;
            selectfirst = false;
            selectsecond = false;
            ready=false;
            currShapeCode = Shape::null;
            update();
        }

        void translatetarget()
        {
            foreach(Shape * shape, shapeList) {
                if(shape->getid() == targetid)
                    shape->translate(dx, dy);
            }
            update();
        }

        void rotatetarget()
        {
            foreach(Shape * shape, shapeList) {
                if(shape->getid() == targetid)
                    shape->rotate(centerx, centery, 360-r);
            }
            update();
        }

        void scaletarget()
        {
            foreach(Shape * shape, shapeList) {
                if(shape->getid() == targetid)
                    shape->scale(centerx, centery, s);
            }
            update();
        }

        void cliptarget1()
        {
            foreach(Shape * shape, shapeList) {
                if(shape->getid() == targetid)
                    shape->clip1(xmin, ymax, xmax, ymin);
            }
            update();
        }

        void cliptarget2()
        {
            foreach(Shape * shape, shapeList) {
                if(shape->getid() == targetid)
                    shape->clip2(xmin, ymax, xmax, ymin);
            }
            update();
        }

        void setR(int R)
        {
            currR = R;
        }

        void setG(int G)
        {
            currG = G;
        }

        void setB(int B)
        {
            currB = B;
        }

        void enableselect()
        {
            perm = true;
            stop = true;
            select = true;
            selectfirst = false;
            selectsecond = false;
            ready=false;
            currShapeCode=Shape::null;
        }

        void enableselectfirst()
        {
            perm = true;
            stop = true;
            select = false;
            selectfirst = true;
            selectsecond = false;
            ready=false;
            currShapeCode = Shape::null;
        }

        void enableselectsecond()
        {
            perm = true;
            stop = true;
            select = false;
            selectfirst = false;
            selectsecond = true;
            ready=false;
            currShapeCode = Shape::null;
        }

        void setcenterx(int x)
        {
            centerx=x;
        }

        void setcentery(int y)
        {
            centery = height() - y;
        }

        void sets(int ss)
        {
            s = ss / 10.0;
        }

        void setr(int rr)
        {
            r = rr / 10.0;
        }

        void setxmin(int x)
        {
            xmin = x;
        }

        void setxmax(int x)
        {
            xmax = x;
        }

        void setymin(int y)
        {
            ymin = height() - y;
        }

        void setymax(int y)
        {
            ymax = height() - y;
        }

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

private:
        Shape::Code currShapeCode=Shape::null;
        Shape *shape;
        int shapenum=0;
        bool perm=true;
        bool stop=true;
        bool ready=false;
        bool select=false;
        bool selectfirst=false;
        bool selectsecond=false;
        QList<Shape*> shapeList;
        int currR = 0;
        int currG = 0;
        int currB = 0;
        int targetid = 0;
        int dx=0, dy=0;
        int centerx = 450, centery=450;
        float r = 0.0;
        float s = 1.0;
        int xmin = 0, ymin = 0, xmax = 0, ymax = 0;
};

#endif // PAINTWIDGET_H
