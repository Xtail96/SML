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
    Point3D destinationPoint(OGLWidget *w) const;

    size_t getId() const override;

    std::string getName() const override;

    /**
     * @return строковое представление каждого из аргументов текущей команды
     */
    QStringList getArguments() const override;

    /**
     * @return подробное строковое представление аргументов текущей команды
     */
    QString getArgumentsString() const override;

    QColor getColor() const override;

private:
    size_t id = CMD_TTLINE;
    std::string name = "ТТ-Линия";

    PointsManager* pointsManager;
    QString destinationPointNumber;
    bool airPassageIsNeed;
    QString dz;
    QString v;
    QColor color = SmlColors::gray();
};

#endif // TTLINE_H
