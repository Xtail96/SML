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
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"
#include "models/machinetool/pointsmanager/pointsmanager.h"

class CommandsInterpreter;

class OGLWidget : public QGLWidget
{
public:
    OGLWidget(QWidget *parent = 0);

    ~OGLWidget() {}

    void drawArc(double radius, double startAngle, double arcAngle, double v = 1);

    void drawLine(double dx, double dy, double dz, double v = 1, Point3D src = Point3D());

    void drawPoint(Point3D src = Point3D(), QString text = "");

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

    PointsManager* getPointsManager() const;
    void setPointsManager(PointsManager *value);


    CommandsInterpreter *getCommandsInterpreter() const;
    void setCommandsInterpreter(CommandsInterpreter *value);

    unsigned int getGridSize() const;
    void setGridSize(unsigned int value);

    bool getGridVisible() const;
    void setGridVisible(bool value);

    unsigned int getGridCellSize() const;
    void setGridCellSize(unsigned int value);

    std::string getGridPlane() const;
    void setGridPlane(const std::string &value);

protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void drawCoordinatesVectors();
    void drawCommands();
    void drawPoints();
    void drawGrid();

    double scale = 0.005;
    double angleX = 180;
    double angleY = 0;
    double angleZ = 0;
    int mousePositionX = 0;
    int mousePositionY = 0;
    int mouseMoveAction = 1;

    bool gridVisible = false;
    std::string gridPlane = "X0Y";
    unsigned int gridSize = 1000;
    unsigned int gridCellSize = 1;

    CommandsInterpreter* commandsInterpreter;

    bool pointsVisible = false;
    PointsManager* pointsManager;

    void mousePressEvent(QMouseEvent *mouseEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void move();
    void wheelEvent(QWheelEvent *wheelEvent);
};

#endif // OGLWIDGET_H
