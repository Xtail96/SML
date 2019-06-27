#include "prepare_execution_queue_interactor.h"

PrepareExecutionQueueInteractor::PrepareExecutionQueueInteractor()
{

}

QQueue<QByteArray> PrepareExecutionQueueInteractor::execute(QStringList gcodesProgram)
{
    QQueue<QByteArray> result = {};

    const std::string data = gcodesProgram.join("\n").toStdString();
    gpr::gcode_program program = gpr::parse_gcode(data);
    int programLength = program.num_blocks();
    for(int i = 0; i < programLength; i++)
    {
        gpr::block block = program.get_block(i);

        QtJson::JsonObject package = {};
        package.insert("frame", QString::fromStdString(block.to_string()));
        QtJson::JsonObject detailedInfo = {};

        int blockSize = block.size();
        if(blockSize <= 0) continue;
            //throw InvalidArgumentException("gcodes block size <= 0");

        QPair<QString, double> myFirstChunk = PrepareExecutionQueueInteractor::chunkToKeyValuePair(block.get_chunk(0));
        if(((myFirstChunk.first.toLower() == "m") && (qFuzzyCompare(myFirstChunk.second, double(3)))) ||
          ((myFirstChunk.first.toLower() == "m") && (qFuzzyCompare(myFirstChunk.second, double(4)))) ||
          ((myFirstChunk.first.toLower() == "m") && (qFuzzyCompare(myFirstChunk.second, double(5)))))
        {
            package.insert("target", "U1");
        }
        else
        {
            package.insert("target", "U2");
        }

        QtJson::JsonArray axisesArguments = {};
        for(int j = 1; j < block.size(); j++)
        {
            QPair<QString, double> myChunk = PrepareExecutionQueueInteractor::chunkToKeyValuePair(block.get_chunk(j));
            QString key = myChunk.first;
            double value = myChunk.second;
            QString serializedChunk = key + QString::number(value);
            if(key.toLower() == "f")
            {
                detailedInfo.insert("feedrate", serializedChunk);
                continue;
            }

            if(key.toLower() == "m")
            {
                detailedInfo.insert("support_m_code_id", serializedChunk);
                continue;
            }

            if(key.toLower() == "e")
            {
                continue;
            }

            axisesArguments.append(serializedChunk);
        }
        detailedInfo.insert("frame_id", myFirstChunk.first + QString::number(myFirstChunk.second));
        detailedInfo.insert("axises_count", axisesArguments.size());
        detailedInfo.insert("axises_arguments", axisesArguments);
        package.insert("detailed_info", detailedInfo);
        result.enqueue(QtJson::serialize(package));
    }
    return result;
}

QPair<QString, double> PrepareExecutionQueueInteractor::chunkToKeyValuePair(gpr::chunk chunk)
{
    if(chunk.tp() == gpr::CHUNK_TYPE_WORD_ADDRESS)
    {
        QString key = QString(chunk.get_word());
        gpr::addr addr = chunk.get_address();
        double value = double(-INT_MAX);
        switch (addr.tp())
        {
            case gpr::ADDRESS_TYPE_DOUBLE:
            {
                value = addr.double_value();
                break;
            }
            case gpr::ADDRESS_TYPE_INTEGER:
            {
                value = addr.int_value();
                break;
            }
        }

        // value == double(-INT_MAX)
        if(qFuzzyCompare(value, double(-INT_MAX)))
            throw InvalidArgumentException("unknown gcode " + key + " " + QString::number(value));

        // если пара соответсвует M3, M4, M5 - включение/выключение шпинделя
        QPair<QString, double> myChunk(key, value);
        return  myChunk;
    }
    else
    {
        throw InvalidArgumentException("unknown chunk type");
    }
}
