#ifndef MACHINETOOL_H
#define MACHINETOOL_H

struct Point4D
{
    double x;
    double y;
    double z;

    double a;
};

/**
 * \brief Класс "Станок"
 * \warning Является синглтоном
 *
 * Данный класс отвечает за управление станком:
 *      Перемещение по координатам
 *      ...
 */
template <class T>
class MachineTool
{
public:
    /// Возвращает один и тот же экземпляр класса MachineTool
    static MachineTool<T>& Instance();

    /// Возвращает текущие координаты
    T getCurrentCoordinates();

    /// Возвращает координаты базы
    T getBaseCoordinates();

    /// Возвращает координаты парка
    T getParkCoordinates();

    /// Смещенение относительно текущих координат на offset с шагом step
    void move(T offset, double step);

    //void moveA(double a);

private:

    /// Координаты базы, абсолютные
    T base;

    /// Координаты парка, абсолютные
    T park;

    /// Координаты точки ноль относительно базы
    T zero;

    /// Текущие относительно нуля
    T current;



    // конструктор и деструктор недоступны публично
    MachineTool();
    ~MachineTool();

    // запрет копирования
    MachineTool(MachineTool const&);
    MachineTool& operator=(MachineTool const&);
};










template <class T>
MachineTool<T>& MachineTool<T>::Instance()
{
    static MachineTool<T> m;
    return m;
}


template <class T>
MachineTool<T>::MachineTool()
{

}


template <class T>
MachineTool<T>::~MachineTool()
{

}


template <class T>
T MachineTool<T>::getBaseCoordinates()
{
    return base;
}


template <class T>
T MachineTool<T>::getCurrentCoordinates()
{
    return current;
}


template <class T>
T MachineTool<T>::getParkCoordinates()
{
    return park;
}


template <class T>
void MachineTool<T>::move(T offset, double step)
{
    // шаг по x и y за 1 итерацию
    double dx, dy;
    // количество итераций
    int t;

    if (step > 0)
    {
        // дискретное движение с шагом step
        if (offset.x > offset.y)
        {
            dy = step;
            dx = offset.x * step / offset.y;

            t = offset.x / dx;
        }
        else
        {
            dx = step;
            dy = offset.y * step / offset.x;

            t = offset.y / dy;
        }


        // перемещаемся
        for (int i = 0; i < t; i++)
        {
            current.x += dx;
            current.y += dy;

            // uart move
        }
    }
    else
    {
        // непрерывное движение
    }

}


#endif // MACHINETOOL_H
