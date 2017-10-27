#include "kflopmanager.h"

KFlopManager::KFlopManager()
{
    try
    {
        int* kmotionHandle = nullptr;
        qDebug() << KM_dotnet_Interop_New(kmotionHandle, 1);
        qDebug() << KM_dotnet_Interop_Free(kmotionHandle);
    }
    catch(...)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Не удалось инициализировать KFlop").exec();
    }
}
