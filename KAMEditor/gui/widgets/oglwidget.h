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

class Command;

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
     * \brief Устанавливает угол поворота вокруг оси X
     * \param angle - угол поворота вокруг оси X
     */
    void setXAngle(double angle);

    /*!
     * \brief Устанавливает угол поворота вокруг оси Z
     * \param angle - угол поворота вокруг оси Z
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

    /*!
     * \brief Возвращает максимальную точность сетки
     * \return максимальная точность сетки
     */
    double getGridMaximalAccuracy() const;

    /*!
     * \brief Устанавливает максимальную точность сетки
     * \param value - максимальная точность сетки
     */
    void setGridMaximalAccuracy(double value);

    /*!
     * \brief Возвращает максимальное, на текущий момент, смещение в положительную сторону
     * \return максимальное, на текущий момент, смещение в положительную сторону
     */
    Point3D getMaxPositiveOffset() const;

    /*!
     * \brief Устанавливает максимальное, на текущий момент, смещение в положительную сторону
     * \param value - новое значение смещения в положительную сторону
     */
    void setMaxPositiveOffset(const Point3D &value);

    /*!
     * \brief Возвращает максимальное, на текущий момент, смещение в отрицательную сторону
     * \return максимальное, на текущий момент, значение смещения в отрицательную сторону
     */
    Point3D getMaxNegativeOffset() const;

    /*!
     * \brief Устанавливает максимальное, на текущий момент, смещение в отрицательную сторону
     * \param value - новое значение смещения в отрицательную сторону
     */
    void setMaxNegativeOffset(const Point3D &value);

    /*!
     * \brief Возвращает общее, на текущий момент, смещение по осям
     * \return общее, на текущий момент, смещение по осям
     */
    Point3D getGeneralOffset() const;

    /*!
     * \brief Устанавливает общее, на текущий момент, смещение по осям
     * \param value - общее, на текущий момент, смещение по осям
     */
    void setGeneralOffset(const Point3D &value);


    /*!
     * \brief Возвращает текущую позицию сцены виджета по оси X
     * \return текущая позицию сцены виджета по оси X
     */
    double getPositionX() const;

    /*!
     * \brief Устанавливает текущую позицию сцены виджета по оси X
     * \param value - позиция сцены виджета по оси X
     */
    void setPositionX(double value);

    /*!
     * \brief Возвращает текущую позицию сцены виджета по оси Y
     * \return текущая позицию сцены виджета по оси Y
     */
    double getPositionY() const;

    /*!
     * \brief Устанавливает текущую позицию сцены виджета по оси Y
     * \param value - позиция сцены виджета по оси Y
     */
    void setPositionY(double value);

    /*!
     * \brief Возвращает текущую точку траектории
     * \return текущая точка траектории
     */
    Point3D getCurrentPoint() const;

    /*!
     * \brief Устанавливает текущую точку траектории
     * \param value - точка траектории, которую нужно сделать текущей
     */
    void setCurrentPoint(const Point3D &value);

    std::vector<std::shared_ptr<Command> > getCommands() const;
    void setCommands(const std::vector<std::shared_ptr<Command> > &value);

    std::vector<std::shared_ptr<Point3D> > getPoints() const;
    void setPoints(const std::vector<std::shared_ptr<Point3D> > &value);

protected:
    /*!
     * \brief Инициализирует виджет
     */
    void initializeGL();

    /*!
     * \brief Изменияет размер виджета
     * \param w - новая ширина виджета
     * \param h - новая высота виджета
     */
    void resizeGL(int w, int h);

    /*!
     * \brief Осуществляет рисование на виджете
     */
    void paintGL();

    /*!
     * \brief Рисует векторы координат
     */
    void drawCoordinatesVectors();

    /*!
     * \brief Рисует команды
     */
    void drawCommands();

    /*!
     * \brief Рисует точки
     */
    void drawPoints();

    /*!
     * \brief Рисует сетку
     */
    void drawGrid();

    /*!
     * \brief Коэффициент приближения/отдаления сцены (начальное значение = 0.005)
     */
    double scale = 0.005;

    /*!
     * \brief Угол поворота сцены вокруг оси X (начальное значение = 0)
     */
    double angleX = 0;

    //double angleY = 0;

    /*!
     * \brief Угол поворота сцены вокруг оси Z (начальное значение = 0)
     */
    double angleZ = 0;

    /*!
     * \brief Текущая позиция мыши по оси X (начальное значение = 0)
     */
    int mousePositionX = 0;

    /*!
     * \brief Текущая позиция мыши по оси Y (начальное значение = 0)
     */
    int mousePositionY = 0;

    /*!
     * \brief Нужно ли отрисовывать сетку (начальное значение = false)
     */
    bool gridVisible = false;

    /*!
     * \brief Строковое представление плоскости для рисования сетки (начальное значение = "X0Y")
     */
    std::string gridPlane = "X0Y";

    /*!
     * \brief Размер сетки, мм (начальное значение = 1000)
     */
    unsigned int gridSize = 1000;

    /*!
     * \brief Размер ячейки сетки, мм (начальное значение = 1)
     */
    double gridCellSize = 1;

    /*!
     * \brief Максимальная точность сетки, мм (начальное значение = 0.01)
     */
    double gridMaximalAccuracy = 0.01;

    std::vector< std::shared_ptr<Command> > commands;

    /*!
     * \brief Нужно ли отрисовывать точки (начальное значение = false)
     */
    bool pointsVisible = false;

    std::vector< std::shared_ptr<Point3D> > points;

    /*!
     * \brief Обрабатывает нажатие клавиш мыши
     * \param mouseEvent - событие мыши
     */
    void mousePressEvent(QMouseEvent *mouseEvent);

    /*!
     * \brief Позиция сцены по оси X (начальное значение = 0)
     */
    double positionX = 0;

    /*!
     * \brief Позиция сцены по оси Y (начальное значение = 0)
     */
    double positionY = 0;

    /*!
     * \brief Обрабатывает перемещение мыши
     * \param mouseEvent - событие мыши
     */
    void mouseMoveEvent(QMouseEvent *mouseEvent);

    /*!
     * \brief Обрабатывает вращение колесика мыши
     * \param wheelEvent - событие колесика мыши
     */
    void wheelEvent(QWheelEvent *wheelEvent);

    /*!
     * \brief Нужно ли обновлять максимальные смещения по координатам (начальное значение = false)
     */
    bool updateOffsetsIsNeed = false;

    /*!
     * \brief Макcимальное смещение по координатам в положительную сторону (начальное значение Point(X = 0; Y = 0; Z = 0))
     */
    Point3D maxPositiveOffset = Point3D();

    /*!
     * \brief Максимальное смещение по координатам в отрицательную сторону (начальное значение Point(X = 0; Y = 0; Z = 0))
     */
    Point3D maxNegativeOffset = Point3D();

    /*!
     * \brief Максимальное общее смещение по координатам (начальное значение Point(X = 0; Y = 0; Z = 0))
     */
    Point3D generalOffset = Point3D();

    /*!
     * \brief Обновляет максимальные смещения
     * \param newVertex - новая вершина
     */
    void updateOffsets(Point3D newVertex);

    /*!
     * \brief Текущая точка траектории (начальное значение Point(X = 0; Y = 0; Z = 0))
     */
    Point3D currentPoint = Point3D();

    /*!
     * \brief Нужно ли обновлять текущую точку траектории (начальное значение = false)
     */
    bool updateCurrentPointIsNeed = false;

    /*!
     * \brief Обновляет теущую точку
     * \param destination - точка, которую нужно сделать текущей
     */
    void updateCurrentPoint(Point3D destination);
};

#endif // OGLWIDGET_H
