#include "gcodesviewwidget.h"

GCodesViewWidget::GCodesViewWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

}

GCodesViewWidget::~GCodesViewWidget()
{

}

void GCodesViewWidget::initializeGL()
{
    glClearColor(0.913, 0.933, 0.996, 1);
    glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    rotate();
}

void GCodesViewWidget::paintGL()
{
    try
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Задаем режим матрицы
        glMatrixMode(GL_PROJECTION);

        //Загружаем матрицу
        glLoadIdentity();

        move();
        rotate();

        glScalef(scale, scale, scale);
        drawCoordinatesVectors();

        /*drawCommands();

        if(pointsVisible)
        {
            drawPoints();
        }

        if(gridVisible)
        {
            drawGrid();
        }*/
#ifdef Q_OS_MACOS
    swapBuffers();
#endif
    }
    catch(...)
    {
        this->setUpdatesEnabled(false);
        this->close();
        QMessageBox(QMessageBox::Warning, "Ошибка", "Невозможно отобразить траекторию движения").exec();
    }
}

void GCodesViewWidget::drawCoordinatesVectors()
{
    glLineWidth(2.0f);
    glDisable(GL_LINE_STIPPLE);

    //updateOffsetsIsNeed = false;
    //updateCurrentPointIsNeed = false;

    currentPoint.x = 0;
    currentPoint.y = 0;
    currentPoint.z = 0;

    glColor3f(1, 0, 0);
    drawLine(10, 0, 0);
    renderText(10, 0, 0, "X");

    glColor3f(0, 1, 0);
    drawLine(0, 10, 0);
    renderText(0, 10, 0, "Y");

    glColor3f(0, 0, 1);
    drawLine(0, 0, 10);
    renderText(0, 0, 10, "Z");
}

double GCodesViewWidget::getScale() const
{
    return scale;
}

void GCodesViewWidget::setScale(double value)
{
    scale = value;
}

double GCodesViewWidget::getAngleX() const
{
    return angleX;
}

void GCodesViewWidget::setAngleX(double value)
{
    if(value >= 180)
    {
        angleX = 0;
    }
    else
    {
        angleX = value;
    }
}

double GCodesViewWidget::getAngleZ() const
{
    return angleZ;
}

void GCodesViewWidget::setAngleZ(double value)
{
    if(value >= 180)
    {
        angleZ = 0;
    }
    else
    {
        angleZ = value;
    }
}

int GCodesViewWidget::getMousePositionX() const
{
    return mousePositionX;
}

void GCodesViewWidget::setMousePositionX(int value)
{
    mousePositionX = value;
}

int GCodesViewWidget::getMousePositionY() const
{
    return mousePositionY;
}

void GCodesViewWidget::setMousePositionY(int value)
{
    mousePositionY = value;
}

void GCodesViewWidget::updateField()
{
    updateGL();
}

void GCodesViewWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    mousePositionX = mouseEvent->x();
    mousePositionY = mouseEvent->y();
}

double GCodesViewWidget::getPositionY() const
{
    return positionY;
}

void GCodesViewWidget::setPositionY(double value)
{
    positionY = value;
}

double GCodesViewWidget::getPositionX() const
{
    return positionX;
}

void GCodesViewWidget::setPositionX(double value)
{
    positionX = value;
}

void GCodesViewWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{

    double dx = (mouseEvent->x() - mousePositionX) / 10;
    double dy = (mouseEvent->y() - mousePositionY) / 10;

    if (mouseEvent->buttons() == Qt::LeftButton)
    {
        //setXAngle(angleX - 1 * dy);
        //setYAngle(angleY - 1 * dx);
        setPositionX(positionX + dx/1000);
        setPositionY(positionY + dy/1000);
    }
    else
    {
        if(mouseEvent->buttons() == Qt::RightButton)
        {
            setAngleX(angleX + 1 * dy);
            setAngleZ(angleZ + 1 * dx);
        }
    }
    updateGL();
}

void GCodesViewWidget::wheelEvent(QWheelEvent *wheelEvent)
{
    scaling(wheelEvent->delta());
}

void GCodesViewWidget::rotate()
{
    glRotated(angleX, 1, 0, 0);
    //glRotated(angleY, 0, 1, 0);
    glRotated(angleZ, 0, 0, 1);
}

void GCodesViewWidget::move()
{
    glTranslatef(0.5f*positionX, -(0.5f*positionY), 0);
}

void GCodesViewWidget::scaling(int delta)
{
    // если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
    // иначе - делим на 1.1
    if (delta > 0)
    {
        scale *= 1.1;
    }
    else
    {
        if (delta < 0)
        {
            scale /= 1.1;
        }
    }
    updateGL();
}

void GCodesViewWidget::resizeGL(int w, int h)
{
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/
}

void GCodesViewWidget::drawPoint(Point3D src, QString text)
{
    /*glBegin(GL_POINTS);
    glVertex3f(src.x, src.y, src.z);
    glEnd();
    renderText(src.x, src.y, src.z, text);*/
}

void GCodesViewWidget::drawLine(double dx, double dy, double dz)
{
    double newX = currentPoint.x + dx;
    double newY = currentPoint.y + dy;
    double newZ = currentPoint.z + dz;

    if(newZ > 0 && updateCurrentPointIsNeed)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x1111);
    }
    else
    {
        glDisable(GL_LINE_STIPPLE);
    }

    glBegin(GL_LINES);

    glVertex3f(currentPoint.x, currentPoint.y, currentPoint.z);

    glVertex3f(newX, newY, newZ);

    glEnd();

    //Point3D destinaton(newX, newY, newZ);
    //updateOffsets(destinaton);
    //updateCurrentPoint(destinaton);
}