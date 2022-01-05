#include "configmanager.h"

///
/// \brief
/// \param parent
///
configManager::configManager(QObject *parent) : QObject(parent)
{

}

//初始化设置函数
void configManager::writer()
{
    QSettings settings(QCoreApplication::organizationName() ,QCoreApplication::applicationName());

}

//基础数据预读取函数,由于其特殊性，不暴露且禁止调用
void configManager::reader()
{

}
