#ifndef MACHINETOOL_H
#define MACHINETOOL_H


class MachineTool
{
public:
    // всегда возвращает один и тот же экземпляр класса MachineTool
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
