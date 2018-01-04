#include "gcodesmanager.h"

GCodesManager::GCodesManager()
{
    updateGCodesProgram("");
}

GCodesManager::~GCodesManager()
{
    //delete m_gcodes;
}

void GCodesManager::updateGCodesProgram(const std::string &data)
{
    gpr::gcode_program m_gcodes = gpr::parse_gcode(data);
    qDebug() << m_gcodes.num_blocks();
    //qDebug() << QString::fromStdString(m_gcodes.get_block(7).to_string());
}

/*gpr::gcode_program GCodesManager::gcodes() const
{
    return m_gcodes;
}*/
