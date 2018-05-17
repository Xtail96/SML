#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <thread>
#include <stack>
#include <string>
#include <map>

#include "models/machinetool/commandsmanager/commands/smlcommandsbuilder.h"

class PointsManager;
class DevicesManager;

/*!
 * \brief Класс интерпретатор SML-команд
 * \warning Методы данного класса являются статическими и не привязаны к какому-либо объекту
 */
class CommandsInterpreter
{
public:
    /*!
     * \brief Конструктор класса интерпретатор SML-команд
     */
    CommandsInterpreter();

    /*!
      * \brief Деструктор класса интерпретатор SML-команд
      */
    ~CommandsInterpreter();

    /*!
     * \brief Обновляет УП для станка
     * \param commands список команд
     * \param pointsmanager менеджер точек
     * \param devicesManager менеджер устройств
     * \return Обновленный список команд
     */
    static std::vector< std::shared_ptr<SMLCommand> > updateProgram(
            std::vector< std::shared_ptr<SMLCommand> > commands,
            PointsManager* pointsmanager,
            DevicesManager* devicesManager);


    /*!
     * \brief Конструирует УП для станка
     * \param commands список команд
     * \param pointsmanager менеджер точек
     * \param devicesManager менеджер устройств
     * \return Обновленный список команд
     */
    static std::vector< std::shared_ptr<SMLCommand> > makeProgram(
            std::vector< std::shared_ptr<SMLCommand> > commands,
            PointsManager* pointsManager,
            DevicesManager* devicesManager);
private:

    /*!
     * \brief Подставляет значения переменных по их именам
     * \param commands список команд
     */
    static std::vector< std::shared_ptr<SMLCommand> > inlineVariables(
            std::vector< std::shared_ptr<SMLCommand> > commands);

    /*!
     * \brief Подставляет значение одной переменной по ее имени во все места, где это нужно
     * \param key имя переменной
     * \param value значение переменной
     * \param commands список команд
     * \return Обновленный список команд
     */
    static std::vector< std::shared_ptr<SMLCommand> > inlineVariable(
            QString key, QString value, std::vector<std::shared_ptr<SMLCommand> > commands);

    /*!
     * \brief Удаляет из УП коментарии
     * \param commands список команд
     * \return Обновленный список команд
     */
    static std::vector< std::shared_ptr<SMLCommand> > eraseComments(
            std::vector<std::shared_ptr<SMLCommand> > commands);

    /*!
     * \brief Удаляет одну или несколько команд из списка команд
     * \param indexes список индексов удаляемых команд
     * \param commands список команд, из которых необходимо произвести уаление
     * \return Обновленный список команд
     */
    static std::vector< std::shared_ptr<SMLCommand> > eraseCommands(
            QList<size_t> indexes,
            std::vector<std::shared_ptr<SMLCommand> > commands);
};

#endif // COMMANDINTERPRETER_H
