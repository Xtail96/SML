#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QMouseEvent>
#ifdef Q_OS_WIN
    #include <GL/glu.h>
    #include <GL/gl.h>
#endif

#ifdef Q_OS_MACX
    #include <OpenGL/glu.h>
    #include <OpenGL/gl.h>
#endif

class OGLWidget : public QGLWidget
{
public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget() {}

    void drawArc(double radius, double startAngle, double arcAngle, double v = 1);
    void drawLine(double dx, double dy, double dz, double v = 1);
protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void drawCoordinatesVectors();
    void drawCommands();

    double scale = 1.0;
    double angleX = 0;
    double angleY = 0;
    double angleZ = 0;
    int mousePositionX = 0;
    int mousePositionY = 0;
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void rotate();
    void move();
    void wheelEvent(QWheelEvent *wheelEvent);
};

#endif // OGLWIDGET_H
