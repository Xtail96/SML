#ifndef COLORS_H
#define COLORS_H

#include <QString>

/*!
 * \brief Структура SML-цвета
 * Возвращает цвет в формтае QString с помощью соответсвующего static метода
 */
struct Colors
{
    /*!
     * \brief Возвращает зеленый цвет
     * \return #2e8b57
     */
    static QString green()
    {
        return QString("#2e8b57");
    }

    /*!
     * \brief Возвращает светло-зеленый цвет
     * \return #55bb55
     */
    static QString lightGreen()
    {
        return QString("#55bb55");
    }

    /*!
     * \brief Возвращает красный цвет
     * \return #b22222
     */
    static QString red()
    {
        return QString("#b22222");
    }

    /*!
     * \brief Возвращает серый цвет
     * \return #333
     */
    static QString gray()
    {
        return QString("#333");
    }

    /*!
     * \brief Возвращает светло-серый цвет
     * \return #dfdfdf
     */
    static QString lightGray()
    {
        return QString("#888");
    }

    /*!
     * \brief Возвращает белый цвет
     * \return #fff
     */
    static QString white()
    {
        return QString("#fff");
    }

    /*!
     * \brief Возвращает голубой цвет
     * \return #4682b4
     */
    static QString blue()
    {
        return QString("#4682b4");
    }

};

#endif // COLORS_H
