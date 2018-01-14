#include "gcodesviewwidget.h"

GCodesViewWidget::GCodesViewWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    //gCodesProgram = gpr::parse_gcode("");
}

GCodesViewWidget::~GCodesViewWidget()
{

}

void GCodesViewWidget::initializeGL()
{
    glClearColor(0.913, 0.933, 0.996, 1);
    glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    rotate();
}

void GCodesViewWidget::paintGL()
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

        drawGCodes();

        /*if(pointsVisible)
        {
            drawPoints();
        }

        if(gridVisible)
        {
            drawGrid();
        }*/
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

void GCodesViewWidget::drawCoordinatesVectors()
{
    glLineWidth(2.0f);
    glDisable(GL_LINE_STIPPLE);

    bool tmp = absolutePositioning;
    absolutePositioning = true;
    //updateCurrentPointIsNeed = false;

    currentPoint.x = 0;
    currentPoint.y = 0;
    currentPoint.z = 0;

    glColor3f(1, 0, 0);
    drawLine(10, 0, 0);
    drawPoint(Point3D(10, 0, 0), "X");

    glColor3f(0, 1, 0);
    drawLine(0, 10, 0);
    drawPoint(Point3D(0, 10, 0), "Y");

    glColor3f(0, 0, 1);
    drawLine(0, 0, 10);
    drawPoint(Point3D(0, 0, 10), "Z");

    absolutePositioning = tmp;
}

void GCodesViewWidget::drawGCodes()
{
    glLineWidth(3.0f);

    size_t programLength = gCodes.num_blocks();
    for(size_t i = 0; i < programLength; i++)
    {
        gpr::block currentBlock = gCodes.get_block(i);
        gpr::chunk currentChunk = currentBlock.get_chunk(0);
        switch (currentChunk.tp())
        {
        case gpr::CHUNK_TYPE_WORD_ADDRESS:
        {
            if(currentChunk.get_word() == 'G')
            {
                if(currentChunk.get_address().tp() == gpr::ADDRESS_TYPE_INTEGER)
                {
                    switch (currentChunk.get_address().int_value())
                    {
                    case 0:
                        // G0
                        drawG0(i);
                        break;
                    case 1:
                        // G1
                        drawG1(i);
                        break;
                    case 90:
                        absolutePositioning = true;
                        break;
                    case 91:
                        absolutePositioning = false;
                        break;
                    default:
                        break;
                    }
                }
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

void GCodesViewWidget::drawG0(size_t index)
{
    Point3D arguments;

    gpr::block currentBlock = gCodes.get_block(index);
    size_t blockLength = currentBlock.size();
    for(size_t i = 0; i < blockLength; i++)
    {
        gpr::chunk currentChunk = currentBlock.get_chunk(i);
        if(currentChunk.tp() == gpr::CHUNK_TYPE_WORD_ADDRESS)
        {
            if(currentChunk.get_word() == 'X')
            {
                if(currentChunk.get_address().tp() == gpr::ADDRESS_TYPE_DOUBLE)
                {
                    arguments.x = currentChunk.get_address().double_value();
                }
            }

            if(currentChunk.get_word() == 'Y')
            {
                if(currentChunk.get_address().tp() == gpr::ADDRESS_TYPE_DOUBLE)
                {
                    arguments.y = currentChunk.get_address().double_value();
                }
            }

            if(currentChunk.get_word() == 'Z')
            {
                if(currentChunk.get_address().tp() == gpr::ADDRESS_TYPE_DOUBLE)
                {
                    arguments.z = currentChunk.get_address().double_value();
                }
            }
        }
    }

    qglColor(Qt::darkGray);
    drawLine(arguments.x, arguments.y, arguments.z);
}

void GCodesViewWidget::drawG1(size_t index)
{
    drawG0(index);
}

void GCodesViewWidget::updateField()
{
    updateGL();
}

void GCodesViewWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    mousePositionX = mouseEvent->x();
    mousePositionY = mouseEvent->y();
}

void GCodesViewWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{

    double dx = (mouseEvent->x() - mousePositionX) / 10;
    double dy = (mouseEvent->y() - mousePositionY) / 10;

    if (mouseEvent->buttons() == Qt::LeftButton)
    {
        setPositionX(positionX + dx/1000);
        setPositionY(positionY + dy/1000);
    }
    else
    {
        if(mouseEvent->buttons() == Qt::RightButton)
        {
            setAngleX(angleX + 1 * dy);
            setAngleZ(angleZ + 1 * dx);
        }
    }
    updateGL();
}

void GCodesViewWidget::wheelEvent(QWheelEvent *wheelEvent)
{
    scaling(wheelEvent->delta());
}

void GCodesViewWidget::rotate()
{
    glRotated(angleX, 1, 0, 0);
    //glRotated(angleY, 0, 1, 0);
    glRotated(angleZ, 0, 0, 1);
}

void GCodesViewWidget::move()
{
    glTranslatef(0.5f*positionX, -(0.5f*positionY), 0);
}

void GCodesViewWidget::scaling(int delta)
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

void GCodesViewWidget::resizeGL(int w, int h)
{
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void GCodesViewWidget::drawPoint(Point3D src, QString text)
{
    glBegin(GL_POINTS);
    glVertex3f(src.x, src.y, src.z);
    glEnd();
    renderText(src.x, src.y, src.z, text);
}

void GCodesViewWidget::updateCurrentPoint(Point3D destination)
{
    currentPoint = destination;
}

void GCodesViewWidget::drawLine(double dx, double dy, double dz)
{
    double newX;
    double newY;
    double newZ;

    if(absolutePositioning)
    {
        newX = dx;
        newY = dy;
        newZ = dz;
        currentPoint = Point3D(0, 0, 0);
    }
    else
    {
        newX = currentPoint.x + dx;
        newY = currentPoint.y + dy;
        newZ = currentPoint.z + dz;
    }

    if(newZ > 0 && !absolutePositioning)
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
    //updateOffsets(destinaton);
    updateCurrentPoint(destinaton);
}

double GCodesViewWidget::getScale() const
{
    return scale;
}

void GCodesViewWidget::setScale(double value)
{
    scale = value;
}

void GCodesViewWidget::setGCodesProgram(const QString &value)
{
    std::string data = value.toStdString();
    gpr::gcode_program program = gpr::parse_gcode(data);
    gCodes = program;

    // вывод в консоль
    size_t programLength = gCodes.num_blocks();
    for(size_t i = 0; i < programLength; i++)
    {
        try
        {
            qDebug() << "";
            qDebug() << "New Block " << i;
            for(size_t j = 0; j < gCodes.get_block(i).size(); j++)
            {
                if(gCodes.get_block(i).get_chunk(j).tp() == gpr::CHUNK_TYPE_COMMENT)
                {
                    qDebug() << "chunk #" << j << "(comment)  = " << QString::fromStdString(gCodes.get_block(i).get_chunk(j).get_comment_text());
                }
                else
                {
                    if(gCodes.get_block(i).get_chunk(j).tp() == gpr::CHUNK_TYPE_WORD_ADDRESS)
                    {
                        qDebug() << "chunk #" << j << "(word)  = " << gCodes.get_block(i).get_chunk(j).get_word();
                    }
                    //qDebug() << "chunk #" << j << "(single word)  = " << gCodes.get_block(i).get_chunk(i).get_single_word();

                    //qDebug() << "chunk #" << j << "(left delim)  = " << gCodes.get_block(i).get_chunk(i).get_left_delim();
                    //qDebug() << "chunk #" << j << "(right delim)  = " << gCodes.get_block(i).get_chunk(i).get_right_delim();

                    if(gCodes.get_block(i).get_chunk(j).get_address().tp() == gpr::ADDRESS_TYPE_INTEGER)
                    {
                        qDebug() << "chunk #" << j << "(address int value)  = " << gCodes.get_block(i).get_chunk(j).get_address().int_value();
                    }
                    else
                    {
                        if(gCodes.get_block(i).get_chunk(j).get_address().tp() == gpr::ADDRESS_TYPE_DOUBLE)
                        {
                            qDebug() << "chunk #" << j << "(address double value)  = " << gCodes.get_block(i).get_chunk(j).get_address().double_value();
                        }
                    }
                }

            }
            qDebug() << "";
        }
        catch(...) {}
        //qDebug() << QString::fromStdString(gCodesProgram.get_block(i).to_string());
    }
    /*size_t programLength = gCodes.num_blocks();
    for(size_t i = 0; i < programLength; i++)
    {
        qDebug() << QString::fromStdString(gCodes.get_block(i).to_string());
    }*/
}

double GCodesViewWidget::getAngleX() const
{
    return angleX;
}

void GCodesViewWidget::setAngleX(double value)
{
    if(value >= 180)
    {
        angleX = 0;
    }
    else
    {
        angleX = value;
    }
}

double GCodesViewWidget::getAngleZ() const
{
    return angleZ;
}

void GCodesViewWidget::setAngleZ(double value)
{
    if(value >= 180)
    {
        angleZ = 0;
    }
    else
    {
        angleZ = value;
    }
}

double GCodesViewWidget::getPositionY() const
{
    return positionY;
}

void GCodesViewWidget::setPositionY(double value)
{
    positionY = value;
}

double GCodesViewWidget::getPositionX() const
{
    return positionX;
}

void GCodesViewWidget::setPositionX(double value)
{
    positionX = value;
}

int GCodesViewWidget::getMousePositionX() const
{
    return mousePositionX;
}

void GCodesViewWidget::setMousePositionX(int value)
{
    mousePositionX = value;
}

int GCodesViewWidget::getMousePositionY() const
{
    return mousePositionY;
}

void GCodesViewWidget::setMousePositionY(int value)
{
    mousePositionY = value;
}
