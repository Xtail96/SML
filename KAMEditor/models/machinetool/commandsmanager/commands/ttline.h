#ifndef TTLINE_H
#define TTLINE_H

#include "command.h"

class TTLine : public Command
{
public:
    TTLine(PointsManager* _pointsManager, unsigned int _destinationPointNumber, bool _airPassageIsNeed, double _dz, double _v = 1);
    ~TTLine();

    byte_array getDataForMachineTool() const override;

    void draw(OGLWidget* w, Point3D sourcePoint = Point3D()) const override;

    Point3D returnDestinationPoint(Point3D sourcePoint = Point3D()) const override;

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
    size_t id = CMD_LINE;
    std::string name = "ТТ-Линия";

    PointsManager* pointsManager;
    unsigned int destinationPointNumber;
    bool airPassageIsNeed;
    double dz;
    double v;
    QColor color = SmlColors::gray();
};

#endif // TTLINE_H
