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

/*!
 * \brief Класс Виджет визуализации
 * Визуализирует управляющую программу трехкоординатного станка в трехмерном пространстве
 */
class OGLWidget : public QGLWidget
{
    Q_OBJECT
signals:
    /*!
     * \brief Сигнал об изменении смещений по координатам
     */
    void offsetsChanged();
public:
    /*!
     * \brief Конструктор класса Виджет визуализации
     * \param parent - родительский виджет, значение по умолчанию 0
     */
    OGLWidget(QWidget *parent = 0);

    ~OGLWidget() {}

    /*!
     * \brief Рисует дугу в плоскости X0Y
     * \param radius - радиус дуги
     * \param startAngle - угол поворота дуги
     * \param arcAngle - угол дуги
     * \param v - скорость отрисовки (по умолчанию 1)
     */
    void drawArc(double radius, double startAngle, double arcAngle, double v = 1);

    /*!
     * \brief Рисует линию в трехмерном пространстве
     * \param dx - смещение по координате X
     * \param dy - смещение по координате Y
     * \param dz - смещение по координате Z
     * \param v - скорость отрисовки (по умолчнию 1)
     */
    void drawLine(double dx, double dy, double dz, double v = 1);

    /*!
     * \brief Рисует линию между текущей точкой и точкой, указанной в параметрах
     * \param dest - точка, в которую нужно провести линию
     * \param v - скорость отрисовки
     */
    void drawTTLine(Point3D dest, double v = 1);

    /*!
     * \brief Рисует воздушный переход между текущей точкой и точкой, указанной в параметрах
     * \param dest - точка, в которую нужно сделать воздушный переход
     * \param dz - смещение по оси Z при воздушном переходе
     * \param v - скорость отрисовки
     */
    void drawAirPassage(Point3D dest, double dz, double v = 1);

    /*!
     * \brief Рисует точку
     * \param src - точка для отрисовки
     * \param text - текст для подписи точки
     */
    void drawPoint(Point3D src = Point3D(), QString text = "");

    /*!
     * \brief Приближает или удаляет сцену
     * \param delta - коэффициент приближения/отдаления (в зависимости от знака)
     */
    void scaling(int delta);

    /*!
     * \brief Вращает сцену
     */
    void rotate();

    /*!
     * \brief Перемещает сцену
     */
    void move();

    /*!
     * \brief Устанавливает угол поворота оси X
     * \param angle - угол поворота оси X
     */
    void setXAngle(double angle);

    /*!
     * \brief Устанавливает угол поворота по оси Z
     * \param angle - угол поворота по оси Z
     */
    void setZAngle(double angle);

    /*!
     * \brief Возвращает текущий коэффициент приближения/отдаления сцены
     * \return коэффициент приближения/отдаления сцены
     */
    double getScale() const;

    /*!
     * \brief Устанавливает значение коэффициента приближения/отдаления сцены
     * \param value - значение коэффициента приближения/отдаления сцены
     */
    void setScale(double value);

    /*!
     * \brief Осуществляет перерисовку виджета
     */
    void updateField();

    /*!
     * \brief Возвращает значение переменной, отвечающей за то, нужно ли отрисовывать точки
     * \return значение переменной, отвечающей за то, нужно ли отрисовывать точки
     */
    bool getPointsVisible() const;

    /*!
     * \brief Устанавливает значение переменной, отвечающей за то, нужно ли отрисовывать точки
     * \param value - значение переменной, отвечающей за то, нужно ли отрисовывать точки
     */
    void setPointsVisible(bool value);

    /*!
     * \brief Возвращает указатель на менеджер точек
     * \return указатель на менеджер точек
     */
    PointsManager* getPointsManager() const;

    /*!
     * \brief Устанавливает значение указателя на менеджер точек
     * \param value - указатель на менеджер точек
     */
    void setPointsManager(PointsManager *value);

    /*!
     * \brief Возвращает указатель на интерпретоатор команд
     * \return указатель на интерпретоатор команд
     */
    CommandsInterpreter *getCommandsInterpreter() const;

    /*!
     * \brief Устанавливает значение указателя на интерпретатор команд
     * \param value - указатель на интерпретоатор команд
     */
    void setCommandsInterpreter(CommandsInterpreter *value);

    /*!
     * \brief Возвращает размер сетки
     * \return размер сетки
     */
    unsigned int getGridSize() const;

    /*!
     * \brief Устанавливает размер сетки
     * \param value - размер сетки
     */
    void setGridSize(unsigned int value);

    /*!
     * \brief Возвращает значение переменной, отвечающей за то, нужно ли отображать сетку
     * \return значение переменной, отвечающей за то, нужно ли отображать сетку
     */
    bool getGridVisible() const;

    /*!
     * \brief Устанавливает значение переменной, отвечающей за то, нужно ли отображать сетку
     * \param value - значение переменной, отвечающей за то, нужно ли отображать сетку
     */
    void setGridVisible(bool value);

    /*!
     * \brief Возвращает размер ячейки сетки
     * \return размер ячейки сетки
     */
    double getGridCellSize() const;

    /*!
     * \brief Устанавливает размер ячейки сетки
     * \param value - размер ячейки сетки
     */
    void setGridCellSize(double value);

    /*!
     * \brief Возвращает строковый идентификатор плоскости для отрисовки сетки
     * \return строковый идентификатор плоскости для отрисовки сетки (например "X0Y")
     */
    std::string getGridPlane() const;

    /*!
     * \brief Возвращает строковый идентификатор плоскости для отрисовки сетки
     * \param value - строковый идентификатор плоскости для отрисовки сетки (например "X0Y")
     */
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

    Point3D getCurrentPoint() const;
    void setCurrentPoint(const Point3D &value);

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
    //double angleY = 0;
    double angleZ = 0;
    int mousePositionX = 0;
    int mousePositionY = 0;

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
    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void wheelEvent(QWheelEvent *wheelEvent);

    bool updateOffsetsIsNeed = false;
    Point3D maxPositiveOffset = Point3D();
    Point3D maxNegativeOffset = Point3D();
    Point3D generalOffset = Point3D();


    void updateOffsets(Point3D newVertex);

    Point3D currentPoint = Point3D();
    bool updateCurrentPointIsNeed = false;
    void updateCurrentPoint(Point3D destination);
};

#endif // OGLWIDGET_H
