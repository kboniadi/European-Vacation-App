#include "tablemanager.h"
#include "City.h"

TableManager::TableManager()
    : parisTripSpinBoxMax{0}, purchaseTableSpinBoxes{nullptr}
{
    purchaseTableSpinBoxes = new QVector<QSpinBox*>;
}

TableManager* TableManager::instance()
{
	static TableManager instance;
	return &instance;
}

TableManager::~TableManager() {}

// *********************** Cities Table Methods ****************************

    // Initializes cities table to blank
void TableManager::InitializeCitiesTable(QTableWidget* table, const int &cols, const QStringList &headers)
{

}

    // Populates cities table with relevant information
void TableManager::PopulateCitiesTable(QTableWidget* table, QVector<City>* cities)
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
void TableManager::PopulateTripTable(QTableView* table, const QStringList& cities)
{
	QStringListModel *model = new QStringListModel;
	model->setStringList(cities);

	// prevent unwanted editing by user
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->verticalHeader()->setVisible(false);
	// note: QStringListModel has no header setting function
	table->horizontalHeader()->setVisible(false);
	table->setGridStyle(Qt::NoPen);
	table->setModel(model);
}

// ************** Food Purchasing Table Methods ****************************
    // Initializes purchase table to blank
void TableManager::InitializePurchaseTable(QTableWidget* purchaseTable, const int &cols, const QStringList &headers)
{
    purchaseTable->clearContents();
    purchaseTable->setColumnCount(cols);
    purchaseTable->setHorizontalHeaderLabels(headers);
    // TODO - Might be a good idea to set column widths here
    purchaseTable->setEditTriggers(QTableView::NoEditTriggers);
    purchaseTable->hideColumn(P_KEY);
    purchaseTable->verticalHeader()->hide();

    DeleteAllTableRows(purchaseTable);
}

    // Populates purchase table with relevant information
void TableManager::PopulatePurchaseTable(QTableWidget* purchaseTable, QVector<City>* cities)
{
    QTableWidgetItem* priceItem;
    QString currentName;
    QString previousName;

    // For the length of the city list
    for(int cityIndex = 0; cityIndex < cities->size(); cityIndex++)
    {
        int foodListSize = cities->at(cityIndex).GetFoodListSize();

        // Iterate through each city's food list
        for(int foodIndex = 0; foodIndex < foodListSize; foodIndex++)
        {
            // Generate food price tablewidgetitem
            priceItem = new QTableWidgetItem(QString::number(cities->at(cityIndex).GetFoodPriceAt(foodIndex)));

            // If list is not empty
            if(purchaseTable->rowCount() != 0)
            {
                // Check to see if there's a match between this row's city name and the previous row's city name
                currentName = purchaseTable->item(purchaseTable->rowCount() -1, P_KEY)->data(0).toString();
                previousName = cities->at(cityIndex).GetName();

                // Add a row to the end
                purchaseTable->insertRow(purchaseTable->rowCount());

                bool match = currentName == previousName;

                // If the row names do not match, insert the city name into the name column
                if(!match)
                {
                    // Insert city name into city name column
                    purchaseTable->setItem(purchaseTable->rowCount() - 1, P_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
                }
                else // Else, insert blank name
                {
                    purchaseTable->setItem(purchaseTable->rowCount() - 1, P_CITYNAME, new QTableWidgetItem(""));
                }
            } // END if purchase table not empty
            else // if purchase table empty
            {
                // Add new row
                purchaseTable->insertRow(purchaseTable->rowCount());

                // Insert city name into city name column
                purchaseTable->setItem(purchaseTable->rowCount() - 1, P_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
            }

            // Insert city name into key column
            purchaseTable->setItem(purchaseTable->rowCount() - 1, P_KEY, new QTableWidgetItem(cities->at(cityIndex).GetName()));
            // Add food name
            purchaseTable->setItem(purchaseTable->rowCount() - 1, P_FOOD, new QTableWidgetItem(cities->at(cityIndex).GetFoodNameAt(foodIndex)));
            // Add food price
            purchaseTable->setItem(purchaseTable->rowCount() - 1, P_PRICE, priceItem);

        } // END for iterate through food list
    } // END for iterate through city list
}

    // Inserts a dynamic spinbox in table at specific column
void TableManager::InsertSpinBoxCol(QTableWidget* table, const int min, const int max, const int col)
{
    QSpinBox *sBox;

    purchaseTableSpinBoxes->clear();

    for(int row = 0; row < table->rowCount(); row++)
    {
        sBox = new QSpinBox(table);
        sBox->setRange(min, max);
        table->setCellWidget(row, col, sBox);
        purchaseTableSpinBoxes->append(sBox);
    }
}

// ********************** Receipt Table Methods ****************************
    // Initializes receipt table to blank
void TableManager::InitializeReceiptTable(QTableWidget* receiptTable, const int &cols, const QStringList &headers)
{
    // All of the code below is dependent on receiptTable being a tablewidget. glhf
//    receiptTable->clearContents();
//    receiptTable->setColumnCount(cols);
//    receiptTable->setHorizontalHeaderLabels(headers);
//    // TODO - Might be a good idea to set column widths here
//    receiptTable->setEditTriggers(QTableView::NoEditTriggers);
//    receiptTable->hideColumn(P_KEY);
//    receiptTable->verticalHeader()->hide();

//    DeleteAllTableRows(receiptTable);
    receiptTable->clearContents();
    receiptTable->setColumnCount(cols);
    receiptTable->setHorizontalHeaderLabels(headers);
    // TODO - Might be a good idea to set column widths here
    receiptTable->setEditTriggers(QTableView::NoEditTriggers);
    receiptTable->hideColumn(P_KEY);
    receiptTable->verticalHeader()->hide();

    DeleteAllTableRows(receiptTable);
}

    // Populates receipt table with relevant information
void TableManager::PopulateReceiptTable(QTableWidget* receiptTable, QVector<City>* cities)
{
    QTableWidgetItem* priceItem;
    QString currentName;
    QString previousName;

    // For the length of the city list
    for(int cityIndex = 0; cityIndex < cities->size(); cityIndex++)
    {
        int foodListSize = cities->at(cityIndex).GetFoodListSize();

        // Iterate through each city's food list
        for(int foodIndex = 0; foodIndex < foodListSize; foodIndex++)
        {
            // Generate food price tablewidgetitem
            priceItem = new QTableWidgetItem(QString::number(cities->at(cityIndex).GetFoodPriceAt(foodIndex)));

            // If list is not empty
            if(receiptTable->rowCount() != 0)
            {
                // Check to see if there's a match between this row's city name and the previous row's city name
                currentName = receiptTable->item(receiptTable->rowCount() -1, P_KEY)->data(0).toString();
                previousName = cities->at(cityIndex).GetName();

                // Add a row to the end
                receiptTable->insertRow(receiptTable->rowCount());

                bool match = currentName == previousName;

                // If the row names do not match, insert the city name into the name column
                if(!match)
                {
                    // Insert city name into city name column
                    receiptTable->setItem(receiptTable->rowCount() - 1, P_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
                }
                else // Else, insert blank name
                {
                    receiptTable->setItem(receiptTable->rowCount() - 1, P_CITYNAME, new QTableWidgetItem(""));
                }
            } // END if purchase table not empty
            else // if purchase table empty
            {
                // Add new row
                receiptTable->insertRow(receiptTable->rowCount());

                // Insert city name into city name column
                receiptTable->setItem(receiptTable->rowCount() - 1, P_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
            }

            // Insert city name into key column
            receiptTable->setItem(receiptTable->rowCount() - 1, P_KEY, new QTableWidgetItem(cities->at(cityIndex).GetName()));
            // Add food name
            receiptTable->setItem(receiptTable->rowCount() - 1, P_FOOD, new QTableWidgetItem(cities->at(cityIndex).GetFoodNameAt(foodIndex)));
            // Add food price
            receiptTable->setItem(receiptTable->rowCount() - 1, P_PRICE, priceItem);

        } // END for iterate through food list
    } // END for iterate through city list

}

// ****************** Admin Table Table Methods ****************************
    // Intializes admin table to blank
void TableManager::InitializeAdminTable(QTableView* table)
{
	QSqlQueryModel *model = new QSqlQueryModel;

	model->setQuery("SELECT cityNames, endCity, distances FROM distance, cities WHERE"
					" cities.id = distance.id ORDER BY cities.id");

	if (!model->query().exec())
		qDebug() << "TableManager::InitializeAdminTable() : query failed";

	model->setHeaderData(0, Qt::Horizontal, QObject::tr("Starting City"), Qt::DisplayRole);
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ending City"), Qt::DisplayRole);
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("Distance"), Qt::DisplayRole);

	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setModel(model);
}
    // Populates admin table with relevant information
void TableManager::PopulateAdminTable(QTableWidget* table, QVector<City>* cities)
{

}

// *************************************************************************************
// Deletes entire contents of passed in table
// *************************************************************************************
void TableManager::DeleteAllTableRows(QTableWidget *table)
{
    const int ROW_COUNT = table->rowCount();

    for(int index = 0; index < ROW_COUNT; index++)
    {
        table->removeRow(0);
    }
}

    // TODO copy/paste contents of one table to another
// void CopyXTableToOther(QTableWidget* origin, QTableWidget* destination);
