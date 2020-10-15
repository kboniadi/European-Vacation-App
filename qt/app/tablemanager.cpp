#include "tablemanager.h"
#include "City.h"
#include <QHeaderView>

// Constructor
TableManager::TableManager()
    : parisTripSpinBoxMax{0}, purchaseTableSpinBoxes{nullptr}
{
    purchaseTableSpinBoxes = new QVector<QSpinBox*>;
}

// Reference to instance
TableManager* TableManager::instance()
{
	static TableManager instance;
	return &instance;
}

// *********************** Cities Table Methods ****************************

// Initializes cities table to blank
void TableManager::InitializeCitiesTable(QTableWidget* citiesTable, const int &citiesCols, const QStringList &citiesHeaders)
{
    citiesTable->clearContents();
    citiesTable->setColumnCount(citiesCols);
    citiesTable->setHorizontalHeaderLabels(citiesHeaders);
	citiesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    citiesTable->setEditTriggers(QTableView::NoEditTriggers);
    citiesTable->verticalHeader()->hide();

    DeleteAllTableRows(citiesTable);
}

// Populates cities table with relevant information
void TableManager::PopulateCitiesTable(QTableWidget* cityTable, QStringList* cityNames, QVector<int>* distancesFromBerlin)
{
    // Create distance item
    QTableWidgetItem* distanceItem;

    // Loop to insert values into table
    for(int index = 0; index < cityNames->size(); index++)
    {
        // Create row
        cityTable->insertRow(cityTable->rowCount());

        // Populate cityname column
        cityTable->setItem(cityTable->rowCount() -1, C_CITYNAME, new QTableWidgetItem(cityNames->at(index)));

        // Create distance item
        distanceItem = new QTableWidgetItem(QString::number(distancesFromBerlin->at(index)));

        // Populate distance column
        cityTable->setItem(cityTable->rowCount() - 1, C_DISTANCE, distanceItem);
    }
}

// ************************* Food Table Methods ****************************

// Initializes foods table to blank
void TableManager::InitializeFoodTable(QTableWidget* foodTable, const int &foodCols, const QStringList &foodHeaders)
{
    foodTable->clearContents();
    foodTable->setColumnCount(foodCols);
    foodTable->setHorizontalHeaderLabels(foodHeaders);
	foodTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    foodTable->setEditTriggers(QTableView::NoEditTriggers);
    foodTable->hideColumn(F_KEY);
    foodTable->verticalHeader()->hide();

    DeleteAllTableRows(foodTable);
}

// Populates food table with relevant information
void TableManager::PopulateFoodTable(QTableWidget* foodTable, QVector<City>* cities)
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
			priceItem = new QTableWidgetItem(QString::number(cities->at(cityIndex).GetFoodPriceAt(foodIndex), 'f', 2));

            // If list is not empty
            if(foodTable->rowCount() != 0)
            {
                // Check to see if there's a match between this row's city name and the previous row's city name
                currentName = foodTable->item(foodTable->rowCount() -1, F_KEY)->data(0).toString();
                previousName = cities->at(cityIndex).GetName();

                // Add a row to the end
                foodTable->insertRow(foodTable->rowCount());

                bool match = currentName == previousName;

                // If the row names do not match, insert the city name into the name column
                if(!match)
                {
                    // Insert city name into city name column
                    foodTable->setItem(foodTable->rowCount() - 1, F_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
                }
                else // Else, insert blank name
                {
                    foodTable->setItem(foodTable->rowCount() - 1, F_CITYNAME, new QTableWidgetItem(""));
                }
            } // END if food table not empty
            else // if food table empty
            {
                // Add new row
                foodTable->insertRow(foodTable->rowCount());

                // Insert city name into city name column
                foodTable->setItem(foodTable->rowCount() - 1, F_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
            }

            // Insert city name into key column
            foodTable->setItem(foodTable->rowCount() - 1, F_KEY, new QTableWidgetItem(cities->at(cityIndex).GetName()));
            // Add food name
            foodTable->setItem(foodTable->rowCount() - 1, F_FOODNAME, new QTableWidgetItem(cities->at(cityIndex).GetFoodNameAt(foodIndex)));
            // Add food price
            foodTable->setItem(foodTable->rowCount() - 1, F_PRICE, priceItem);

        } // END for iterate through food list
    } // END for iterate through city list for iterate through city list
}

// **************** Trip Planning Table Methods ****************************

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
	purchaseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
			priceItem = new QTableWidgetItem(QString::number(cities->at(cityIndex).GetFoodPriceAt(foodIndex), 'f', 2));

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
    receiptTable->clearContents();
    receiptTable->setColumnCount(cols);
    receiptTable->setHorizontalHeaderLabels(headers);
	receiptTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    receiptTable->setEditTriggers(QTableView::NoEditTriggers);
    receiptTable->hideColumn(P_KEY);
    receiptTable->verticalHeader()->hide();

    DeleteAllTableRows(receiptTable);
}

// Populates receipt table with relevant information
void TableManager::PopulateReceiptTable(QTableWidget* receiptTable, QVector<City>* cities)
{
    QTableWidgetItem* priceItem;
    QTableWidgetItem* qtyItem;
    QTableWidgetItem* totalItem;
    QString currentName;
    QString previousName;

    for (int i = 0; i < cities->size(); i++)
    {
        // Removes food from list if qty is 0
        int foodListSize = cities->at(i).GetFoodListSize();
        for (int j = 0; j < foodListSize; j++)
        {
            qtyItem = new QTableWidgetItem(QString::number(cities->at(i).GetFoodQtyAt(j)));
            if (qtyItem->text().toDouble() == 0)
            {
                cities->operator[](i).RemoveFoodAt(j);
                j--;
                foodListSize--;
            }
        }
    }

    // For the length of the city list
    for(int cityIndex = 0; cityIndex < cities->size(); cityIndex++)
    {
        int foodListSize = cities->at(cityIndex).GetFoodListSize();

        // Iterate through each city's food list
        for(int foodIndex = 0; foodIndex < foodListSize; foodIndex++)
        {
                // Generate food quantity tablewidgetitem
                qtyItem = new QTableWidgetItem(QString::number(cities->at(cityIndex).GetFoodQtyAt(foodIndex)));

                // Generate food price tablewidgetitem
				priceItem = new QTableWidgetItem(QString::number(cities->at(cityIndex).GetFoodPriceAt(foodIndex), 'f', 2));

                // Generate food total tablewidgetitem
				totalItem = new QTableWidgetItem(QString::number((cities->at(cityIndex).GetFoodPriceAt(foodIndex)) * (cities->at(cityIndex).GetFoodQtyAt(foodIndex)), 'f', 2));

                // If list is not empty
                if(receiptTable->rowCount() != 0)
                {
                    // Check to see if there's a match between this row's city name and the previous row's city name
                    currentName = receiptTable->item(receiptTable->rowCount() -1, R_KEY)->data(0).toString();
                    previousName = cities->at(cityIndex).GetName();

                    // Add a row to the end
                    receiptTable->insertRow(receiptTable->rowCount());

                    bool match = currentName == previousName;

                    // If the row names do not match, insert the city name into the name column
                    if(!match)
                    {
                        // Insert city name into city name column
                        receiptTable->setItem(receiptTable->rowCount() - 1, R_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
                    }
                    else // Else, insert blank name
                    {
                        receiptTable->setItem(receiptTable->rowCount() - 1, R_CITYNAME, new QTableWidgetItem(""));
                    }
                } // END if purchase table not empty
                else // if purchase table empty
                {
                    // Add new row
                    receiptTable->insertRow(receiptTable->rowCount());

                    // Insert city name into city name column
                    receiptTable->setItem(receiptTable->rowCount() - 1, R_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
                }

                // Insert city name into key column
                receiptTable->setItem(receiptTable->rowCount() - 1, R_KEY, new QTableWidgetItem(cities->at(cityIndex).GetName()));
                // Add food name
                receiptTable->setItem(receiptTable->rowCount() - 1, R_FOOD, new QTableWidgetItem(cities->at(cityIndex).GetFoodNameAt(foodIndex)));
                // Add food price
                receiptTable->setItem(receiptTable->rowCount() - 1, R_PRICE, priceItem);
                // Add food quantity
                receiptTable->setItem(receiptTable->rowCount() - 1, R_QTY, qtyItem);

                receiptTable->setItem(receiptTable->rowCount() - 1, R_TOTAL, totalItem);

        } // END for iterate through food list
    } // END for iterate through city list
}

// ****************** Admin Table Table Methods ****************************

// Intializes admin table using model for city distance list
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

// Initializes admin table to blank
void TableManager::InitializeAdminTable(QTableWidget* adminTable, const int &cols, const QStringList &headers)
{
	adminTable->clearContents();
	adminTable->setColumnCount(cols);
	adminTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	adminTable->setHorizontalHeaderLabels(headers);
	// TODO - Might be a good idea to set column widths here
	adminTable->setEditTriggers(QTableView::NoEditTriggers);
	adminTable->hideColumn(P_KEY);
	adminTable->verticalHeader()->hide();

	DeleteAllTableRows(adminTable);
}
// Populates admin table with relevant information
void TableManager::PopulateAdminTable(QTableWidget* table, QVector<City>* cities)
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
			priceItem = new QTableWidgetItem(QString::number(cities->at(cityIndex).GetFoodPriceAt(foodIndex), 'f', 2));

			// If list is not empty
			if(table->rowCount() != 0)
			{
				// Check to see if there's a match between this row's city name and the previous row's city name
				currentName = table->item(table->rowCount() -1, P_KEY)->data(0).toString();
				previousName = cities->at(cityIndex).GetName();

				// Add a row to the end
				table->insertRow(table->rowCount());

				bool match = currentName == previousName;

				// If the row names do not match, insert the city name into the name column
				if(!match)
				{
					// Insert city name into city name column
					table->setItem(table->rowCount() - 1, P_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
				}
				else // Else, insert blank name
				{
					table->setItem(table->rowCount() - 1, P_CITYNAME, new QTableWidgetItem(""));
				}
			} // END if purchase table not empty
			else // if purchase table empty
			{
				// Add new row
				table->insertRow(table->rowCount());

				// Insert city name into city name column
				table->setItem(table->rowCount() - 1, P_CITYNAME, new QTableWidgetItem(cities->at(cityIndex).GetName()));
			}

			// Insert city name into key column
			table->setItem(table->rowCount() - 1, P_KEY, new QTableWidgetItem(cities->at(cityIndex).GetName()));
			// Add food name
			table->setItem(table->rowCount() - 1, P_FOOD, new QTableWidgetItem(cities->at(cityIndex).GetFoodNameAt(foodIndex)));
			// Add food price
			table->setItem(table->rowCount() - 1, P_PRICE, priceItem);

		} // END for iterate through food list
	} // END for iterate through city list
}

// Deletes contents of passed in table
void TableManager::DeleteAllTableRows(QTableWidget *table)
{
    const int ROW_COUNT = table->rowCount();

    for(int index = 0; index < ROW_COUNT; index++)
    {
        table->removeRow(0);
    }
}
