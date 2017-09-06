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
    Q_OBJECT

signals:
    void offsetsChanged();
public:
    OGLWidget(QWidget *parent = 0);

    ~OGLWidget() {}

    void drawArc(double radius, double startAngle, double arcAngle, double v = 1, Point3D src = Point3D());

    void drawLine(double dx, double dy, double dz, double v = 1, Point3D src = Point3D());

    void drawPoint(Point3D src = Point3D(), QString text = "");

    void scaling(int delta);

    void rotate();

    void move();

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

    double getGridCellSize() const;
    void setGridCellSize(double value);

    std::string getGridPlane() const;
    void setGridPlane(const std::string &value);

    double getGridMaximalAccuracy() const;
    void setGridMaximalAccuracy(double value);

    Point3D getMaxPositiveOffset() const;
    void setMaxPositiveOffset(const Point3D &value);

    Point3D getMaxNegativeOffset() const;
    void setMaxNegativeOffset(const Point3D &value);

    Point3D getGeneralOffset() const;
    void setGeneralOffset(const Point3D &value);

    double getPositionX() const;
    void setPositionX(double value);

    double getPositionY() const;
    void setPositionY(double value);

    double getPositionZ() const;
    void setPositionZ(double value);

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
    double gridCellSize = 1;
    double gridMaximalAccuracy = 0.01;

    CommandsInterpreter* commandsInterpreter;

    bool pointsVisible = false;
    PointsManager* pointsManager;

    void mousePressEvent(QMouseEvent *mouseEvent);

    double positionX = 0;
    double positionY = 0;
    double positionZ = 0;
    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void wheelEvent(QWheelEvent *wheelEvent);

    bool updateOffsetsIsNeed = false;
    Point3D maxPositiveOffset = Point3D();
    Point3D maxNegativeOffset = Point3D();
    Point3D generalOffset = Point3D();


    void updateOffsets(Point3D newVertex);
};

#endif // OGLWIDGET_H
