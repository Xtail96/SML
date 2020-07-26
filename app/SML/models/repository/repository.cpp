#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_settingsManager(),
    m_gcodesFilesManager(this),
    m_points(QList<Point>()),
    m_zeroCoordinates(Point()),
    m_parkCoordinates(Point()),
    m_velocity(0),
    m_movementStep(0)
{
}

void Repository::setGCodes(const QString &data)
{
    try
    {
        m_gcodesFilesManager.setFileContent(data);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setGCodes: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

QStringList Repository::getGCodesProgram()
{
    QStringList result = {};

    try
    {
        result = m_gcodesFilesManager.getContent();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getGCodesProgram: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return result;
}

QStringList Repository::getOptionsLabels()
{
    /// todo: переписать метод
    QStringList optionsNames =
    {
        "Кабриоль",
        "ДВИ",
        "САС"
    };
    return optionsNames;
}

double Repository::getMovementStep() const
{
    return m_movementStep;
}

void Repository::setMovementStep(double movementStep)
{
    m_movementStep = movementStep;
}

Point Repository::getZeroCoordinates() const
{
    return m_zeroCoordinates;
}

void Repository::setZeroCoordinates(const Point &zeroCoordinates)
{
    m_zeroCoordinates = zeroCoordinates;
}

Point Repository::getParkCoordinates() const
{
    return m_parkCoordinates;
}

void Repository::setParkCoordinates(const Point &parkCoordinates)
{
    m_parkCoordinates = parkCoordinates;
}

void Repository::addPoint(QMap<QString, double> coords)
{
    try
    {
        Point p;
        for(auto axisUid : coords.keys())
        {
            p.insertAxis(axisUid, coords[axisUid]);
        }
        m_points.append(p);

        emit this->pointsUpdated();
    }
    catch(...)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Не удалось добавить точку").exec();
        qDebug() << QStringLiteral("Repository::addPoint: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

QList<Point> Repository::getPoints()
{
    return m_points;
}

Point Repository::getPoint(unsigned int index)
{
    if(m_points.size() <= int(index)) throw OutOfRangeException("Point with index " + QString::number(index) + " doest not exists");
    return m_points[int(index)];
}

void Repository::deletePoint(unsigned int index)
{
    if(m_points.size() <= int(index)) throw OutOfRangeException("Point with index " + QString::number(index) + " doest not exists");
    m_points.removeAt(int(index));

    emit this->pointsUpdated();
}

void Repository::updatePoint(QMap<QString, double> coordinates, unsigned int index)
{
    if(m_points.size() <= int(index)) throw OutOfRangeException("Point with index " + QString::number(index) + " doest not exists");
    m_points.replace(int(index), Point(coordinates));

    emit this->pointsUpdated();
}

QString Repository::getFilePath(QString type)
{
    QString path = "";

    try
    {
        if(type == "gcodes")
        {
            path = m_gcodesFilesManager.getFilePath();
        }
        else
        {
            if(type == "sml")
            {
                path = "sml file path";
            }
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getFilePath: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return path;
}

void Repository::exportSettings()
{
    try
    {
        QString path = QFileDialog::getSaveFileName(nullptr, "Выберите путь до файла", "", "*.ini");
        m_settingsManager.exportSettings(path);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::exportSettings: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::importSettings()
{
    try
    {
        QString path = QFileDialog::getOpenFileName(nullptr, "Выберите файл с настройками", "", "*.ini");
        m_settingsManager.importSettings(path);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::importSettings: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::openGCodesFile()
{
    try
    {
        m_gcodesFilesManager.openGCodesFile();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::openGCodesFile: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::saveGCodesFile(const QString data)
{
    try
    {
        m_gcodesFilesManager.setFileContent(data);
        m_gcodesFilesManager.saveGCodesFile();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::saveGCodesFile: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::saveGCodesFileAs(const QString data)
{
    try
    {
        m_gcodesFilesManager.setFileContent(data);
        m_gcodesFilesManager.saveGCodesFileAs();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::saveGCodesFileAs: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::newGCodesFile()
{
    try
    {
        m_gcodesFilesManager.newGCodesFile();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::newGCodesFile: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::addGCodesFile(const QString data)
{
    try
    {
        this->saveGCodesFile(data);
        m_gcodesFilesManager.addGCodesFile();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::addGCodesFile: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}
