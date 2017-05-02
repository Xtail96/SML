#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#ifdef Q_OS_WIN
#include <GL/glu.h>
#include <GL/gl.h>
#endif
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

class OGLWidget : public QOpenGLWidget
{
public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget() {}

    void drawArc(double radius, double startAngle, double arcAngle, double v = 1);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // OGLWIDGET_H
