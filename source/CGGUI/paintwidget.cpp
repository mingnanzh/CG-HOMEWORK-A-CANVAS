#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent)
        : QWidget(parent), currShapeCode(Shape::Line), shape(nullptr), perm(false)
{
    setFixedSize(900,900);
    currShapeCode = Shape::null;
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.drawRect(-1, -1, size().width()+1, size().height()+1);
    foreach(Shape * shape, shapeList) {
        painter.setPen(shape->getcolor());
        shape->paint(painter);
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if(select)
    {
        QPoint temp = event->pos();
        emit changecenterx(temp.x());
        emit changecentery(height()-temp.y());
        return;
    }

    if(selectfirst)
    {
        QPoint temp = event->pos();
        emit changexmin(temp.x());
        emit changeymin(height()-temp.y());
        return;
    }

    if(selectsecond)
    {
        QPoint temp = event->pos();
        emit changexmax(temp.x());
        emit changeymax(height()-temp.y());
        return;
    }

    if (event->button() == Qt::RightButton)
    {
        stop = true;
        /*
        switch(currShapeCode)
        {
            case Shape::Poly:
            {
                 shape = new Poly;
                 stop = false;
                 shapeList<<shape;
                 shape->setcolor(currR, currG, currB);
                 shape->setalgorithm("DDA");
                 shape->setid(++shapenum);
                 break;
            }
            case Shape::Poly2:
            {
                shape = new Poly;
                stop = false;
                shapeList<<shape;
                shape->setcolor(currR, currG, currB);
                shape->setalgorithm("Bresenham");
                shape->setid(++shapenum);
                break;
            }
            case Shape::Curve:
            {
                shape = new Curve;
                stop = false;
                shapeList<<shape;
                shape->setcolor(currR, currG, currB);
                shape->setalgorithm("Bezier");
                shape->setid(++shapenum);
                break;
            }
            case Shape::Curve2:
            {
                shape = new Curve;
                stop = false;
                shapeList<<shape;
                shape->setcolor(currR, currG, currB);
                shape->setalgorithm("B-spline");
                shape->setid(++shapenum);
                break;
            }
        }
        */
    }
    else if (event->button() == Qt::LeftButton) {
        switch(currShapeCode)
        {
            case Shape::Line:
            {
                shape = new Line;
                perm = false;
                shapeList<<shape;
                shape->setStart(event->pos());
                shape->setEnd(event->pos());
                shape->setcolor(currR, currG, currB);
                shape->setalgorithm("DDA");
                shape->setid(++shapenum);
                break;
            }
            case Shape::Line2:
            {
                shape = new Line;
                perm = false;
                shapeList<<shape;
                shape->setStart(event->pos());
                shape->setEnd(event->pos());
                shape->setcolor(currR, currG, currB);
                shape->setalgorithm("Bresenham");
                shape->setid(++shapenum);
                break;
            }
            case Shape::Rect:
            {
                shape = new Rect;
                perm = false;
                shapeList<<shape;
                shape->setStart(event->pos());
                shape->setEnd(event->pos());
                shape->setcolor(currR, currG, currB);
                shape->setid(++shapenum);
                break;
            }
            case Shape::Poly:
            {
                if(stop)
                {
                    shape = new Poly;
                    stop = false;
                    shapeList<<shape;
                    shape->setcolor(currR, currG, currB);
                    shape->setalgorithm("DDA");
                    shape->setid(++shapenum);
                    shape->pushpoint(event->pos());
                }
                else if(!stop)
                {
                    shape->pushpoint(event->pos());
                    update();
                }
                break;
            }
            case Shape::Poly2:
            {
                if(stop)
                {
                    shape = new Poly;
                    stop = false;
                    shapeList<<shape;
                    shape->setcolor(currR, currG, currB);
                    shape->setalgorithm("Bresenham");
                    shape->setid(++shapenum);
                    shape->pushpoint(event->pos());
                }
                else if(!stop)
                {
                    shape->pushpoint(event->pos());
                    update();
                }
                break;
            }
            case Shape::Elli:
            {
                shape = new Elli;
                perm = false;
                shapeList<<shape;
                shape->setStart(event->pos());
                shape->setEnd(event->pos());
                shape->setcolor(currR, currG, currB);
                shape->setid(++shapenum);
                break;
            }
            case Shape::Curve:
            {
                if(stop)
                {
                    shape = new Curve;
                    stop = false;
                    shapeList<<shape;
                    shape->setcolor(currR, currG, currB);
                    shape->setalgorithm("Bezier");
                    shape->setid(++shapenum);
                    shape->pushpoint(event->pos());
                }
                else if(!stop)
                {
                    shape->pushpoint(event->pos());
                    update();
                }
                break;
            }
            case Shape::Curve2:
            {
                if(stop)
                {
                    shape = new Curve;
                    stop = false;
                    shapeList<<shape;
                    shape->setcolor(currR, currG, currB);
                    shape->setalgorithm("B-spline");
                    shape->setid(++shapenum);
                    shape->pushpoint(event->pos());
                }
                else if(!stop)
                {
                    shape->pushpoint(event->pos());
                    update();
                }
                break;
            }
            default: ;
        }
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    switch(currShapeCode)
    {
        case Shape::Line:
        {
            if(shape && !perm) {
                shape->setEnd(event->pos());
                update();
            }
            break;
        }
        case Shape::Line2:
        {
            if(shape && !perm) {
                shape->setEnd(event->pos());
                update();
            }
            break;
        }
        case Shape::Rect:
        {
            if(shape && !perm) {
                shape->setEnd(event->pos());
                update();
            }
            break;
        }
        case Shape::Elli:
        {
            if(shape && !perm) {
                shape->setEnd(event->pos());
                update();
            }
            break;
        }
        default: ;
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
        perm = true;
}
