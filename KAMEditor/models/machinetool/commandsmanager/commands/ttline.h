#ifndef TTLINE_H
#define TTLINE_H

#include "command.h"

class TTLine : public Command
{
public:
    TTLine(PointsManager* _pointsManager, QString _destinationPointNumber, bool _airPassageIsNeed, QString _dz, QString _v = QString::number(1));
    ~TTLine();

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
    size_t id = CMD_TTLINE;
    const QString name = "ТТ-Линия";

    PointsManager* pointsManager;
    QString destinationPointNumber;
    bool airPassageIsNeed;
    QString dz;
    QString v;
    QColor color = SmlColors::gray();

    Point3D destinationPoint(OGLWidget *w) const;
};

#endif // TTLINE_H
