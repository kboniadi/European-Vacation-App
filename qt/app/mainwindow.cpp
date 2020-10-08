#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include "City.h"
#include "tablemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	  ui->stackedWidget_pages->setCurrentIndex(HOME); // setCurrentIndex cycles through the stackedwidget
    ui->tabWidget_home_pages->setCurrentIndex(HOME); // setCurrentIndex cycles through the tabWidget
    

	// Creates single Database instance
	DBManager::instance();

	// Create single TableManager instance
    TableManager::instance();

    // Create list of cities used in purchasing and receipt pages
    cities = new QVector<City>;

    // initialize paris trip spinbox (will be moved to tablemanager)
    ui->spinBox_paris_select->setMinimum(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*----PAGE NAVIGATION----*/
/*----HOME----*/
void MainWindow::on_pushButton_home_berlin_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(BERLIN);
    QStringList unsorted;
    QStringList sorted;

    // Delete existing cities list
    DestroyCities();

	// puts list of cities in a form that can be sorted
	DBManager::instance()->GetCities(unsorted);
	unsorted.removeAll("Berlin");
	unsorted.push_front("Berlin");

    algorithm::sort(unsorted, sorted);
    TableManager::instance()->PopulateTripTable(ui->tableView_berlin_cities, sorted);


    // TODO This is where 'delete _foods' in the city constructor will break the program.
    // Dunno how to resolve

    // Populate city objects
    for(int index = 0; index < sorted.size(); index++)
    {
        City temp;
        temp.SetName(sorted.at(index));
        cities->push_back(temp);
    }

	// totals distance for the trip based on sorted list of cities
	int total = 0;
	for (int i = 0; i < sorted.length() - 1; i++) {
		total += DBManager::instance()->GetDistances(sorted[i], sorted[i + 1]);
	}

    ui->label_berlin_total_distance->setText("Total Distance(km): " + QString::number(total));
    ui->label_berlin_total_distance->adjustSize();
}

void MainWindow::on_pushButton_home_paris_clicked()
{
    City temp; // City object to populate initial cities list

    ui->stackedWidget_pages->setCurrentIndex(PARIS);
    ui->spinBox_paris_select->setValue(1);

    // Delete existing cities list
    DestroyCities();

    // Populate initial two cities
    temp.SetName("Paris");
    cities->push_back(temp);
    temp.SetName("Brussels");
    cities->push_back(temp);

}

void MainWindow::on_pushButton_home_custom_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(CUSTOM);
    // hiding/showing for custom trip page (will move to a tablemanager function)
    ui->label_custom_otherCities->hide();
    ui->comboBox_custom_otherCities->hide();
    ui->pushButton_custom_add->hide();

    // Delete existing cities list
    DestroyCities();

    // Reset fields/objects
    customTripCities.clear();
    ui->label_custom_distance->clear();
    customTripComboBoxCities.clear();
    ui->comboBox_custom_otherCities->clear();
    ui->comboBox_custom_startingCity->clear();

    // Reset table
    QSqlQueryModel* reset = new QSqlQueryModel;
    ui->tableView->setModel(reset);

    // If food selection enabled, disable
    if(ui->pushButton_custom_continue->isEnabled())
    { ui->pushButton_custom_continue->setDisabled(true); }

    // If combobox is disabled, enable
    if(!ui->comboBox_custom_startingCity->isEnabled())
    { ui->comboBox_custom_startingCity->setEnabled(true); }

    // Set combobox index to 0
    ui->comboBox_custom_startingCity->setCurrentIndex(0);

    // Populate cities dropdown
    DBManager::instance()->GetCities(customTripComboBoxCities);
    ui->comboBox_custom_startingCity->addItems(customTripComboBoxCities);

    // Grey out 'finalize trip'
    ui->pushButton_custom_finalize->setDisabled(true);
}

void MainWindow::on_pushButton_home_exit_clicked()
{
    QCoreApplication::quit();
}

/*----BERLIN----*/
void MainWindow::on_pushButton_berlin_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    DestroyCities();
}

void MainWindow::on_pushButton_berin_continue_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PURCHASE);

    // Create shopping list
    DBManager::instance()->CreateShoppingList(cities);

    // Initialize purchase table to blank
    TableManager::instance()->InitializePurchaseTable(ui->tableWidget_purchase_pos,
                                                      TableManager::instance()->PURCHASE_TABLE_COL_COUNT,
                                                      TableManager::instance()->purchaseTableColNames);
    // Populate purchase table
    TableManager::instance()->PopulatePurchaseTable(ui->tableWidget_purchase_pos, cities);

    // Insert spinbox column
    TableManager::instance()->InsertSpinBoxCol(ui->tableWidget_purchase_pos,
                                               TableManager::instance()->PURCHASE_SPINBOX_MIN,
                                               TableManager::instance()->PURCHASE_SPINBOX_MAX,
                                               TableManager::instance()->P_QTY);
}

/*----PARIS----*/
void MainWindow::on_spinBox_paris_select_valueChanged(int citiesToVisit)
{
    // kord's berlin trip code unless commented
    QStringList unsorted;
    QStringList sorted;
    QStringList trip; // list of cities included in trip
    DBManager::instance()->GetCities(unsorted);
    unsorted.removeAll("Paris");
    unsorted.push_front("Paris");
    algorithm::sort(unsorted, sorted);
    City temp; // temp object used to populate purchase page

    // Populate spinbox
    ui->spinBox_paris_select->setMaximum(sorted.length() - 1);

    // Fill trip list with sorted list
    for (int i = 0; i < citiesToVisit + 1; i++)
    {
        trip.push_back(sorted.front());
        sorted.pop_front();
    }

    // If spinbox value is decreased, remove city from purchase cities list
    if(ui->spinBox_paris_select->value() < parisSpinBoxPreviousVal && cities->size() > 0)
    {
        cities->pop_back();
    }
    else // If spinbox value is increased, add city to purchase cities list
    {
        // Add subsequent cities to purchase page object
        temp.SetName(trip.back());
        cities->push_back(temp);
    }

    TableManager::instance()->PopulateTripTable(ui->tableView_paris_cities, trip);

    int total = 0;
    for (int i = 0; i < trip.length() - 1; i++) {
        total += DBManager::instance()->GetDistances(trip[i], trip[i + 1]);
    }

    ui->label_paris_total_distance->setText("Total Distance(km): " + QString::number(total));
    ui->label_paris_total_distance->adjustSize();

    parisSpinBoxPreviousVal = ui->spinBox_paris_select->value();
}

void MainWindow::on_pushButton_paris_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    DestroyCities();
}

void MainWindow::on_pushButton_paris_continue_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PURCHASE);

    // Create shopping list
    DBManager::instance()->CreateShoppingList(cities);

    // Initialize purchase table to blank
    TableManager::instance()->InitializePurchaseTable(ui->tableWidget_purchase_pos,
                                                      TableManager::instance()->PURCHASE_TABLE_COL_COUNT,
                                                      TableManager::instance()->purchaseTableColNames);
    // Populate purchase table
    TableManager::instance()->PopulatePurchaseTable(ui->tableWidget_purchase_pos, cities);

    // Insert spinbox column
    TableManager::instance()->InsertSpinBoxCol(ui->tableWidget_purchase_pos,
                                               TableManager::instance()->PURCHASE_SPINBOX_MIN,
                                               TableManager::instance()->PURCHASE_SPINBOX_MAX,
                                               TableManager::instance()->P_QTY);
}

/*----CUSTOM-----*/
void MainWindow::on_pushButton_custom_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    DestroyCities();
}

void MainWindow::on_pushButton_custom_continue_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PURCHASE);

    // Create shopping list
    DBManager::instance()->CreateShoppingList(cities);

    // Initialize purchase table to blank
    TableManager::instance()->InitializePurchaseTable(ui->tableWidget_purchase_pos,
                                                      TableManager::instance()->PURCHASE_TABLE_COL_COUNT,
                                                      TableManager::instance()->purchaseTableColNames);
    // Populate purchase table
    TableManager::instance()->PopulatePurchaseTable(ui->tableWidget_purchase_pos, cities);

    // Insert spinbox column
    TableManager::instance()->InsertSpinBoxCol(ui->tableWidget_purchase_pos,
                                               TableManager::instance()->PURCHASE_SPINBOX_MIN,
                                               TableManager::instance()->PURCHASE_SPINBOX_MAX,
                                               TableManager::instance()->P_QTY);
}

void MainWindow::on_comboBox_custom_startingCity_activated(int index)
{
    // hiding/showing for custom trip page (will move to a tablemanager function)
    ui->label_custom_otherCities->show();
    ui->comboBox_custom_otherCities->show();
    ui->pushButton_custom_add->show();

    // Enable other_cities combobox
    if(!ui->comboBox_custom_otherCities->isEnabled())
    { ui->comboBox_custom_otherCities->setEnabled(true); }

    // Enable add_city pushbutton
    if(!ui->pushButton_custom_add->isEnabled())
    { ui->pushButton_custom_add->setEnabled(true); }

    // Place starting city on separate list
    customTripCities.push_back(ui->comboBox_custom_startingCity->currentText());

    // Remove cities from available selection
    customTripComboBoxCities.removeOne(ui->comboBox_custom_startingCity->currentText());

    // Populate other combobox
    ui->comboBox_custom_otherCities->addItems(customTripComboBoxCities);

    // Grey out combobox
    ui->comboBox_custom_startingCity->setDisabled(true);

    // Place city on table
    TableManager::instance()->PopulateTripTable(ui->tableView, customTripCities);

}

/*----PURCHASE----*/
void MainWindow::on_pushButton_purchase_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    DestroyCities();
}

void MainWindow::on_pushButton_purchase_continue_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(RECEIPT);

    // Collect data from spinboxes and populate final form of cities objects
    CreateReceipt(cities);

    // Initialize (to blank), receipt table
    TableManager::instance()->InitializeReceiptTable(ui->tableWidget_receipt_view,
                                                      TableManager::instance()->PURCHASE_TABLE_COL_COUNT,
                                                      TableManager::instance()->purchaseTableColNames);

    // Populate table with data
    TableManager::instance()->PopulateReceiptTable(ui->tableWidget_receipt_view, cities);
}

/*----RECEIPT----*/
void MainWindow::on_pushButton_receipt_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    DestroyCities();
}

/*----ADMIN----*/
void MainWindow::on_pushButton_login_continue_clicked()
{
	ui->stackedWidget_pages->setCurrentIndex(ADMIN);
    ui->tabWidget_admin_pages->setCurrentIndex(ADMINTAB);
    TableManager::instance()->InitializeAdminTable(ui->tableView_admin_cities);
}

void MainWindow::on_pushButton_admin_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    ui->tabWidget_home_pages->setCurrentIndex(HOME);
}

void MainWindow::on_pushButton_admin_food_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    ui->tabWidget_home_pages->setCurrentIndex(HOME);
}

void MainWindow::on_pushButton_admin_import_clicked()
{
    DBManager::instance()->ImportCities(this);
    TableManager::instance()->InitializeAdminTable(ui->tableView_admin_cities);
}



void MainWindow::on_pushButton_custom_add_clicked()
{
    // Add city to QStringList
    customTripCities.push_back(ui->comboBox_custom_otherCities->currentText());

    // Remove city from combobox
    ui->comboBox_custom_otherCities->removeItem(ui->comboBox_custom_otherCities->currentIndex());

    // Add city to table
    TableManager::instance()->PopulateTripTable(ui->tableView, customTripCities);

    // Enable "Plan trip" button
    if(!ui->pushButton_custom_finalize->isEnabled())
    { ui->pushButton_custom_finalize->setEnabled(true);}

    // Disable button if empty
    if(ui->comboBox_custom_otherCities->count() == 0)
    { ui->pushButton_custom_add->setDisabled(true); }
}


void MainWindow::on_pushButton_custom_finalize_clicked()
{
    QStringList sorted;

    // Disable other_cities combobox
    if(ui->comboBox_custom_otherCities->isEnabled())
    { ui->comboBox_custom_otherCities->setDisabled(true); }

    // Disable add_city pushbutton
    if(ui->pushButton_custom_add->isEnabled())
    { ui->pushButton_custom_add->setDisabled(true); }

    // Disable finalize_trip button
    if(ui->pushButton_custom_finalize->isEnabled())
    { ui->pushButton_custom_finalize->setDisabled(true); }

    // Enable 'Continue' pushbutton
    if(!ui->pushButton_custom_continue->isEnabled())
    { ui->pushButton_custom_continue->setEnabled(true); }

    // Run the sorting algorithm
    algorithm::sort(customTripCities, sorted);
    TableManager::instance()->PopulateTripTable(ui->tableView, sorted);

    // Delete existing cities list
    DestroyCities();

    // Populate city objects
    for(int index = 0; index < sorted.size(); index++)
    {
        City temp;
        temp.SetName(sorted.at(index));
        cities->push_back(temp);
        qDebug() << cities->at(index).GetName();
    }

    // Calculate distance
    int total = 0;
    for (int i = 0; i < sorted.length() - 1; i++) {
        total += DBManager::instance()->GetDistances(sorted[i], sorted[i + 1]);
    }

    // Display distance
    ui->label_custom_distance->setText("Total Distance(km): " + QString::number(total));
    ui->label_custom_distance->adjustSize();
}

void MainWindow::on_tabWidget_home_pages_currentChanged(int index)
{
    if(index == T_CITIES)
    {
        // Create objects
        QStringList* cityNames = new QStringList;
        QVector<int>* distancesFromBerlin = new QVector<int>;

        // Initialize cities table
        TableManager::instance()->InitializeCitiesTable(ui->tableWidget_cities_view,
                                                        TableManager::instance()->CITIES_TABLE_COL_COUNT,
                                                        TableManager::instance()->citiesTableColNames);

        // Get table data from db
        DBManager::instance()->GetCitiesTable(cityNames, distancesFromBerlin);


        // Populate table
        TableManager::instance()->PopulateCitiesTable(ui->tableWidget_cities_view, cityNames, distancesFromBerlin);
    }
}


/*----END NAVIGATION----*/


/*----HELPER FUNCTIONS----*/

// Destroy cities list used in purchasing and receipt page
void MainWindow::DestroyCities()
{
    int size = cities->size();

    for(int index = 0; index < size; index++)
    {
        cities->pop_front();
    }
}

// Clear fields on admin page for add/edit/remove food items
void ClearFields()
{

}

// Create receipt to print on receipt page
void MainWindow::CreateReceipt(QVector<City>* cities)
{
    int uberIndex = 0;
    for(int cityIndex = 0; cityIndex < cities->size(); cityIndex++)
    {
        for(int foodIndex = 0; foodIndex < cities->at(cityIndex).GetFoodListSize(); foodIndex++)
        {
            // Add food to item
            cities->operator[](cityIndex).SetFoodQtyAt(foodIndex, TableManager::instance()->purchaseTableSpinBoxes->at(uberIndex)->value());
            uberIndex++;
        }
    }
}

/*----END HELPER FUNCTIONS----*/

