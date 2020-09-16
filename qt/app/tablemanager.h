#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H


class TableManager
{
public:
    static TableManager* instance();

private:
    TableManager();
    ~TableManager();
};

#endif // TABLEMANAGER_H
