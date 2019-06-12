#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QAction>
#include <QIcon>
#include <QPushButton>
#include <QToolBar>
#include <QStatusBar>
#include <QActionGroup>
#include <QSpinBox>
#include <QSlider>
#include <QLayout>
#include "shape.h"
#include "paintwidget.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT

public:
        MainWindow(QWidget *parent = 0);

signals:
        void changeCurrentShape(Shape::Code newShape);
        void changeanglelabel(QString s);
        void changescalelabel(QString s);

private slots:
        void drawLineActionTriggered();
        void drawLine2ActionTriggered();
        void drawRectActionTriggered();
        void drawElliActionTriggered();
        void drawPolyActionTriggered();
        void drawPoly2ActionTriggered();
        void drawCurveActionTriggered();
        void drawCurve2ActionTriggered();
        void angleValueChanged(int s);
        void scaleValueChanged(int s);
};

#endif // MAINWINDOW_H
