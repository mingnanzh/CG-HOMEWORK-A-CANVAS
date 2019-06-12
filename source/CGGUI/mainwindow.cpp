#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    this->setFixedSize(1300, 1000);
    PaintWidget *paintWidget = new PaintWidget(this);
    QSpinBox *idbox = new QSpinBox;
    idbox->setRange(0,100000);
    QLabel *idlabel = new QLabel;
    idlabel->setText("Target id:");
    QSpinBox *dxbox = new QSpinBox;
    dxbox->setRange(-paintWidget->width(), paintWidget->width());
    dxbox->setValue(0);
    QLabel *dxlabel = new QLabel;
    dxlabel->setText("dx:");
    QSpinBox *dybox = new QSpinBox;
    dybox->setRange(-paintWidget->height(), paintWidget->height());
    dybox->setValue(0);
    QLabel *dylabel = new QLabel;
    dylabel->setText("dy:");
    QPushButton *translatebutton = new QPushButton;
    translatebutton->setText("Translate");
    translatebutton->setIcon(QIcon(":/translate.png"));
    QLabel *centerpoint = new QLabel;
    centerpoint->setText("Center Point");
    centerpoint->setAlignment(Qt::AlignCenter);
    QSpinBox *xbox = new QSpinBox;
    xbox->setRange(-paintWidget->width(), paintWidget->width());
    xbox->setValue(0);
    QLabel *xlabel = new QLabel;
    xlabel->setText("x:");
    QSpinBox *ybox = new QSpinBox;
    ybox->setRange(-paintWidget->height(), paintWidget->height());
    ybox->setValue(0);
    QLabel *ylabel = new QLabel;
    ylabel->setText("y:");
    QSlider *rslider = new QSlider(Qt::Horizontal);
    rslider->setRange(0, 3600);
    rslider->setValue(0);
    QLabel *rlabel = new QLabel;
    rlabel->setText("r:");
    QLabel *r = new QLabel;
    r->setText(u8"0.0\u00b0");
    QPushButton *rotatebutton = new QPushButton;
    rotatebutton->setText("Rotate");
    rotatebutton->setIcon(QIcon(":/rotate.png"));
    QSlider *sslider = new QSlider(Qt::Horizontal);
    sslider->setRange(0, 30);
    sslider->setValue(10);
    QLabel *slabel = new QLabel;
    slabel->setText("s:");
    QLabel *s = new QLabel;
    s->setText(u8"1.0×");
    QPushButton *scalebutton = new QPushButton;
    scalebutton->setText("Scale");
    scalebutton->setIcon(QIcon(":/scale.png"));
    QLabel *clipwindowlabel = new QLabel;
    clipwindowlabel->setText("Clip Window");
    clipwindowlabel->setAlignment(Qt::AlignCenter);
    QLabel *xminlabel = new QLabel;
    xminlabel->setText("xmin:");
    QLabel *xmaxlabel = new QLabel;
    xmaxlabel->setText("xmax:");
    QLabel *yminlabel = new QLabel;
    yminlabel->setText("ymin:");
    QLabel *ymaxlabel = new QLabel;
    ymaxlabel->setText("ymax:");
    QSpinBox *xminbox = new QSpinBox;
    xminbox->setRange(0, paintWidget->width());
    xminbox->setValue(0);
    QSpinBox *xmaxbox = new QSpinBox;
    xmaxbox->setRange(0, paintWidget->width());
    xmaxbox->setValue(0);
    QSpinBox *yminbox = new QSpinBox;
    yminbox->setRange(0, paintWidget->height());
    yminbox->setValue(0);
    QSpinBox *ymaxbox = new QSpinBox;
    ymaxbox->setRange(0, paintWidget->height());
    ymaxbox->setValue(0);
    QPushButton *clipbutton1 = new QPushButton;
    clipbutton1->setText("Cohen-Sutherland");
    clipbutton1->setIcon(QIcon(":/clip.png"));
    QPushButton *clipbutton2 = new QPushButton;
    clipbutton2->setText("Liang-Barsky");
    clipbutton2->setIcon(QIcon(":/clip.png"));

    QSpinBox *Rbox = new QSpinBox;
    QSlider *Rslider = new QSlider(Qt::Vertical);
    QLabel *Rlabel = new QLabel;
    Rbox->setRange(0, 255);
    Rslider->setRange(0, 255);
    Rlabel->setText("R");
    Rlabel->setAlignment(Qt::AlignCenter);
    Rbox->setValue(0);
    QSpinBox *Gbox = new QSpinBox;
    QSlider *Gslider = new QSlider(Qt::Vertical);
    QLabel *Glabel = new QLabel;
    Gbox->setRange(0, 255);
    Gslider->setRange(0, 255);
    Glabel->setText("G");
    Glabel->setAlignment(Qt::AlignCenter);
    Gbox->setValue(0);
    QSpinBox *Bbox = new QSpinBox;
    QSlider *Bslider = new QSlider(Qt::Vertical);
    QLabel *Blabel = new QLabel;
    Bbox->setRange(0, 255);
    Bslider->setRange(0, 255);
    Blabel->setText("B");
    Blabel->setAlignment(Qt::AlignCenter);

    QToolBar *bar = this->addToolBar("Tools");
    QActionGroup *group = new QActionGroup(bar);
    QAction *saveAction = new QAction("Save", bar);
    saveAction->setIcon(QIcon(":/save.png"));
    saveAction->setToolTip(tr("Save the canva."));
    saveAction->setStatusTip(tr("Save the canva."));
    saveAction->setCheckable(true);
    group->addAction(saveAction);
    bar->addAction(saveAction);
    QAction *clearAction = new QAction("Clean", bar);
    clearAction->setIcon(QIcon(":/clean.png"));
    clearAction->setToolTip(tr("Clean the canva."));
    clearAction->setStatusTip(tr("Clean the canva."));
    clearAction->setCheckable(true);
    clearAction->setChecked(true);
    clearAction->triggered(true);
    group->addAction(clearAction);
    bar->addAction(clearAction);
    QAction *drawLineAction = new QAction("Line1", bar);
    drawLineAction->setIcon(QIcon(":/line.png"));
    drawLineAction->setToolTip(tr("Draw a line using DDA algorithm."));
    drawLineAction->setStatusTip(tr("Draw a line using DDA algorithm."));
    drawLineAction->setCheckable(true);
    group->addAction(drawLineAction);
    bar->addAction(drawLineAction);
    QAction *drawLine2Action = new QAction("Line2", bar);
    drawLine2Action->setIcon(QIcon(":/line2.png"));
    drawLine2Action->setToolTip(tr("Draw a line using Bresenham algorithm."));
    drawLine2Action->setStatusTip(tr("Draw a line using Bresenham algorithm."));
    drawLine2Action->setCheckable(true);
    group->addAction(drawLine2Action);
    bar->addAction(drawLine2Action);
    QAction *drawRectAction = new QAction("Rectangle", bar);
    drawRectAction->setIcon(QIcon(":/rect.png"));
    drawRectAction->setToolTip(tr("Draw a rectangle."));
    drawRectAction->setStatusTip(tr("Draw a rectangle."));
    drawRectAction->setCheckable(true);
    group->addAction(drawRectAction);
    bar->addAction(drawRectAction);
    QAction *drawPolyAction = new QAction("Polygon1", bar);
    drawPolyAction->setIcon(QIcon(":/poly.png"));
    drawPolyAction->setToolTip(tr("Draw a polygon using DDA algorithm."));
    drawPolyAction->setStatusTip(tr("Draw a polygon using DDA algorithm."));
    drawPolyAction->setCheckable(true);
    group->addAction(drawPolyAction);
    bar->addAction(drawPolyAction);
    QAction *drawPoly2Action = new QAction("Polygon2", bar);
    drawPoly2Action->setIcon(QIcon(":/poly2.png"));
    drawPoly2Action->setToolTip(tr("Draw a polygon using Bresenham algorithm."));
    drawPoly2Action->setStatusTip(tr("Draw a polygon using Bresenham algorithm."));
    drawPoly2Action->setCheckable(true);
    group->addAction(drawPoly2Action);
    bar->addAction(drawPoly2Action);
    QAction *drawElliAction = new QAction("Ellipse", bar);
    drawElliAction->setIcon(QIcon(":/elli.png"));
    drawElliAction->setToolTip(tr("Draw an ellipse."));
    drawElliAction->setStatusTip(tr("Draw an ellipse."));
    drawElliAction->setCheckable(true);
    group->addAction(drawElliAction);
    bar->addAction(drawElliAction);
    QAction *drawCurveAction = new QAction("Bezier Curve", bar);
    drawCurveAction->setIcon(QIcon(":/curve.png"));
    drawCurveAction->setToolTip(tr("Draw a Bezier curve."));
    drawCurveAction->setStatusTip(tr("Draw a Bezier curve."));
    drawCurveAction->setCheckable(true);
    group->addAction(drawCurveAction);
    bar->addAction(drawCurveAction);
    QAction *drawCurve2Action = new QAction("B-spline Curve", bar);
    drawCurve2Action->setIcon(QIcon(":/curve2.png"));
    drawCurve2Action->setToolTip(tr("Draw a B-spline curve."));
    drawCurve2Action->setStatusTip(tr("Draw a B-spline curve."));
    drawCurve2Action->setCheckable(true);
    group->addAction(drawCurve2Action);
    bar->addAction(drawCurve2Action);
    QAction *selectAction = new QAction("Select", bar);
    selectAction->setIcon(QIcon(":/select.png"));
    selectAction->setToolTip(tr("Select a point as center point."));
    selectAction->setStatusTip(tr("Select a point as center point."));
    selectAction->setCheckable(true);
    group->addAction(selectAction);
    bar->addAction(selectAction);
    QAction *selectclipwindow1Action = new QAction("Select1", bar);
    selectclipwindow1Action->setIcon(QIcon(":/select1.png"));
    selectclipwindow1Action->setToolTip(tr("Select the first point of clip window."));
    selectclipwindow1Action->setStatusTip(tr("Select the first point of clip window."));
    selectclipwindow1Action->setCheckable(true);
    group->addAction(selectclipwindow1Action);
    bar->addAction(selectclipwindow1Action);
    QAction *selectclipwindow2Action = new QAction("Select1", bar);
    selectclipwindow2Action->setIcon(QIcon(":/select1.png"));
    selectclipwindow2Action->setToolTip(tr("Select the second point of clip window."));
    selectclipwindow2Action->setStatusTip(tr("Select the second point of clip window."));
    selectclipwindow2Action->setCheckable(true);
    group->addAction(selectclipwindow2Action);
    bar->addAction(selectclipwindow2Action);

    QLabel *statusMsg = new QLabel;
    statusBar()->addWidget(statusMsg);

    QHBoxLayout *targetidlayout = new QHBoxLayout;
    targetidlayout->addWidget(idlabel);
    targetidlayout->addWidget(idbox);
    Bbox->setValue(0);
    QHBoxLayout *dxdylayout = new QHBoxLayout;
    dxdylayout->addWidget(dxlabel);
    dxdylayout->addWidget(dxbox);
    dxdylayout->addWidget(dylabel);
    dxdylayout->addWidget(dybox);
    QHBoxLayout *translatebuttonlayout = new QHBoxLayout;
    translatebuttonlayout->addWidget(translatebutton);
    QVBoxLayout *translatelayout = new QVBoxLayout;
    translatelayout->addLayout(dxdylayout);
    translatelayout->addLayout(translatebuttonlayout);
    QHBoxLayout *centerpointlabellayout = new QHBoxLayout;
    centerpointlabellayout->addWidget(centerpoint);
    QHBoxLayout *xylayout = new QHBoxLayout;
    xylayout->addWidget(xlabel);
    xylayout->addWidget(xbox);
    xylayout->addWidget(ylabel);
    xylayout->addWidget(ybox);
    QVBoxLayout *centerpointlayout = new QVBoxLayout;
    centerpointlayout->addLayout(centerpointlabellayout);
    centerpointlayout->addLayout(xylayout);
    QHBoxLayout *rotatelayout = new QHBoxLayout;
    rotatelayout->addWidget(rlabel);
    rotatelayout->addWidget(r);
    rotatelayout->addWidget(rslider);
    rotatelayout->addWidget(rotatebutton);
    QHBoxLayout *scalelayout = new QHBoxLayout;
    scalelayout->addWidget(slabel);
    scalelayout->addWidget(s);
    scalelayout->addWidget(sslider);
    scalelayout->addWidget(scalebutton);
    QHBoxLayout *clipwindowlayout = new QHBoxLayout;
    clipwindowlayout->addWidget(clipwindowlabel);
    QHBoxLayout *clipwindowxlayout = new QHBoxLayout;
    clipwindowxlayout->addWidget(xminlabel);
    clipwindowxlayout->addWidget(xminbox);
    clipwindowxlayout->addWidget(xmaxlabel);
    clipwindowxlayout->addWidget(xmaxbox);
    QHBoxLayout *clipwindowylayout = new QHBoxLayout;
    clipwindowylayout->addWidget(yminlabel);
    clipwindowylayout->addWidget(yminbox);
    clipwindowylayout->addWidget(ymaxlabel);
    clipwindowylayout->addWidget(ymaxbox);
    QHBoxLayout *clipbuttonlayout = new QHBoxLayout;
    clipbuttonlayout->addWidget(clipbutton1);
    clipbuttonlayout->addWidget(clipbutton2);
    QVBoxLayout *cliplayout = new QVBoxLayout;
    cliplayout->addLayout(clipwindowlayout);
    cliplayout->addLayout(clipwindowxlayout);
    cliplayout->addLayout(clipwindowylayout);
    cliplayout->addLayout(clipbuttonlayout);
    QVBoxLayout *vrlayout = new QVBoxLayout;
    vrlayout->addWidget(Rslider);
    vrlayout->addWidget(Rbox);
    vrlayout->addWidget(Rlabel);
    QVBoxLayout *vglayout = new QVBoxLayout;
    vglayout->addWidget(Gslider);
    vglayout->addWidget(Gbox);
    vglayout->addWidget(Glabel);
    QVBoxLayout *vblayout = new QVBoxLayout;
    vblayout->addWidget(Bslider);
    vblayout->addWidget(Bbox);
    vblayout->addWidget(Blabel);
    QHBoxLayout *colorlayout = new QHBoxLayout;
    colorlayout->addLayout(vrlayout);
    colorlayout->addLayout(vglayout);
    colorlayout->addLayout(vblayout);
    QVBoxLayout *toollayout = new QVBoxLayout;
    toollayout->addLayout(targetidlayout);
    toollayout->addLayout(translatelayout);
    toollayout->addLayout(centerpointlayout);
    toollayout->addLayout(rotatelayout);
    toollayout->addLayout(scalelayout);
    toollayout->addLayout(cliplayout);
    toollayout->addLayout(colorlayout);
    toollayout->setSpacing(25);
    QHBoxLayout *paintwidgetlayout = new QHBoxLayout;
    paintwidgetlayout->addWidget(paintWidget);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addLayout(toollayout);
    hlayout->addLayout(paintwidgetlayout);
    toollayout->setMargin(10);
    QWidget *wi = new QWidget;
    wi->setLayout(hlayout);
    this->setCentralWidget(wi);
    this->setWindowTitle("Canvas");
    this->setIconSize(QSize(40,40));
    this->setWindowIcon(QIcon(":/canvas.png"));


    connect(idbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(settargetid(int)));
    connect(dxbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setdx(int)));
    connect(dybox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setdy(int)));
    connect(xbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setcenterx(int)));
    connect(ybox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setcentery(int)));
    connect(translatebutton, SIGNAL(clicked()), paintWidget, SLOT(translatetarget()));
    connect(sslider, SIGNAL(valueChanged(int)), this, SLOT(scaleValueChanged(int)));
    connect(this, SIGNAL(changescalelabel(QString)), s, SLOT(setText(QString)));
    connect(sslider, SIGNAL(valueChanged(int)), paintWidget, SLOT(sets(int)));
    connect(scalebutton, SIGNAL(clicked()), paintWidget, SLOT(scaletarget()));
    connect(rslider, SIGNAL(valueChanged(int)), this, SLOT(angleValueChanged(int)));
    connect(this, SIGNAL(changeanglelabel(QString)), r, SLOT(setText(QString)));
    connect(rotatebutton, SIGNAL(clicked()), paintWidget, SLOT(rotatetarget()));
    connect(clipbutton1, SIGNAL(clicked()), paintWidget, SLOT(cliptarget1()));
    connect(clipbutton2, SIGNAL(clicked()), paintWidget, SLOT(cliptarget2()));
    connect(xminbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setxmin(int)));
    connect(xmaxbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setxmax(int)));
    connect(yminbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setymin(int)));
    connect(ymaxbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setymax(int)));
    connect(rslider, SIGNAL(valueChanged(int)), paintWidget, SLOT(setr(int)));
    connect(Rslider, SIGNAL(valueChanged(int)), Rbox, SLOT(setValue(int)));
    connect(Rbox, SIGNAL(valueChanged(int)), Rslider, SLOT(setValue(int)));
    connect(Rbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setR(int)));
    connect(Gslider, SIGNAL(valueChanged(int)), Gbox, SLOT(setValue(int)));
    connect(Gbox, SIGNAL(valueChanged(int)), Gslider, SLOT(setValue(int)));
    connect(Gbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setG(int)));
    connect(Bslider, SIGNAL(valueChanged(int)), Bbox, SLOT(setValue(int)));
    connect(Bbox, SIGNAL(valueChanged(int)), Bslider, SLOT(setValue(int)));
    connect(Bbox, SIGNAL(valueChanged(int)), paintWidget, SLOT(setB(int)));
    connect(clearAction, SIGNAL(triggered()), paintWidget, SLOT(clearall()));
    connect(saveAction, SIGNAL(triggered()), paintWidget, SLOT(savefile()));
    connect(drawLineAction, SIGNAL(triggered()), this, SLOT(drawLineActionTriggered()));
    connect(drawLine2Action, SIGNAL(triggered()), this, SLOT(drawLine2ActionTriggered()));
    connect(drawRectAction, SIGNAL(triggered()), this, SLOT(drawRectActionTriggered()));
    connect(drawElliAction, SIGNAL(triggered()), this, SLOT(drawElliActionTriggered()));
    connect(drawPolyAction, SIGNAL(triggered()), this, SLOT(drawPolyActionTriggered()));
    connect(drawPoly2Action, SIGNAL(triggered()), this, SLOT(drawPoly2ActionTriggered()));
    connect(drawCurveAction, SIGNAL(triggered()), this, SLOT(drawCurveActionTriggered()));
    connect(drawCurve2Action, SIGNAL(triggered()), this, SLOT(drawCurve2ActionTriggered()));
    connect(this, SIGNAL(changeCurrentShape(Shape::Code)), paintWidget, SLOT(setCurrentShape(Shape::Code)));
    connect(selectAction, SIGNAL(triggered()), paintWidget, SLOT(enableselect()));
    connect(selectclipwindow1Action, SIGNAL(triggered()), paintWidget, SLOT(enableselectfirst()));
    connect(selectclipwindow2Action, SIGNAL(triggered()), paintWidget, SLOT(enableselectsecond()));
    connect(paintWidget, SIGNAL(changecenterx(int)), xbox, SLOT(setValue(int)));
    connect(paintWidget, SIGNAL(changecentery(int)), ybox, SLOT(setValue(int)));
    connect(paintWidget, SIGNAL(changexmin(int)), xminbox, SLOT(setValue(int)));
    connect(paintWidget, SIGNAL(changexmax(int)), xmaxbox, SLOT(setValue(int)));
    connect(paintWidget, SIGNAL(changeymin(int)), yminbox, SLOT(setValue(int)));
    connect(paintWidget, SIGNAL(changeymax(int)), ymaxbox, SLOT(setValue(int)));
}

void MainWindow::drawLineActionTriggered()
{
    emit changeCurrentShape(Shape::Line);
}

void MainWindow::drawLine2ActionTriggered()
{
    emit changeCurrentShape(Shape::Line2);
}

void MainWindow::drawRectActionTriggered()
{
    emit changeCurrentShape(Shape::Rect);
}

void MainWindow::drawPolyActionTriggered()
{
    emit changeCurrentShape(Shape::Poly);
}

void MainWindow::drawPoly2ActionTriggered()
{
    emit changeCurrentShape(Shape::Poly2);
}

void MainWindow::drawElliActionTriggered()
{
    emit changeCurrentShape(Shape::Elli);
}

void MainWindow::drawCurveActionTriggered()
{
    emit changeCurrentShape(Shape::Curve);
}

void MainWindow::drawCurve2ActionTriggered()
{
    emit changeCurrentShape(Shape::Curve2);
}

void MainWindow::angleValueChanged(int s)
{
    double doublevalue = s/10.0;
    emit changeanglelabel(QString::number(doublevalue, 'f', 1) + u8"°");
}

void MainWindow::scaleValueChanged(int s)
{
    double doublevalue = s/10.0;
    emit changescalelabel(QString::number(doublevalue, 'f', 1) + u8"×");
}
