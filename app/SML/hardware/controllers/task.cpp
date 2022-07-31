#include "task.h"

Task::Task(QString gcode) :
    m_gcode(gpr::parse_gcode(gcode.toStdString()))
{
    this->removeEmptyBlocks();
}

QString Task::serialize()
{
    QStringList result = {};
    for(int i = 0; i < m_gcode.num_blocks(); i++)
    {
        result.append(this->block(i));
    }

    return result.join("\n");
}

int Task::blocksCount() const
{
    return m_gcode.num_blocks();
}

QString Task::block(int index)
{
    QString serializedBlock = QString::fromStdString(m_gcode.get_block(index).to_string());;
    serializedBlock = serializedBlock.remove(serializedBlock.length() - 1, 1);
    return serializedBlock;
}

QString Task::blockId(int index)
{
    gpr::block block = m_gcode.get_block(index);
    if(!this->chunkExists(block, GCODE_ID_KEY)) return "";

    gpr::chunk chunk = this->getChunk(block, GCODE_ID_KEY);

    return QString(chunk.get_word()) + Task::strAddr(chunk.get_address());
}

QMap<QString, QVariant> Task::blockAxesArgs(int index)
{
    QMap<QString, QVariant> result = {};

    gpr::block block = m_gcode.get_block(index);
    for(int j = 0; j < block.size(); j++)
    {
        gpr::chunk chunk = block.get_chunk(j);
        QString word = QString(chunk.get_word());
        QString addr = Task::strAddr(chunk.get_address());

        if(!GCODE_AXIS_KEYS.contains(word.toLower())) continue;
        result.insert(word, addr);
    }

    return result;
}

QString Task::blockFeedrate(int index)
{
    gpr::block block = m_gcode.get_block(index);
    if(!this->chunkExists(block, GCODE_FEEDRATE_KEY)) return "";

    gpr::chunk chunk = this->getChunk(block, GCODE_FEEDRATE_KEY);

    return QString(chunk.get_word()) + Task::strAddr(chunk.get_address());
}

QString Task::blockMCode(int index)
{
    gpr::block block = m_gcode.get_block(index);
    if(!this->chunkExists(block, MCODE_KEY)) return "";

    gpr::chunk chunk = this->getChunk(block, MCODE_KEY);

    return QString(chunk.get_word()) + Task::strAddr(chunk.get_address());
}

void Task::removeEmptyBlocks()
{
    QStringList decoratedProgram = {};
    for(int i = 0; i < m_gcode.num_blocks(); i++)
    {
        gpr::block block = m_gcode.get_block(i);
        QStringList decoratedBlock = {};
        for(int j = 0; j < block.size(); j++)
        {
            gpr::chunk chunk = block.get_chunk(j);
            if(chunk.tp() != gpr::chunk_type::CHUNK_TYPE_WORD_ADDRESS) continue;

            QString word = QString(chunk.get_word());
            QString addr = Task::strAddr(chunk.get_address());
            decoratedBlock.append(word + addr);
        }

        if(decoratedBlock.isEmpty()) continue;
        decoratedProgram.append(decoratedBlock.join(" "));
    }

    m_gcode = gpr::parse_gcode(decoratedProgram.join("\n").toStdString());
}

QString Task::strAddr(gpr::addr addr)
{
    QString result = "";
    switch(addr.tp())
    {
    case gpr::address_type::ADDRESS_TYPE_DOUBLE:
        result = QString::number(addr.double_value());
        break;
    case gpr::address_type::ADDRESS_TYPE_INTEGER:
        result = QString::number(addr.int_value());
        break;
    }
    return result;
}

bool Task::chunkExists(gpr::block block, QString word)
{
    bool result = false;
    for(int j = 0; j < block.size(); j++)
    {
        gpr::chunk chunk = block.get_chunk(j);
        QString chunkWord = QString(chunk.get_word());
        if(chunkWord.toLower() == word)
        {
            result = true;
            break;
        }
    }
    return result;
}

gpr::chunk Task::getChunk(gpr::block block, QString word)
{
    for(int j = 0; j < block.size(); j++)
    {
        gpr::chunk chunk = block.get_chunk(j);
        QString chunkWord = QString(chunk.get_word());
        if(chunkWord.toLower() == word) return chunk;
    }

    throw std::invalid_argument("chunk " + word.toStdString() +
                                "does not exists in block" + block.to_string());
}
