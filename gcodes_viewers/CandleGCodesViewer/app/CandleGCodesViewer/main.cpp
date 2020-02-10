#include <QApplication>
#include <widget/candle_visualizer_dialog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CandleVisualizerDialog(QStringList(), nullptr).exec();

    return a.exec();
}
