#ifndef SMLTTTARC_H
#define SMLTTTARC_H

#include "smlcommand.h"

class SMLTTTArc : public SMLCommand
{
public:
    SMLTTTArc(PointsManager* _pointsManager, QString _middlePointNumber, QString _endPointNumber, QString _v = QString::number(1));
    ~SMLTTTArc();

    byte_array getDataForMachineTool() const override;

    void draw(OGLWidget* w) const override;

    size_t getId() const override;

    QString getName() const override;

    /**
     * @return строковое представление каждого из аргументов текущей команды
     */
    QStringList getArguments() const override;

    void setArguments(const QStringList arguments) override;

    /**
     * @return подробное строковое представление аргументов текущей команды
     */
    QString getArgumentsString() const override;

    QColor getColor() const override;

    bool isArgumentsCorrect() const override;

private:
    size_t id = CMD_TTTARC;
    const QString name = "ТТT-Дуга";
    PointsManager* pointsManager;

    QString middlePointNumber;
    QString endPointNumber;
    QString v;
    QColor color = SmlColors::gray();
};

#endif // SMLTTTARC_H
