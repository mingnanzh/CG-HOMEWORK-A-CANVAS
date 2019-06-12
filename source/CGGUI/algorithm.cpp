#include "algorithm.h"

static int _width = 1000;
static int _height = 1000;
static int R = 0;
static int G = 0;
static int B = 0;
static float Pi = 3.1415926535;

string filename, imageSaveAddress;

static Primitive listbegin = NULL;
static Primitive listend = NULL;

void insert2list(Primitive p)
{
    if(!listbegin)
    {
        listbegin = p;
        listend = listbegin;
    }
    else
    {
        listend->next = p;
        listend = listend->next;
    }
}

Primitive findid(int id)
{
    Primitive temp = listbegin;
    while(temp)
    {
        if(temp->id == id)
            return temp;
        else
            temp = temp->next;
    }
    return temp;
}

QImage resetCanvas(int width, int height)
{
    return QImage(width,height,QImage::Format_RGB32);
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

void saveCanvas(QImage &picture,string name)
{
    name = imageSaveAddress + "\\" + name + ".bmp";
    cout << "BMP file is saved at " << name << endl;
    char *addr = (char *)(name.c_str());
    picture.save (addr,"BMP");
}

void setColor(QPainter &painter, int R, int G, int B)
{
    painter.setPen(QColor(R,G,B));
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
                    painter.drawPoint(int(px), _height - int(py));
                    py += sgn(x2 - x1) * m;
                }
            }
            else
            {
                px = x1;
                for(py = y1; sgn(y2 - y1) * py <= sgn(y2 - y1) * y2; py += sgn(y2 - y1))
                {
                    painter.drawPoint(int(px), _height - int(py));
                    px += sgn(y2 - y1) * (1 / m);
                }
            }
        }
        else
        {
            px = x1;
            for(py = y1; sgn(y2 - y1) * py <= sgn(y2 - y1) * y2; py += sgn(y2 - y1))
            {
                painter.drawPoint(int(px), _height - int(py));
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
                painter.drawPoint(int(y), _height - int(x));
            else
                painter.drawPoint(int(x), _height - int(y));
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

void drawPolygon(QPainter &painter, int n, vector<float> &x, vector<float> &y, string algorithm)
{
    for(int i = 0; i < n-1; i++)
        drawLine(painter, x[i], y[i], x[i+1], y[i+1], algorithm);
    drawLine(painter, x[n-1], y[n-1], x[0], y[0], algorithm);
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
            painter.drawPoint(int(x)+yc, _height-(int(y)+xc));
            painter.drawPoint(int(x)+yc, _height-(int(y)-xc));
            painter.drawPoint(int(x)-yc, _height-(int(y)+xc));
            painter.drawPoint(int(x)-yc, _height-(int(y)-xc));
        }
        else
        {
            painter.drawPoint(int(x)+xc, _height-(int(y)+yc));
            painter.drawPoint(int(x)+xc, _height-(int(y)-yc));
            painter.drawPoint(int(x)-xc, _height-(int(y)+yc));
            painter.drawPoint(int(x)-xc, _height-(int(y)-yc));
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
        painter.drawPoint(int(x)+yc, _height-(int(y)+xc));
        painter.drawPoint(int(x)+yc, _height-(int(y)-xc));
        painter.drawPoint(int(x)-yc, _height-(int(y)+xc));
        painter.drawPoint(int(x)-yc, _height-(int(y)-xc));
    }
    else
    {
        painter.drawPoint(int(x)+xc, _height-(int(y)+yc));
        painter.drawPoint(int(x)+xc, _height-(int(y)-yc));
        painter.drawPoint(int(x)-xc, _height-(int(y)+yc));
        painter.drawPoint(int(x)-xc, _height-(int(y)-yc));
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
            painter.drawPoint(int(x)+yc, _height-(int(y)+xc));
            painter.drawPoint(int(x)+yc, _height-(int(y)-xc));
            painter.drawPoint(int(x)-yc, _height-(int(y)+xc));
            painter.drawPoint(int(x)-yc, _height-(int(y)-xc));
        }
        else
        {
            painter.drawPoint(int(x)+xc, _height-(int(y)+yc));
            painter.drawPoint(int(x)+xc, _height-(int(y)-yc));
            painter.drawPoint(int(x)-xc, _height-(int(y)+yc));
            painter.drawPoint(int(x)-xc, _height-(int(y)-yc));
        }
    }
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
            painter.drawPoint(old_x[0], _height-old_y[0]);
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
                painter.drawPoint(px, _height-py);
            }
            i++;
        }
    }
}

void repaint(QPainter &painter, Primitive temp)
{
    if(temp != listend)
    {
        if(temp->kind == Primitive_::kind::LINE)
        {
            setColor(painter, temp->u.line->R, temp->u.line->G, temp->u.line->B);
            drawLine(painter, temp->u.line->x1, temp->u.line->y1, temp->u.line->x2, temp->u.line->y2, temp->u.line->algorithm);
        }
        else if (temp->kind == Primitive_::kind::POLYGON)
        {
            setColor(painter, temp->u.polygon->R, temp->u.polygon->G, temp->u.polygon->B);
            drawPolygon(painter, temp->u.polygon->n, temp->u.polygon->x, temp->u.polygon->y, temp->u.polygon->algorithm);
        }
        else if (temp->kind == Primitive_::kind::ELLIPSE)
        {
            setColor(painter, temp->u.ellipse->R, temp->u.ellipse->G, temp->u.ellipse->B);
            drawEllipse(painter, temp->u.ellipse->x, temp->u.ellipse->y, temp->u.ellipse->rx, temp->u.ellipse->ry);
        }
        else if (temp->kind == Primitive_::kind::CURVE)
        {
            setColor(painter, temp->u.curve->R, temp->u.curve->G, temp->u.curve->B);
            drawCurve(painter, temp->u.curve->n, temp->u.curve->x, temp->u.curve->y, temp->u.curve->algorithm);
        }
        repaint(painter, temp->next);
    }
    else
    {
        if(temp->kind == Primitive_::kind::LINE)
        {
            setColor(painter, temp->u.line->R, temp->u.line->G, temp->u.line->B);
            drawLine(painter, temp->u.line->x1, temp->u.line->y1, temp->u.line->x2, temp->u.line->y2, temp->u.line->algorithm);
        }
        else if (temp->kind == Primitive_::kind::POLYGON)
        {
            setColor(painter, temp->u.polygon->R, temp->u.polygon->G, temp->u.polygon->B);
            drawPolygon(painter, temp->u.polygon->n, temp->u.polygon->x, temp->u.polygon->y, temp->u.polygon->algorithm);
        }
        else if (temp->kind == Primitive_::kind::ELLIPSE)
        {
            setColor(painter, temp->u.ellipse->R, temp->u.ellipse->G, temp->u.ellipse->B);
            drawEllipse(painter, temp->u.ellipse->x, temp->u.ellipse->y, temp->u.ellipse->rx, temp->u.ellipse->ry);
        }
        else if (temp->kind == Primitive_::kind::CURVE)
        {
            setColor(painter, temp->u.curve->R, temp->u.curve->G, temp->u.curve->B);
            drawCurve(painter, temp->u.curve->n, temp->u.curve->x, temp->u.curve->y, temp->u.curve->algorithm);
        }
    }
}

void translate(QPainter &painter, int id, float dx, float dy)
{
    Primitive temp = findid(id);
    if (temp->kind == Primitive_::kind::LINE)
    {
        temp->u.line->x1 += dx;
        temp->u.line->x2 += dx;
        temp->u.line->y1 += dy;
        temp->u.line->y2 += dy;
        repaint(painter, listbegin);
    }
    else if (temp->kind == Primitive_::kind::POLYGON)
    {
        for (vector<float>::iterator iter = temp->u.polygon->x.begin(); iter != temp->u.polygon->x.end(); iter++)
            (*iter) += dx;
        for (vector<float>::iterator iter = temp->u.polygon->y.begin(); iter != temp->u.polygon->y.end(); iter++)
            (*iter) += dy;
        repaint(painter, listbegin);
    }
    else if (temp->kind == Primitive_::kind::ELLIPSE)
    {
        temp->u.ellipse->x += dx;
        temp->u.ellipse->y += dy;
        repaint(painter, listbegin);
    }
    else if (temp->kind == Primitive_::kind::CURVE)
    {
        for (vector<float>::iterator iter = temp->u.curve->x.begin(); iter != temp->u.curve->x.end(); iter++)
            (*iter) += dx;
        for (vector<float>::iterator iter = temp->u.curve->y.begin(); iter != temp->u.curve->y.end(); iter++)
            (*iter) += dy;
        repaint(painter, listbegin);
    }
}

void rotate(QPainter &painter, int id, float x, float y, float r)
{
    Primitive temp = findid(id);
    if (temp->kind == Primitive_::kind::LINE)
    {
        float xx, yy;
        xx = (temp->u.line->x1 - x) * cos(Pi*r/180) + (temp->u.line->y1 - y) * sin(Pi*r/180) + x;
        yy = (temp->u.line->y1 - y) * cos(Pi*r/180) - (temp->u.line->x1 - x) * sin(Pi*r/180) + y;
        temp->u.line->x1 = xx;
        temp->u.line->y1 = yy;
        xx = (temp->u.line->x2 - x) * cos(Pi*r/180) + (temp->u.line->y2 - y) * sin(Pi*r/180) + x;
        yy = (temp->u.line->y2 - y) * cos(Pi*r/180) - (temp->u.line->x2 - x) * sin(Pi*r/180) + y;
        temp->u.line->x2 = xx;
        temp->u.line->y2 = yy;
        repaint(painter, listbegin);
    }
    else if (temp->kind == Primitive_::kind::POLYGON)
    {
        float xx, yy;
        for (int i = 0; i < temp->u.polygon->n; i++) {
            xx = (temp->u.polygon->x[i] - x) * cos(Pi*r/180) + (temp->u.polygon->y[i] - y) * sin(Pi*r/180) + x;
            yy = (temp->u.polygon->y[i] - y) * cos(Pi*r/180) - (temp->u.polygon->x[i] - x) * sin(Pi*r/180) + y;
            temp->u.polygon->x[i] = xx;
            temp->u.polygon->y[i] = yy;
        }
        repaint(painter, listbegin);
    }
    else if (temp->kind == Primitive_::kind::CURVE)
    {
        float xx, yy;
        for (int i = 0; i < temp->u.curve->n; i++) {
            xx = (temp->u.curve->x[i] - x) * cos(Pi*r/180) + (temp->u.curve->y[i] - y) * sin(Pi*r/180) + x;
            yy = (temp->u.curve->y[i] - y) * cos(Pi*r/180) - (temp->u.curve->x[i] - x) * sin(Pi*r/180) + y;
            temp->u.curve->x[i] = xx;
            temp->u.curve->y[i] = yy;
        }
        repaint(painter, listbegin);
    }
}

void scale(QPainter &painter, int id, float x, float y, float s)
{
    Primitive temp = findid(id);
    if (temp->kind == Primitive_::kind::LINE)
    {
        temp->u.line->x1 = (temp->u.line->x1 - x) * s + x;
        temp->u.line->y1 = (temp->u.line->y1 - y) * s + y;
        temp->u.line->x2 = (temp->u.line->x2 - x) * s + x;
        temp->u.line->y2 = (temp->u.line->y2 - y) * s + y;
        repaint(painter, listbegin);
    }
    else if (temp->kind == Primitive_::kind::POLYGON)
    {
        for (vector<float>::iterator iter = temp->u.polygon->x.begin(); iter != temp->u.polygon->x.end(); iter++)
            (*iter) = ((*iter) - x) * s + x;
        for (vector<float>::iterator iter = temp->u.polygon->y.begin(); iter != temp->u.polygon->y.end(); iter++)
            (*iter) = ((*iter) - y) * s + y;
        repaint(painter, listbegin);
    }
    else if (temp->kind == Primitive_::kind::ELLIPSE)
    {
        temp->u.ellipse->x = (temp->u.ellipse->x - x) * s + x;
        temp->u.ellipse->y = (temp->u.ellipse->y - y) * s + y;
        temp->u.ellipse->rx = temp->u.ellipse->rx * s;
        temp->u.ellipse->ry = temp->u.ellipse->ry * s;
        repaint(painter, listbegin);
    }
    else if (temp->kind == Primitive_::kind::CURVE)
    {
        for (vector<float>::iterator iter = temp->u.curve->x.begin(); iter != temp->u.curve->x.end(); iter++)
            (*iter) = ((*iter) - x) * s + x;
        for (vector<float>::iterator iter = temp->u.curve->y.begin(); iter != temp->u.curve->y.end(); iter++)
            (*iter) = ((*iter) - y) * s + y;
        repaint(painter, listbegin);
    }
}

void clip(QPainter &painter, int id, float xmin, float ymin, float xmax,  float ymax, string algorihtm)
{
    if (algorihtm == "Cohen-Sutherland")
    {
        Primitive temp = findid(id);
        float x1 = temp->u.line->x1;
        float y1 = temp->u.line->y1;
        float x2 = temp->u.line->x2;
        float y2 = temp->u.line->y2;
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
                temp->u.line->x1=0;
                temp->u.line->y1=0;
                temp->u.line->x2=0;
                temp->u.line->y2=0;
                temp->u.line->R=255;
                temp->u.line->G=255;
                temp->u.line->B=255;
                break;
            }
            if (C1==0 && C2==0)
            {
                temp->u.line->x1=x1;
                temp->u.line->y1=y1;
                temp->u.line->x2=x2;
                temp->u.line->y2=y2;
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
        repaint(painter, listbegin);

    }
    else if (algorihtm == "Liang-Barsky") {
        Primitive temp = findid(id);
        bool flag = false;
        float u1 = 0, u2 = 1;
        float p[4], q[4];
        float r;
        p[0]=temp->u.line->x1 - temp->u.line->x2;
        p[1]=temp->u.line->x2 - temp->u.line->x1;
        p[2]=temp->u.line->y1 - temp->u.line->y2;
        p[3]=temp->u.line->y2 - temp->u.line->y1;
        q[0]=temp->u.line->x1 - xmin;
        q[1]=xmax - temp->u.line->x1;
        q[2]=temp->u.line->y1 - ymin;
        q[3]=ymax - temp->u.line->y1;

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
            temp->u.line->x1=0;
            temp->u.line->y1=0;
            temp->u.line->x2=0;
            temp->u.line->y2=0;
            temp->u.line->R=255;
            temp->u.line->G=255;
            temp->u.line->B=255;
        }
        else
        {
            float x1 = temp->u.line->x1 + u1*(temp->u.line->x2-temp->u.line->x1);
            float y1 = temp->u.line->y1 + u1*(temp->u.line->y2-temp->u.line->y1);
            float x2 = temp->u.line->x1 + u2*(temp->u.line->x2-temp->u.line->x1);
            float y2 = temp->u.line->y1 + u2*(temp->u.line->y2-temp->u.line->y1);
            temp->u.line->x1=x1;
            temp->u.line->y1=y1;
            temp->u.line->x2=x2;
            temp->u.line->y2=y2;
        }
        repaint(painter, listbegin);
    }
}

void paintevent(){
    QImage picture;
    QPainter painter;
    painter.begin(&picture);

    ifstream fin(filename);
    if (!fin){
        cout << "Open File failed." << endl;
        exit(0);
    };

    string buff;
    while(!fin.eof()){
        fin >> buff;
        if (buff == "resetCanvas") {
            fin >>_width>>_height;
            painter.end();
            picture=resetCanvas(_width, _height);
            picture.fill(QColor(255,255,255));
            listbegin = NULL;
            painter.begin(&picture);
        }
        else if (buff == "saveCanvas") {
            string name;
            fin >> name;
            saveCanvas(picture, name);
        }
        else if (buff == "setColor") {
            fin >> R >> G >> B;
            setColor(painter,R,G,B);
        }
        else if (buff == "drawLine") {
            int id;
            float x1, y1, x2, y2;
            string algorithm;
            fin >> id >> x1 >> y1 >> x2 >> y2 >> algorithm;
            Linee line = new struct Line_;
            line->x1 = x1;
            line->y1 = y1;
            line->x2 = x2;
            line->y2 = y2;
            line->algorithm = algorithm;
            line->R = R;
            line->G = G;
            line->B = B;
            Primitive temp = Primitive(malloc(sizeof(struct Primitive_)));
            temp->id = id;
            temp->kind = Primitive_::kind::LINE;
            temp->u.line = line;
            insert2list(temp);
            drawLine(painter, x1, y1, x2, y2, algorithm);
        }
        else if (buff == "drawPolygon") {
            int id, n;
            string algorithm;
            fin >> id >> n >> algorithm;
            vector<float> x;
            vector<float> y;
            for(int i = 0; i < n; i++){
                float a, b;
                fin >> a >> b;
                x.push_back(a);
                y.push_back(b);
            }
            Polygon polygon = new struct Polygon_();
            polygon->n = n;
            polygon->x = x;
            polygon->y = y;
            polygon->algorithm = algorithm;
            polygon->R = R;
            polygon->G = G;
            polygon->B = B;
            Primitive temp = Primitive(malloc(sizeof(struct Primitive_)));
            temp->id = id;
            temp->kind = Primitive_::kind::POLYGON;
            temp->u.polygon = polygon;
            insert2list(temp);
            drawPolygon(painter, n, x, y, algorithm);
        }
        else if (buff == "drawEllipse") {
            int id;
            float x, y, rx, ry;
            fin >> id >> x >> y >> rx >> ry;
            Ellipse ellipse = new struct Ellipse_();
            ellipse->x = x;
            ellipse->y = y;
            ellipse->rx = rx;
            ellipse->ry = ry;
            ellipse->R = R;
            ellipse->G = G;
            ellipse->B = B;
            Primitive temp = Primitive(malloc(sizeof(struct Primitive_)));
            temp->id = id;
            temp->kind = Primitive_::kind::ELLIPSE;
            temp->u.ellipse = ellipse;
            insert2list(temp);
            drawEllipse(painter, x, y, rx, ry);
        }
        else if (buff == "drawCurve") {
            int id, n;
            string algorithm;
            fin >> id >> n >> algorithm;
            vector<float> x;
            vector<float> y;
            for(int i = 0; i < n; i++){
                float a, b;
                fin >> a >> b;
                x.push_back(a);
                y.push_back(b);
            }
            Curve curve = new struct Curve_();
            curve->n = n;
            curve->x = x;
            curve->y = y;
            curve->algorithm = algorithm;
            curve->R = R;
            curve->G = G;
            curve->B = B;
            Primitive temp = Primitive(malloc(sizeof(struct Primitive_)));
            temp->id = id;
            temp->kind = Primitive_::kind::CURVE;
            temp->u.curve = curve;
            insert2list(temp);
            drawCurve(painter, n, x, y, algorithm);
        }
        else if (buff == "translate") {
            int id;
            float dx, dy;
            fin >> id >> dx >> dy;
            painter.end();
            picture=resetCanvas(_width, _height);
            picture.fill(QColor(255,255,255));
            painter.begin(&picture);
            translate(painter, id, dx, dy);
            setColor(painter, R, G, B);
        }
        else if (buff == "rotate") {
            int id;
            float x, y;
            float r;
            fin >> id >> x >> y >> r;
            painter.end();
            picture=resetCanvas(_width, _height);
            picture.fill(QColor(255,255,255));
            painter.begin(&picture);
            rotate(painter, id, x, y, r);
            setColor(painter, R, G, B);
        }
        else if (buff == "scale") {
            int id;
            float x, y;
            float s;
            fin >> id >> x >> y >> s;
            painter.end();
            picture=resetCanvas(_width, _height);
            picture.fill(QColor(255,255,255));
            painter.begin(&picture);
            scale(painter, id, x, y, s);
            setColor(painter, R, G, B);
        }
        else if (buff == "clip") {
            int id;
            float xmin, ymin, xmax, ymax;
            string algorithm;
            fin >> id >> xmin >> ymin >> xmax >> ymax >> algorithm;
            painter.end();
            picture=resetCanvas(_width, _height);
            picture.fill(QColor(255,255,255));
            painter.begin(&picture);
            clip(painter, id, xmin, ymin, xmax, ymax, algorithm);
            setColor(painter, R, G, B);
        }
    }
    fin.close();
    painter.end();
}
