#include "tablemanager.h"

TableManager::TableManager()
{

}

TableManager* TableManager::instance()
{
    static TableManager instance;
    return &instance;
}

// *********************** Cities Table Methods ****************************

    // Initializes cities table to blank
void TableManager::InitializeCitiesTable(QTableWidget* table, const int &cols, const QStringList &headers)
{

}

    // Populates cities table with relevant information
void TableManager::PopulateCitiesTable(QTableWidget* table, QVector<City>* cites)
{

}

// ************************* Food Table Methods ****************************

    // Initializes foods table to blank
void TableManager::InitializeFoodTable(QTableWidget* table, const int &cols, const QStringList &headers)
{

}

    // Populates food table with relevant information
void TableManager::PopulateFoodTable(QTableWidget* table, QVector<City>* cites)
{

}

// **************** Trip Planning Table Methods ****************************

    // Initializes trip planning table to blank. Used for all types of trips
void TableManager::InitializeTripTable(QTableWidget* table, const int &cols, const QStringList &headers)
{

}

    // Populates trip planning table with relevant information
void TableManager::PopulateTripTable(QTableWidget* table, QVector<City>* cites)
{

}

// ************** Food Purchasing Table Methods ****************************
    // Initializes purchase table to blank
void TableManager::InitializePurchaseTable(QTableWidget* table, const int &cols, const QStringList &headers)
{

}

    // Populates purchase table with relevant information
void TableManager::PopulatePurchaseTable(QTableWidget* table, QVector<City>* cites)
{

}

    // Inserts a dynamic spinbox in table at specific column
void TableManager::InsertSpinBoxCol(QTableWidget* table, const int min, const int max, const int col)
{

}

// ********************** Receipt Table Methods ****************************
    // Initializes receipt table to blank
void TableManager::InitializeReceiptTable(QTableWidget* table, const int &cols, const QStringList &headers)
{

}

    // Populates receipt table with relevant information
void TableManager::PopulateReceiptTable(QTableWidget* table, QVector<City>* cites)
{

}

// ****************** Admin Table Table Methods ****************************
    // Intializes admin table to blank
void TableManager::InitializeAdminTable(QTableWidget* table, const int &cols, const QStringList &headers)
{

}
    // Populates admin table with relevant information
void TableManager::PopulateAdminTable(QTableWidget* table, QVector<City>* cites)
{

}

    // TODO copy/paste contents of one table to another
// void CopyXTableToOther(QTableWidget* origin, QTableWidget* destination);
