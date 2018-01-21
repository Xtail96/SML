#include "gcodesmanager.h"
GCodesManager::GCodesManager()
{
    m_gcodes = "";
}

GCodesManager::~GCodesManager()
{

}

void GCodesManager::updateGCodesProgram()
{
    /*const std::string data = m_gcodes.toStdString();
    gpr::gcode_program program = gpr::parse_gcode(data);
    size_t programLength = program.num_blocks();
    for(size_t i = 0; i < programLength; i++)
    {
        qDebug() << QString::fromStdString(program.get_block(i).to_string());
    }*/

}

QString GCodesManager::gcodes() const
{
    return m_gcodes;
}

void GCodesManager::setGcodes(const QString &gcodes)
{
    m_gcodes = gcodes;
}

