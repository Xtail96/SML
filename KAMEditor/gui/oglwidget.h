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

#include "models/structs.h"
#include "models/machinetool/commandsmanager/commandsmanager.h"
#include "models/machinetool/pointsmanager/pointsmanager.h"

class CommandsManager;

class OGLWidget : public QGLWidget
{
public:
    OGLWidget(QWidget *parent = 0);

    ~OGLWidget() {}

    void drawArc(double radius, double startAngle, double arcAngle, double v = 1);

    void drawLine(double dx, double dy, double dz, double v = 1, Point3D src = Point3D());

    void drawCylinder(double radius, double height, Point3D src = Point3D());

    void scaling(int delta);

    void rotate();

    void setXAngle(double angle);

    void setYAngle(double angle);

    void setZAngle(double angle);

    double getScale() const;

    void setScale(double value);

    void updateField();

    int getMouseMoveAction() const;

    void setMouseMoveAction(int value);

    bool getPointsVisible() const;
    void setPointsVisible(bool value);

    std::shared_ptr<PointsManager> getPointsManager() const;
    void setPointsManager(const std::shared_ptr<PointsManager> &value);

    std::shared_ptr<CommandsManager> getCommandsManager() const;
    void setCommandsManager(const std::shared_ptr<CommandsManager> &value);

protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void drawCoordinatesVectors();
    void drawCommands();
    void drawPoints();

    double scale = 0.1;
    double angleX = 180;
    double angleY = 0;
    double angleZ = 0;
    int mousePositionX = 0;
    int mousePositionY = 0;
    int mouseMoveAction = 1;

    std::shared_ptr<CommandsManager> commandsManager;

    bool pointsVisible = false;
    std::shared_ptr<PointsManager> pointsManager;

    void mousePressEvent(QMouseEvent *mouseEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void move();
    void wheelEvent(QWheelEvent *wheelEvent);
};

#endif // OGLWIDGET_H
