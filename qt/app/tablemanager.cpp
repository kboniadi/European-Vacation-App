#include "tablemanager.h"

TableManager::TableManager()
{

}

TableManager* TableManager::instance()
{
    static TableManager instance;
    return &instance;
}
