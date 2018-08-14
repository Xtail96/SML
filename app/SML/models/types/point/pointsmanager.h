#ifndef POINTSMANAGER_H
#define POINTSMANAGER_H

#include <vector>
#include <memory>
#include <QMessageBox>
#include "models/types/point/point.h"

#include "models/types/exceptions/exceptions.h"

/**
 * @brief Класс Менеджер точек
 * Взаимодействие с точками происходит через этот класс
 */
class PointsManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класа Менеджер точек
     */
    PointsManager(QObject* parent = nullptr);

    /**
     * @brief Конструктор копирования для класса Менеджер точек
     * @param object ссылка на объект класса Менеджер команд
     */
    PointsManager(const PointsManager &object);

    ~PointsManager();

    /**
     * @brief Добавляет точку в список точек
     * @param p указатель на добавляемую точку
     *
     * Пример:
     * \code{.cpp}
     * manager.addPoint( new Point( {0, 1, 2} ) );
     * \endcode
     */
    void addPoint(Point* p);

    /**
     * @brief Удаляет точку из списка точек
     * @param p указатель на удаляемую точку
     *
     * \warning НЕ удаляет точку, если передать указатель на копию точки, не находящейся в списке
     *
     * Пример ошибки:
     * \code{.cpp}
     * manager.addPoint( new Point( {0, 1, 2} ) );
     * Point* anotherPoint = new Point( { 0, 1, 2 } );
     * manager.deletePoint(anotherPoint); // <- точка не была удалена
     * manager.deletePoint( manager[0] ); // <- точка была удалена
     * \endcode
     *
     */
    void deletePoint(Point* p);

    /**
     * @brief Удаляет точку из списка точек
     * @param p умный указатель на удаляемую точку
     */
    void deletePoint(const QSharedPointer<Point> &p);

    /**
     * @brief Удаляет точку из списка точек
     * @param idx номер точки
     */
    void deletePoint(size_t idx);

    /**
     * @brief Удаляет точки из списка точек
     * @param beginIndex номер начальной точки
     * @param endIndex номер конечной точки
     */
    void deletePoints(size_t beginIndex, size_t endIndex);

    void updatePoint(QStringList coordinates, unsigned int number);

    /**
     * @return текущее количество точек
     */
    size_t pointCount() const;

    /**
     * @brief Задает число координат для каждой точки
     * @param num новое число координат
     */
    void setCoordinatesCount(size_t num);

    /**
     * @brief Возвращает ссылку на точку с заданным номером
     * @param idx номер точки
     * @return ссылка на умный указатель на точку
     * \warning Если заданный номер превышает число точек, бросает исключение out_of_range
     */
    QSharedPointer<Point>& operator[](size_t idx);

    Point3D getPoint3D(QString idx);
    static Point3D toPoint3D(QSharedPointer<Point> origin);

    /**
     * \brief Возвращает все точки в виде списка для вывода на экран
     * \return точки в виде списка QList<QStringList>
     */
    QList<QStringList> points();

    /**
     * \brief Возвращает координаты точки в виде списка для вывода на экран
     * \param number - номер точки (начиная с нуля)
     * \return координаты указанной точки в формате сиска QStringList
     */
    QStringList point(unsigned int number);

    /**
     * \brief Создает и возвращает новый экземпляр класса Точка
     * \param arguments - координаты точки в формате списка QStringList
     * \return новый экземпляр точки
     */
    static Point *makePoint(QStringList arguments);

protected:
    /// Список всех точек
    QList< QSharedPointer<Point> > m_points;

signals:
    void pointsUpdated();
};

#endif
