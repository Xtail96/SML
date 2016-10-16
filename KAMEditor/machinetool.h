#ifndef MACHINETOOL_H
#define MACHINETOOL_H


/**
 * \brief Класс "Станок"
 * \warning Является синглтоном
 *
 * Данный класс отвечает за управление станком:
 * \dot Перемещение по координатам
 * \dot ...
 */
class MachineTool
{
public:
    /// Возвращает один и тот же экземпляр класса MachineTool
    static MachineTool& Instance()
    {
        static MachineTool m;
        return m;
    }

private:
    // конструктор и деструктор недоступны публично
    MachineTool();
    ~MachineTool();

    // запрет копирования
    MachineTool(MachineTool const&);
    MachineTool& operator=(MachineTool const&);
};

#endif // MACHINETOOL_H
