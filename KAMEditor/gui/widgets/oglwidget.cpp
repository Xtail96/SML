#include "oglwidget.h"

#include "models/machinetool/commandsmanager/commands/smlcommands.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

OGLWidget::OGLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

}

void OGLWidget::initializeGL()
{
    glClearColor(0.913, 0.933, 0.996, 1);
    glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    rotate();
}

void OGLWidget::paintGL()
{
    try
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Задаем режим матрицы
        glMatrixMode(GL_PROJECTION);

        //Загружаем матрицу
        glLoadIdentity();

        move();
        rotate();

        glScalef(scale, scale, scale);
        drawCoordinatesVectors();

        drawCommands();

        if(pointsVisible)
        {
            drawPoints();
        }

        if(gridVisible)
        {
            drawGrid();
        }
#ifdef Q_OS_MACOS
    swapBuffers();
#endif
    }
    catch(...)
    {
        this->setUpdatesEnabled(false);
        this->close();
        QMessageBox(QMessageBox::Warning, "Ошибка", "Невозможно отобразить траекторию движения").exec();
    }
}

void OGLWidget::drawCoordinatesVectors()
{
    glLineWidth(2.0f); 
    glDisable(GL_LINE_STIPPLE);

    updateOffsetsIsNeed = false;
    updateCurrentPointIsNeed = false;

    currentPoint.x = 0;
    currentPoint.y = 0;
    currentPoint.z = 0;

    glColor3f(1, 0, 0);
    drawLine(10, 0, 0, 1);
    renderText(10, 0, 0, "X");

    glColor3f(0, 1, 0);
    drawLine(0, 10, 0, 1);
    renderText(0, 10, 0, "Y");

    glColor3f(0, 0, 1);
    drawLine(0, 0, 10, 1);
    renderText(0, 0, 10, "Z");
}

void OGLWidget::drawCommands()
{
    glLineWidth(3.0f);

    updateOffsetsIsNeed = true;
    updateCurrentPointIsNeed = true;

    for(auto command : m_commands)
    {
        qglColor(Qt::darkGray);
        command->draw(this);
    }
}

void OGLWidget::drawPoints()
{
    glPointSize(3.0f);


    updateOffsetsIsNeed = false;

    for(unsigned int i = 0; i < points.size(); i++)
    {
        glColor3f(0, 0, 0);
        drawPoint(*(points[i].get()), QString::number(i+1));
    }
}

void OGLWidget::drawGrid()
{
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1111);
    glLineWidth(1.0f);

    updateOffsetsIsNeed = false;

    qglColor(Qt::lightGray);


    Point3D tmp = currentPoint;

    currentPoint.x = 0;
    currentPoint.y = 0;
    currentPoint.z = 0;

    updateCurrentPointIsNeed = false;

    double multiplier = 1/gridMaximalAccuracy;
    unsigned int step = gridCellSize*multiplier;
    unsigned int stepCount = gridSize*multiplier;

    for(unsigned int i = 0; i <= stepCount; i+=step)
    {
        if(gridPlane == "X0Y")
        {
            drawLine(gridSize, 0, 0);
            currentPoint.y += gridCellSize;
        }
        else
        {
            if(gridPlane == "X0Z")
            {
                drawLine(gridSize, 0, 0);
                currentPoint.z += gridCellSize;
            }
            else
            {
                if(gridPlane == "Y0Z")
                {
                    drawLine(0, gridSize, 0);
                    currentPoint.z += gridCellSize;
                }
            }
        }
    }

    currentPoint.x = 0;
    currentPoint.y = 0;
    currentPoint.z = 0;

    for(unsigned int i = 0; i <= stepCount; i+=step)
    {
        if(gridPlane == "X0Y")
        {
            drawLine(0, gridSize, 0);
            currentPoint.x += gridCellSize;
        }
        else
        {
            if(gridPlane == "X0Z")
            {
                drawLine(0, 0, gridSize);
                currentPoint.x += gridCellSize;
            }
            else
            {
                if(gridPlane == "Y0Z")
                {
                    drawLine(0, 0, gridSize);
                    currentPoint.y += gridCellSize;
                }
            }
        }
    }

    currentPoint = tmp;
    updateCurrentPointIsNeed = true;
}

void OGLWidget::setPoints(const std::vector<std::shared_ptr<Point3D> > &value)
{
    points = value;
}

void OGLWidget::setCommands(const std::vector<std::shared_ptr<SMLCommand> > &value)
{
    m_commands = value;
}

double OGLWidget::getGridMaximalAccuracy() const
{
    return gridMaximalAccuracy;
}

void OGLWidget::setGridMaximalAccuracy(double value)
{
    gridMaximalAccuracy = value;
}

std::string OGLWidget::getGridPlane() const
{
    return gridPlane;
}

void OGLWidget::setGridPlane(const std::string &value)
{
    gridPlane = value;
}

double OGLWidget::getGridCellSize() const
{
    return gridCellSize;
}

void OGLWidget::setGridCellSize(double value)
{
    gridCellSize = value;
}

bool OGLWidget::getGridVisible() const
{
    return gridVisible;
}

void OGLWidget::setGridVisible(bool value)
{
    gridVisible = value;
}

unsigned int OGLWidget::getGridSize() const
{
    return gridSize;
}

void OGLWidget::setGridSize(unsigned int value)
{
    gridSize = value;
}

bool OGLWidget::getPointsVisible() const
{
    return pointsVisible;
}

void OGLWidget::setPointsVisible(bool value)
{
    pointsVisible = value;
}

double OGLWidget::getScale() const
{
    return scale;
}

void OGLWidget::setScale(double value)
{
    scale = value;
}

void OGLWidget::updateField()
{
    updateGL();
}

void OGLWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    mousePositionX = mouseEvent->x();
    mousePositionY = mouseEvent->y();
}

double OGLWidget::getPositionY() const
{
    return positionY;
}

void OGLWidget::setPositionY(double value)
{
    positionY = value;
}

double OGLWidget::getPositionX() const
{
    return positionX;
}

void OGLWidget::setPositionX(double value)
{
    positionX = value;
}

void OGLWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{

    double dx = (mouseEvent->x() - mousePositionX) / 10;
    double dy = (mouseEvent->y() - mousePositionY) / 10;

    if (mouseEvent->buttons() == Qt::LeftButton)
    {
        //setXAngle(angleX - 1 * dy);
        //setYAngle(angleY - 1 * dx);
        setPositionX(positionX + dx/1000);
        setPositionY(positionY + dy/1000);
    }
    else
    {
        if(mouseEvent->buttons() == Qt::RightButton)
        {
            setXAngle(angleX + 1 * dy);
            setZAngle(angleZ + 1 * dx);
        }
    }
    updateGL();
}

void OGLWidget::rotate()
{
    glRotated(angleX, 1, 0, 0);
    //glRotated(angleY, 0, 1, 0);
    glRotated(angleZ, 0, 0, 1);
}

void OGLWidget::setXAngle(double angle)
{
    if(angle >= 180)
    {
        angleX = 0;
    }
    else
    {
        angleX = angle;
    }
}

void OGLWidget::setZAngle(double angle)
{
    if(angle >= 180)
    {
        angleZ = 0;
    }
    else
    {
        angleZ = angle;
    }
}

void OGLWidget::move()
{
    glTranslatef(0.5f*positionX, -(0.5f*positionY), 0);
}

void OGLWidget::wheelEvent(QWheelEvent *wheelEvent)
{
    scaling(wheelEvent->delta());
}

Point3D OGLWidget::getGeneralOffset() const
{
    return generalOffset;
}

void OGLWidget::setGeneralOffset(const Point3D &value)
{
    generalOffset = value;
}

Point3D OGLWidget::getMaxNegativeOffset() const
{
    return maxNegativeOffset;
}

void OGLWidget::setMaxNegativeOffset(const Point3D &value)
{
    maxNegativeOffset = value;
}

Point3D OGLWidget::getMaxPositiveOffset() const
{
    return maxPositiveOffset;
}

void OGLWidget::setMaxPositiveOffset(const Point3D &value)
{
    maxPositiveOffset = value;
}

void OGLWidget::updateOffsets(Point3D newVertex)
{
    if(updateOffsetsIsNeed)
    {
        bool emitSignalIsNeed = false;
        if(newVertex.x > maxPositiveOffset.x)
        {
            maxPositiveOffset.x = newVertex.x;
            generalOffset.x = std::fabs(maxPositiveOffset.x) + std::fabs(maxNegativeOffset.x);
            emitSignalIsNeed = true;
        }
        if(newVertex.y > maxPositiveOffset.y)
        {
            maxPositiveOffset.y = newVertex.y;
            generalOffset.y = std::fabs(maxPositiveOffset.y) + std::fabs(maxNegativeOffset.y);
            emitSignalIsNeed = true;
        }
        if(newVertex.z > maxPositiveOffset.z)
        {
            maxPositiveOffset.z = newVertex.z;
            generalOffset.z = std::fabs(maxPositiveOffset.z) + std::fabs(maxNegativeOffset.z);
            emitSignalIsNeed = true;
        }

        if(newVertex.x < maxNegativeOffset.x)
        {
            maxNegativeOffset.x = newVertex.x;
            generalOffset.x = std::fabs(maxPositiveOffset.x) + std::fabs(maxNegativeOffset.x);
            emitSignalIsNeed = true;
        }
        if(newVertex.y < maxNegativeOffset.y)
        {
            maxNegativeOffset.y = newVertex.y;
            generalOffset.y = std::fabs(maxPositiveOffset.y) + std::fabs(maxNegativeOffset.y);
            emitSignalIsNeed = true;
        }
        if(newVertex.z < maxNegativeOffset.z)
        {
            maxNegativeOffset.z = newVertex.z;
            generalOffset.z = std::fabs(maxPositiveOffset.z) + std::fabs(maxNegativeOffset.z);
            emitSignalIsNeed = true;
        }
        if(emitSignalIsNeed)
        {
            emit offsetsChanged();
        }
    }
}

void OGLWidget::updateCurrentPoint(Point3D destination)
{
    if(updateCurrentPointIsNeed)
    {
        currentPoint.x = destination.x;
        currentPoint.y = destination.y;
        currentPoint.z = destination.z;
    }
}

Point3D OGLWidget::getCurrentPoint() const
{
    return currentPoint;
}

void OGLWidget::setCurrentPoint(const Point3D &value)
{
    currentPoint = value;
}

void OGLWidget::scaling(int delta)
{
    // если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
    // иначе - делим на 1.1
    if (delta > 0)
    {
        scale *= 1.1;
    }
    else
    {
        if (delta < 0)
        {
            scale /= 1.1;
        }
    }
    updateGL();
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/
}

void OGLWidget::drawPoint(Point3D src, QString text)
{
    glBegin(GL_POINTS);
    glVertex3f(src.x, src.y, src.z);
    glEnd();
    renderText(src.x, src.y, src.z, text);
}

void OGLWidget::drawLine(double dx, double dy, double dz, double v)
{
    if(v < 0) {
        return;
    }

    double newX = currentPoint.x + dx;
    double newY = currentPoint.y + dy;
    double newZ = currentPoint.z + dz;

    if(newZ > 0 && updateCurrentPointIsNeed)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x1111);
    }
    else
    {
        glDisable(GL_LINE_STIPPLE);
    }

    glBegin(GL_LINES);

    glVertex3f(currentPoint.x, currentPoint.y, currentPoint.z);

    glVertex3f(newX, newY, newZ);

    glEnd();

    Point3D destinaton(newX, newY, newZ);
    updateOffsets(destinaton);
    updateCurrentPoint(destinaton);
}

void OGLWidget::drawTTLine(Point3D dest, double v)
{
    if(v < 0) {
        return;
    }

    if(dest.z > 0 && updateCurrentPointIsNeed)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x1111);
    }
    else
    {
        glDisable(GL_LINE_STIPPLE);
    }

    glBegin(GL_LINES);

    glVertex3f(currentPoint.x, currentPoint.y, currentPoint.z);

    glVertex3f(dest.x, dest.y, dest.z);

    glEnd();

    updateOffsets(dest);
    updateCurrentPoint(dest);
}

void OGLWidget::drawAirPassage(Point3D dest, double dz, double v)
{
    if(v < 0) {
        return;
    }

    double newZ = currentPoint.z + dz;
    Point3D firstVertex = Point3D(currentPoint.x, currentPoint.y, newZ);
    Point3D secondVertex = Point3D(dest.x, dest.y, newZ);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1111);

    glBegin(GL_LINES);

    glVertex3f(currentPoint.x, currentPoint.y, currentPoint.z);

    glVertex3f(firstVertex.x, firstVertex.y, firstVertex.z);

    glEnd();

    glBegin(GL_LINES);

    glVertex3f(firstVertex.x, firstVertex.y, firstVertex.z);

    glVertex3f(secondVertex.x, secondVertex.y, secondVertex.z);

    glEnd();

    glBegin(GL_LINES);

    glVertex3f(secondVertex.x, secondVertex.y, secondVertex.z);

    glVertex3f(dest.x, dest.y, dest.z);

    glEnd();

    updateOffsets(firstVertex);

    updateOffsets(secondVertex);

    updateOffsets(dest);

    updateCurrentPoint(dest);
}

void OGLWidget::drawArc(double radius, double startAngle, double arcAngle, double v)
{
    if(v < 0) {
        return;
    }

    startAngle = startAngle * M_PI / 180;
    arcAngle = arcAngle * M_PI / 180;

    double angleIncrement = 0.01;

    double x, y;

    Point3D center;
    center.x = currentPoint.x - radius;
    center.y = currentPoint.y;

    glBegin(GL_LINE_STRIP);

    for (double theta = 0; theta < arcAngle; theta += angleIncrement)
    {
        x = center.x + radius * cos(theta);
        y = center.y + radius * sin(theta);

        glVertex2f(x, y);

        Point3D newVertex(x, y, currentPoint.z);
        updateOffsets(newVertex);
        updateCurrentPoint(newVertex);
    }

    glEnd();
}

void OGLWidget::drawTTTArc(Point3D middle, Point3D end, double v)
{
    if(v < 0) {
        return;
    }

    Point3D start = currentPoint;
    double increment = 0.01;

    // менять значение sign и начальную фазу в зависимости от четверти относительно текущей точки
    int sign;
    double phase;
    if(middle.x >= start.x)
    {
        if(middle.y >= start.y)
        {
            // 1 четверть
            sign = -1;
            phase = M_PI;
        }
        else
        {
            // 4 четверть
            sign = 1;
            phase = M_PI;
        }
    }
    else
    {
        if(middle.y < start.y)
        {
            // 3 четверть
            phase = 0;
            sign = -1;
        }
        else
        {
            // 2 четверть
            phase = 0;
            sign = 1;
        }
    }

    /*
        A := x2 - x1;
        B := y2 - y1;
        C := x3 - x1;
        D := y3 - y1;
        E := A * (x1 + x2) + B * (y1 + y2);
        F := C * (x1 + x3) + D * (y1 + y3);
        G := 2 * (A * (y3 - y2) - B * (x3 - x2));
        if G = 0 then Exit;
        Cx := (D * E - B * F) / G;
        Cy := (A * F - C * E) / G;
     */

    Point3D center;
    double a = middle.x - start.x;
    double b = middle.y - start.y;
    double c = end.x - start.x;
    double d = end.y - start.y;
    double e = a * (start.x + middle.x) + b * (start.y + middle.y);
    double f = c * (start.x + end.x) + d * (start.y + end.y);
    double g = 2 * (a * (end.y - middle.y) - b * (end.x - middle.x));
    if(g == 0)
    {
        return;
    }
    center.x = (d * e - b * f) / g;
    center.y = (a * f - c * e) / g;
    this->points.push_back(std::shared_ptr<Point3D>(new Point3D(center.x, center.y, center.z)));

    //double radius = start.x - center.x;
    double radius = std::fabs(start.x - center.x);

    glBegin(GL_LINE_STRIP);

    double lim = 3.14;
    double x, y, z;
    x = start.x;
    y = start.y;
    z = start.z;
    double zStep = (end.z - start.z) * increment / lim;
    for (double theta = 0; theta < lim; theta += increment)
    {
        x = center.x + radius * cos(sign * (theta + phase));
        y = center.y + radius * sin(sign * (theta + phase));
        z += zStep;

        //glVertex2f(x, y);
        glVertex3f(x, y, z);

        Point3D newVertex(x, y, z);
        updateOffsets(newVertex);
        updateCurrentPoint(newVertex);
    }

    glEnd();


}
