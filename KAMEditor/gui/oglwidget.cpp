#include "oglwidget.h"

#include "models/machinetool/commandsmanager/commands/commands.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

OGLWidget::OGLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

}

void OGLWidget::initializeGL()
{
    glClearColor(0.913, 0.933, 0.996, 1);
    glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Задаем режим матрицы
    glMatrixMode(GL_PROJECTION);

    //Загружаем матрицу
    glLoadIdentity();

    glScalef(scale, scale, scale);
    drawCoordinatesVectors();

    drawCommands();

    swapBuffers();
}

void OGLWidget::drawCoordinatesVectors()
{
    glLineWidth(2.0f);

    glColor3f(1, 0, 0);
    drawLine(1, 0, 0, 1);
    renderText(1, 0, 0, "X");

    glColor3f(0, 1, 0);
    drawLine(0, 1, 0, 1);
    renderText(0, 1, 0, "Y");

    glColor3f(0, 0, 1);
    drawLine(0, 0, 1, 1);
    renderText(0, 0, 1, "Z");
}

void OGLWidget::drawCommands()
{
    glLineWidth(1.0f);
    qglColor(Qt::gray);

    glBegin(GL_QUADS);
            glVertex3f( 0.1f, 0.1f,-0.1f);
            glVertex3f(-0.1f, 0.1f,-0.1f);
            glVertex3f(-0.1f, 0.1f, 0.1f);
            glVertex3f( 0.1f, 0.1f, 0.1f);
            glVertex3f( 0.1f,-0.1f, 0.1f);
            glVertex3f(-0.1f,-0.1f, 0.1f);
            glVertex3f(-0.1f,-0.1f,-0.1f);
            glVertex3f( 0.1f,-0.1f,-0.1f);
            glVertex3f( 0.1f, 0.1f, 0.1f);
            glVertex3f(-0.1f, 0.1f, 0.1f);
            glVertex3f(-0.1f,-0.1f, 0.1f);
            glVertex3f( 0.1f,-0.1f, 0.1f);
            glVertex3f( 0.1f,-0.1f,-0.1f);
            glVertex3f(-0.1f,-0.1f,-0.1f);
            glVertex3f(-0.1f, 0.1f,-0.1f);
            glVertex3f( 0.1f, 0.1f,-0.1f);
            glVertex3f(-0.1f, 0.1f, 0.1f);
            glVertex3f(-0.1f, 0.1f,-0.1f);
            glVertex3f(-0.1f,-0.1f,-0.1f);
            glVertex3f(-0.1f,-0.1f, 0.1f);
            glVertex3f( 0.1f, 0.1f,-0.1f);
            glVertex3f( 0.1f, 0.1f, 0.1f);
            glVertex3f( 0.1f,-0.1f, 0.1f);
            glVertex3f( 0.1f,-0.1f,-0.1f);
         glEnd();
}

void OGLWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    double dx = mouseEvent->x() - mousePositionX;
    double dy = mouseEvent->y() - mousePositionY;

    if (mouseEvent->buttons() == Qt::LeftButton)
    {
        setXAngle(angleX + 1 * dy);
        setYAngle(angleY + 1 * dx);
    }
    else
    {
        if(mouseEvent->buttons() == Qt::RightButton)
        {
            setXAngle(angleX + 1 * dy);
            setZAngle(angleZ + 1 * dx);
        }
    }
    rotate();
}

void OGLWidget::rotate()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotated(angleX / 64, 1, 0, 0);
    glRotated(angleY / 64, 0, 1, 0);
    glRotated(angleZ / 64, 0, 0, 1);

    updateGL();
}

void OGLWidget::setXAngle(double angle)
{
    angleX = angle;
}

void OGLWidget::setYAngle(double angle)
{
    angleY = angle;
}

void OGLWidget::setZAngle(double angle)
{
    angleZ = angle;
}

void OGLWidget::move()
{

}

void OGLWidget::wheelEvent(QWheelEvent *wheelEvent)
{
    // если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
    // иначе -- делим на 1.1
    if ((wheelEvent->delta()) > 0)
    {
        scale *= 1.1;
    }
    else
    {
        if ((wheelEvent->delta()) < 0)
        {
            scale /= 1.1;
        }
    }

    updateGL();
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/
}
