#ifndef GCODESVIEWWIDGET_H
#define GCODESVIEWWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QMouseEvent>
#include <QMessageBox>

#ifdef Q_OS_WIN
    #include <GL/glu.h>
    #include <GL/gl.h>
#endif

#ifdef Q_OS_MACX
    #include <OpenGL/glu.h>
    #include <OpenGL/gl.h>
#endif

#include "models/structs.h"
#include "./gpr/parser.h"

class GCodesViewWidget : public QGLWidget
{
     Q_OBJECT
signals:

public:
    GCodesViewWidget(QWidget* parent = 0);
    ~GCodesViewWidget();
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
     * \brief Осуществляет перерисовку виджета
     */
    void updateField();

    double getPositionX() const;
    void setPositionX(double value);

    double getPositionY() const;
    void setPositionY(double value);

    int getMousePositionY() const;
    void setMousePositionY(int value);

    int getMousePositionX() const;
    void setMousePositionX(int value);

    double getAngleZ() const;
    void setAngleZ(double value);

    double getAngleX() const;
    void setAngleX(double value);

    double getScale() const;
    void setScale(double value);

    void setGCodesProgram(const QString &value);

protected:
    gpr::gcode_program gCodes;

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
     * \brief Позиция сцены по оси X (начальное значение = 0)
     */
    double positionX = 0;

    /*!
     * \brief Позиция сцены по оси Y (начальное значение = 0)
     */
    double positionY = 0;

    /*!
     * \brief Текущая точка траектории (начальное значение Point(X = 0; Y = 0; Z = 0))
     */
    Point3D currentPoint = Point3D();

    /*!
     * \brief Нужно ли обновлять текущую точку траектории (начальное значение = false)
     */
    bool updateCurrentPointIsNeed = false;

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
     * \brief Обрабатывает перемещение мыши
     * \param mouseEvent - событие мыши
     */
    void mouseMoveEvent(QMouseEvent *mouseEvent);

    /*!
     * \brief Обрабатывает нажатие клавиш мыши
     * \param mouseEvent - событие мыши
     */
    void mousePressEvent(QMouseEvent *mouseEvent);

    /*!
     * \brief Обрабатывает вращение колесика мыши
     * \param wheelEvent - событие колесика мыши
     */
    void wheelEvent(QWheelEvent *wheelEvent);

    /*!
     * \brief Рисует векторы координат
     */
    void drawCoordinatesVectors();
    void drawGCodes();
    void drawG0(size_t index);
    void drawG1(size_t index);

    void drawLine(double dx, double dy, double dz);
    void drawPoint(Point3D src, QString text);

    /*!
     * \brief Обновляет теущую точку
     * \param destination - точка, которую нужно сделать текущей
     */
    //void updateCurrentPoint(Point3D destination);
};

#endif // GCODESVIEWWIDGET_H
