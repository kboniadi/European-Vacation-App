#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QDebug>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableView>
#include <QVector>
#include <QHeaderView>
#include <QStringListModel>
#include "dbmanager.h"

class City;

class TableManager
{
public:
    static TableManager* instance();
    TableManager(const TableManager&) = delete;
    TableManager& operator=(const TableManager&) = delete;

    // ************************ Cities Table Attributes ************************

        // Number of columns in cities table
    const int CITIES_TABLE_COL_COUNT = 2;
        // Positions of cities table columns by name
    enum CitiesTableColPositions { C_CITYNAME, C_DISTANCE };
        // Names of cities table column headers
    QStringList citiesTableColNames	= { "City Name", "Distance from Berlin (km)" };

    // ************************** Food Table Attributes ************************
        // Number of columns in food table
    const int FOOD_TABLE_COL_COUNT = 3;
        // Positions of food table positions name
    enum FoodTableColPositions { F_CITYNAME, F_FOODNAME, F_PRICE };
        // Names of food table column headers
    QStringList foodTableColNames = { "City Name", "Food Available", "Price" };

    // ***************** Trip Planning Table Attributes ************************

        // Number of columns in trip planning table. Used for all trips
    const int TRIP_TABLE_COL_COUNT = 2;
        // Positions of trip planning table positions name
    enum TripTableColPositions { T_CITYNAME, T_DISTANCE };
        // Names of trip planning table column headers
    QStringList tripTableColNames = { "City Name", "Distance" };
        // List of cities for custom trip. Needs to be set on program start and each time cities are imported
    QStringList CustomTripComboBoxLabels;
        // Minimum value for paris trip spinbox.
    const int PARIS_TRIP_SPINBOX_MIN = 1;
        // Maximum value for paris trip spinbox. Needs to be set on program start and each time cities are imported
    int parisTripSpinBoxMax;

    // **************** Food Purchasing Table Attributes ***********************

        // Number of columns in food-purchasing table
    const int PURCHASE_TABLE_COL_COUNT = 5;
        // Positions of food purchase table columns by name
    enum PurchaseTableColPositions { P_KEY, P_CITYNAME, P_FOOD, P_PRICE, P_QTY };
        // Names of purchase table column headers
    QStringList purchaseTableColNames = {"KEY", "City Name", "Food Available", "Price", "Quantity Desired" };
        // Minimum value for food purchase spinbox
    const int PURCHASE_SPINBOX_MIN = 0;
        // Maximum value for food purchase spinbox
    const int PURCHASE_SPINBOX_MAX = 20;
        // Vector of pointers to spinbox pointers. Needed for dynamically creating spinboxes on purchase page
    QVector<QSpinBox*>* purchaseTableSpinBoxes;

    // ************************ Receipt Table Attributes ***********************

        // Number of columns in receipt table
    const int RECEIPT_TABLE_COL_COUNT = 5;
        // Positions of receipt table columns by name
    enum ReceiptTableColPositions { R_KEY, R_CITYNAME, R_FOOD, R_PRICE, R_QTY, R_TOTAL };
        // Names of receipt table column headers
    QStringList receiptTableColNames = {"KEY", "City Name", "Food Available", "Price", "Quantity Purchased", "Total Charges" };

    // ************************* Admin Table Attributes ************************

        // Number of columns in table
	const int ADMIN_TABLE_COL_COUNT = 4;
        // positions of admin table columns by name
	enum AdminTableColPositions	{ A_Key, A_CITYNAME, A_FOOD, A_PRICE };
        // Names of admin table column headers
	QStringList adminTableColNames = {"KEY", "City Name", "Food Available", "Price" };

                        /***********
                         * Methods *
                         ***********/

    // *********************** Cities Table Methods ****************************

        // Initializes cities table to blank
    void InitializeCitiesTable(QTableWidget* citiesTable, const int &cityTablecols, const QStringList &cityTableHeaders);
        // Populates cities table with relevant information
    void PopulateCitiesTable(QTableWidget* cityTable, QStringList *cityNames, QVector<int> *distancesFromBerlin);

    // ************************* Food Table Methods ****************************

        // Initializes foods table to blank
    void InitializeFoodTable(QTableWidget* table, const int &cols, const QStringList &headers);
        // Populates food table with relevant information
    void PopulateFoodTable(QTableWidget* table, QVector<City>* cites);

    // **************** Trip Planning Table Methods ****************************

        // Initializes trip planning table to blank. Used for all types of trips
    void InitializeTripTable(QTableWidget* table, const int &cols, const QStringList &headers);
        // Populates trip planning table with relevant information
    void PopulateTripTable(QTableView* table, const QStringList& cities);

    // ************** Food Purchasing Table Methods ****************************
        // Initializes purchase table to blank
    void InitializePurchaseTable(QTableWidget* table, const int &cols, const QStringList &headers);
        // Populates purchase table with relevant information
    void PopulatePurchaseTable(QTableWidget* purchaseTable, QVector<City>* cities);
        // Inserts a dynamic spinbox in table at specific column
    void InsertSpinBoxCol(QTableWidget* table, const int min, const int max, const int col);

    // ********************** Receipt Table Methods ****************************
        // Initializes receipt table to blank
    void InitializeReceiptTable(QTableWidget* receiptTable, const int &cols, const QStringList &headers);
        // Populates receipt table with relevant information
    void PopulateReceiptTable(QTableWidget* receiptTable, QVector<City>* cites);

    // ****************** Admin Table Table Methods ****************************
		// Intializes admin table using model for city distance list
	void InitializeAdminTable(QTableView* table);
		// Initilaizes admin food table to blank
	void InitializeAdminTable(QTableWidget* adminTable, const int &cols, const QStringList &headers);
		// Populates admin table with relevant information
    void PopulateAdminTable(QTableWidget* table, QVector<City>* cities);

    void DeleteAllTableRows(QTableWidget *table);
        // TODO copy/paste contents of one table to another
    // void CopyXTableToOther(QTableWidget* origin, QTableWidget* destination);

private:
	TableManager();
	~TableManager() = default;
};

#endif // TABLEMANAGER_H
