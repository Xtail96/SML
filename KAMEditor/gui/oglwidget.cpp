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
    rotate();
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

    if(pointsVisible)
    {
        drawPoints();
    }

    swapBuffers();
}

void OGLWidget::drawCoordinatesVectors()
{
    glLineWidth(2.0f); 
    glDisable(GL_LINE_STIPPLE);

    Point3D zeroPoint;

    glColor3f(1, 0, 0);
    drawLine(10, 0, 0, 1, zeroPoint);
    renderText(10, 0, 0, "X");

    glColor3f(0, 1, 0);
    drawLine(0, 10, 0, 1, zeroPoint);
    renderText(0, 10, 0, "Y");

    glColor3f(0, 0, 1);
    drawLine(0, 0, 10, 1, zeroPoint);
    renderText(0, 0, 10, "Z");
}

void OGLWidget::drawCommands()
{
    glLineWidth(3.0f);

    Point3D src(0, 0, 0);
    Point3D dest(0, 0, 0);
    for(unsigned int i = 0; i < commandsManager->getCommandsCount(); i++)
    {    
        qglColor(Qt::darkGray);
        dest = commandsManager->operator [](i)->returnDestinationPoint(src);
        if(dest.z > 0)
        {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x1111);
        }
        else
        {
            glDisable(GL_LINE_STIPPLE);
        }
        commandsManager->operator [](i)->draw(this, src);
        src = dest;
    }
    /*glBegin(GL_QUADS);
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
            glEnd();*/
}

void OGLWidget::drawPoints()
{
    glPointSize(3.0f);
    for(unsigned int i = 0; i < pointsManager->pointCount(); i++)
    {
        glColor3f(0, 0, 0);
        Point3D src(pointsManager->operator [](i)->get("X"), pointsManager->operator [](i)->get("Y"), pointsManager->operator [](i)->get("Z"));
        drawPoint(src, QString::number(i+1));
    }
}

CommandsManager *OGLWidget::getCommandsManager() const
{
    return commandsManager;
}

void OGLWidget::setCommandsManager(CommandsManager *value)
{
    commandsManager = value;
}

PointsManager *OGLWidget::getPointsManager() const
{
    return pointsManager;
}

void OGLWidget::setPointsManager(PointsManager *value)
{
    pointsManager = value;
}

bool OGLWidget::getPointsVisible() const
{
    return pointsVisible;
}

void OGLWidget::setPointsVisible(bool value)
{
    pointsVisible = value;
}

int OGLWidget::getMouseMoveAction() const
{
    return mouseMoveAction;
}

void OGLWidget::setMouseMoveAction(int value)
{
    mouseMoveAction = value;
}

double OGLWidget::getScale() const
{
    return scale;
}

void OGLWidget::setScale(double value)
{
    scale = value;
}

void OGLWidget::updateField()
{
    updateGL();
}

void OGLWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    mousePositionX = mouseEvent->x();
    mousePositionY = mouseEvent->y();
}

void OGLWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    switch (mouseMoveAction) {
    case 1:
    {
        double dx = (mouseEvent->x() - mousePositionX) / 2;
        double dy = (mouseEvent->y() - mousePositionY) / 2;

        if (mouseEvent->buttons() == Qt::LeftButton)
        {
            setXAngle(angleX - 1 * dy);
            setYAngle(angleY - 1 * dx);
        }
        else
        {
            if(mouseEvent->buttons() == Qt::RightButton)
            {
                setXAngle(angleX - 1 * dy);
                setZAngle(angleZ - 1 * dx);
            }
        }
        rotate();
        break;
    }
    default:
        break;
    }
}

void OGLWidget::rotate()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotated(angleX, 1, 0, 0);
    glRotated(angleY, 0, 1, 0);
    glRotated(angleZ, 0, 0, 1);

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
    scaling(wheelEvent->delta());
}

void OGLWidget::scaling(int delta)
{
    // если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
    // иначе -- делим на 1.1
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

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/
}

void OGLWidget::drawPoint(Point3D src, QString text)
{
    glBegin(GL_POINTS);
    glVertex3f(src.x, src.y, src.z);
    glEnd();
    renderText(src.x, src.y, src.z, text);
}
