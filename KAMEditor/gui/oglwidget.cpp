#include "oglwidget.h"

#include "models/machinetool/commandsmanager/commands/commands.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

OGLWidget::OGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

void OGLWidget::initializeGL()
{
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //auto commands = CommandInterpreter::Instance().getCommands();

    /*for (auto command : commands)
        command->draw(this);*/
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();/*
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/
}
