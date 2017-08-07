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
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    //qDebug() << "paint";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Задаем режим матрицы
    glMatrixMode(GL_PROJECTION);

    //Загружаем матрицу
    glLoadIdentity();

    drawCoordinatesVectors();
    //drawCommands();

    swapBuffers();
}

void OGLWidget::drawCoordinatesVectors()
{
    drawLine(1, 0, 0, 1, 1, 0, 0);
    drawLine(0, 1, 0, 1, 0, 1, 0);
    drawLine(0, 0, 1, 1, 0, 0, 1);
}

void OGLWidget::drawCommands()
{
    //auto commands = CommandInterpreter::Instance().getCommands();

    /*for (auto command : commands)
        command->draw(this);*/
}

void OGLWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if(abs(mouseEvent->x() - mousePositionX) >= 20)
    {
        mousePositionX = mouseEvent->x();
    }
    if(abs(mouseEvent->y() - mousePositionY) >= 20)
    {
        mousePositionY = mouseEvent->y();
    }

    angleX += (mousePositionY - mouseEvent->y())/2;
    angleZ += (mousePositionX - mouseEvent->x())/2;

    mousePositionX = mouseEvent->x();
    mousePositionY = mouseEvent->y();

    rotate();
}

void OGLWidget::rotate()
{
    if(angleX > 360)
    {
        angleX = 0;
    }
    if(angleZ > 360)
    {
        angleZ = 0;
    }
    if(angleX < 0)
    {
        angleX = 360;
    }
    if(angleZ < 0)
    {
        angleZ = 360;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotated(angleX, 1, 0, 0);
    glRotated(angleZ, 0, 1, 0);

    //qDebug() << angleX << " : " << angleZ;

    paintGL();
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
