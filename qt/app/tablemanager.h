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

/*!
 * @class TableManager
 * @brief The TableManager holds attributes for all tables, initializes them,
 * and populates their contents. For use in all program functionality
 */
class TableManager
{
public:
    /*!
     * @brief Creates one instance of the Table Manager
     * @return Pointer the the instance of the TableManager
     */
    static TableManager* instance();

    /*!
     * @brief Deleted copy constructor
     */
    TableManager(const TableManager&) = delete;

    /*!
     * @brief Deleted copy assignment
     */
    TableManager& operator=(const TableManager&) = delete;

    // ************************ Cities Table Attributes ************************

    /// Number of columns in cities table
    const int CITIES_TABLE_COL_COUNT = 2;
    /// Positions of cities table columns by name
    enum CitiesTableColPositions { C_CITYNAME, C_DISTANCE };
    /// Names of cities table column headers
    QStringList citiesTableColNames	= { "City Name", "Distance from Berlin (km)" };

    // ************************** Food Table Attributes ************************
    /// Number of columns in food table
    const int FOOD_TABLE_COL_COUNT = 4;
    /// Positions of food table positions name
    enum FoodTableColPositions { F_KEY, F_CITYNAME, F_FOODNAME, F_PRICE };
    /// Names of food table column headers
    QStringList foodTableColNames = { "KEY", "City Name", "Food Available", "Price" };

    // ***************** Trip Planning Table Attributes ************************

    /// Number of columns in trip planning table. Used for all trips
    const int TRIP_TABLE_COL_COUNT = 2;
    /// Positions of trip planning table positions name
    enum TripTableColPositions { T_CITYNAME, T_DISTANCE };
    /// Names of trip planning table column headers
    QStringList tripTableColNames = { "City Name", "Distance" };
    /// List of cities for custom trip. Needs to be set on program start and each time cities are imported
    QStringList CustomTripComboBoxLabels;
    /// Minimum value for paris trip spinbox.
    const int PARIS_TRIP_SPINBOX_MIN = 1;
    /// Maximum value for paris trip spinbox. Needs to be set on program start and each time cities are imported
    int parisTripSpinBoxMax;

    // **************** Food Purchasing Table Attributes ***********************

    /// Number of columns in food-purchasing table
    const int PURCHASE_TABLE_COL_COUNT = 5;
    /// Positions of food purchase table columns by name
    enum PurchaseTableColPositions { P_KEY, P_CITYNAME, P_FOOD, P_PRICE, P_QTY };
    /// Names of purchase table column headers
    QStringList purchaseTableColNames = {"KEY", "City Name", "Food Available", "Price", "Quantity Desired" };
    /// Minimum value for food purchase spinbox
    const int PURCHASE_SPINBOX_MIN = 0;
    /// Maximum value for food purchase spinbox
    const int PURCHASE_SPINBOX_MAX = 20;
    /// Vector of pointers to spinbox pointers. Needed for dynamically creating spinboxes on purchase page
    QVector<QSpinBox*>* purchaseTableSpinBoxes;

    // ************************ Receipt Table Attributes ***********************

    /// Number of columns in receipt table
    const int RECEIPT_TABLE_COL_COUNT = 6;
    /// Positions of receipt table columns by name
    enum ReceiptTableColPositions { R_KEY, R_CITYNAME, R_FOOD, R_PRICE, R_QTY, R_TOTAL };
    /// Names of receipt table column headers
    QStringList receiptTableColNames = {"KEY", "City Name", "Food Available", "Price", "Quantity Purchased", "Total Charges" };

    // ************************* Admin Table Attributes ************************

    /// Number of columns in table
	const int ADMIN_TABLE_COL_COUNT = 4;
    /// positions of admin table columns by name
	enum AdminTableColPositions	{ A_Key, A_CITYNAME, A_FOOD, A_PRICE };
    /// Names of admin table column headers
	QStringList adminTableColNames = {"KEY", "City Name", "Food Available", "Price" };

                        /***********
                         * Methods *
                         ***********/

    // *********************** Cities Table Methods ****************************

    /*!
     * @brief Initializes cities table to blank
     * @param citiesTable; Table to be initialized
     * @param cityTablecols; Number of columns in table
     * @param cityTableHeaders; Table's column header names
     */
    void InitializeCitiesTable(QTableWidget* citiesTable, const int &cityTablecols, const QStringList &cityTableHeaders);

    /*!
     * @brief Populates cities table with relevant information
     * @param cityTable; Table to be initialized
     * @param cityNames; Number of columns in table
	 * @param distancesFromBerlin; List of distances of each city to Berlin
     */
    void PopulateCitiesTable(QTableWidget* cityTable, QStringList *cityNames, QVector<int> *distancesFromBerlin);

    // ************************* Food Table Methods ****************************

    /*!
     * @brief Initializes foods table to blank
     * @param table; Table to be initialized
     * @param cols; Number of columns in table
     * @param headers; Table's column header names
     */
    void InitializeFoodTable(QTableWidget* table, const int &cols, const QStringList &headers);

    /*!
     * @brief Populates foods table with relevant information
     * @param foodTable; Table to be initialized
     * @param cities; City objects with which to populate table
     */
    void PopulateFoodTable(QTableWidget* foodTable, QVector<City> *cities);

    // **************** Trip Planning Table Methods ****************************

    /*!
     * @brief Populates trip planning table with relevant information
     * @param table; Table to be initialized
     * @param cities; City objects with which to populate table
     */
    void PopulateTripTable(QTableView* table, const QStringList& cities);

    // ************** Food Purchasing Table Methods ****************************

    /*!
     * @brief Initializes purchases table to blank
     * @param table; Table to be initialized
     * @param cols; Number of columns in table
     * @param headers; Table's column header names
     */
    void InitializePurchaseTable(QTableWidget* table, const int &cols, const QStringList &headers);

    /*!
     * @brief Populates purchase table with relevant information
     * @param purchaseTable; Table to be initialized
     * @param cities; City objects with which to populate table
     */
    void PopulatePurchaseTable(QTableWidget* purchaseTable, QVector<City>* cities);

    /*!
     * @brief Inserts a dynamic spinbox in table at specific column
     * @param table; Table in which to insert spinbox column
     * @param min; Minimum value allowed in spinbox
     * @param max; Maximum value allowed in spinbox
     * @param col; Column location to insert spinbox column
     */
    void InsertSpinBoxCol(QTableWidget* table, const int min, const int max, const int col);

    // ********************** Receipt Table Methods ****************************

    /*!
     * @brief Initializes receipt table to blank
     * @param receiptTable; Table to be initialized
     * @param cols; Number of columns in table
     * @param headers; Table's column header names
     */
    void InitializeReceiptTable(QTableWidget* receiptTable, const int &cols, const QStringList &headers);

    /*!
     * @brief Populates receipt table with relevant information
     * @param receiptTable; Table to be initialized
     * @param cities; City objects with which to populate table
     */
    void PopulateReceiptTable(QTableWidget* receiptTable, QVector<City>* cities);

    // ****************** Admin Table Table Methods ****************************
    /*!
     * @brief Initializes admin table using model for city distance list
     * @param table; Table to be initialized
     */
	void InitializeAdminTable(QTableView* table);

    /*!
     * @brief Initializes admin table manually
     * @param adminTable; Table to be initialized
     * @param cols; Number of columns in table
     * @param headers; Table's column header names
     */
	void InitializeAdminTable(QTableWidget* adminTable, const int &cols, const QStringList &headers);

    /*!
     * @brief Populates admin table with relevant information
	 * @param table; Table to be initialized
     * @param cities; City objects with which to populate table
     */
    void PopulateAdminTable(QTableWidget* table, QVector<City>* cities);

    /*!
     * @brief Deletes all rows in table
     * @param table; Table to be deleted
     */
    void DeleteAllTableRows(QTableWidget *table);

private:
    /*!
     * @brief Default TableManager object constructor
     */
	TableManager();

    /*!
     * @brief Destructor
     */
	~TableManager() = default;
};

#endif // TABLEMANAGER_H
