#include "tablemanager.h"
#include "City.h"

TableManager::TableManager()
    : parisTripSpinBoxMax{0}, purchaseTableSpinBoxes{nullptr} {}

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
void TableManager::PopulateTripTable(QTableView* table, const QStringList& cities)
{
	QStringListModel *model = new QStringListModel;
	model->setStringList(cities);

	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->verticalHeader()->setVisible(false);
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

    DeleteAllTableRows(purchaseTable);
}

    // Populates purchase table with relevant information
void TableManager::PopulatePurchaseTable(QTableWidget* purchaseTable, QVector<City>* cities)
{
    QTableWidgetItem* priceItem;

    for(int index = 0; index < cities->size(); index++)
    {
        // Create new row
        purchaseTable->insertRow(index);

        // Convert int values to QString & store into QTableWidgetItems
        priceItem = new QTableWidgetItem(QString::number(cities->at(index).GetFoodPriceAt(index)));


//        // Place items and actor string values into scenarioActorsTable
//        scenarioActorsTable->setItem(index, SC_ID, idItem);
//        scenarioActorsTable->setItem(index, SC_NAME, new QTableWidgetItem(scenarioActorList->at(index).GetName()));
//        scenarioActorsTable->setItem(index, SC_HP, hpItem);
//        scenarioActorsTable->setItem(index, SC_AC, acItem);
//        scenarioActorsTable->setItem(index, SC_DC, dcItem);
//        scenarioActorsTable->setItem(index, SC_NOTES, new QTableWidgetItem(scenarioActorList->at(index).GetNotes()));
//        scenarioActorsTable->setItem(index, SC_TYPE, new QTableWidgetItem(scenarioActorList->at(index).GetType()));

//        // Probably gonna need another loop here for the remaining food items


    } // END for
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
void TableManager::InitializeReceiptTable(QTableWidget* table, const int &cols, const QStringList &headers)
{

}

    // Populates receipt table with relevant information
void TableManager::PopulateReceiptTable(QTableWidget* table, QVector<City>* cites)
{

}

// ****************** Admin Table Table Methods ****************************
    // Intializes admin table to blank
void TableManager::InitializeAdminTable(QTableView* table)
{
	QSqlQueryModel *model = new QSqlQueryModel;

	model->setQuery("SELECT city, endCity, distance FROM Distance, Parent WHERE"
					" Parent.id = Distance.id ORDER BY Parent.id");

	if (!model->query().exec())
		qDebug() << "didn't work";

	model->setHeaderData(0, Qt::Horizontal, QObject::tr("Starting City"), Qt::DisplayRole);
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ending City"), Qt::DisplayRole);
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("Distance"), Qt::DisplayRole);

	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setModel(model);
}
    // Populates admin table with relevant information
void TableManager::PopulateAdminTable(QTableWidget* table, QVector<City>* cites)
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
