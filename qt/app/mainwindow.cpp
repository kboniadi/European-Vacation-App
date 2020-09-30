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
    ui->tabWidget_pages->setCurrentIndex(HOME); // setCurrentIndex cycles through the tabWidget

    // Create Database
    DBManager::instance();

    // Create TableManager
    TableManager::instance();

    // Create list of cities used in purchasing and receipt pages
    cities = new QVector<City>;
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*---FUNCTIONS----*/
// insert any functions for mainwindow into this block

void clearFields() // proposed method to clear all tables and user input.
{

}





/*----END FUNCTIONS----*/


/*----PAGE NAVIGATION----*/
/*----HOME----*/
void MainWindow::on_pushButton_home_berlin_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(BERLIN);
    QStringList unsorted;
    QStringList sorted;

    // Delete existing cities list
    DestroyCities();

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

    int total = 0;
    for (int i = 0; i < sorted.length() - 1; i++) {
        total += DBManager::instance()->GetDistances(sorted[i], sorted[i + 1]);
    }

    ui->label_total_distance->setText("Total Distance(km): " + QString::number(total));
    ui->label_total_distance->adjustSize();
}

void MainWindow::on_pushButton_home_paris_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PARIS);
}

void MainWindow::on_pushButton_home_custom_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(CUSTOM);
    // hiding/showing for custom trip page (will move to a tablemanager function)
    ui->label_custom_otherCities->hide();
    ui->comboBox_custom_otherCities->hide();
    ui->pushButton_custom_add->hide();

}

void MainWindow::on_pushButton_home_exit_clicked()
{
    QCoreApplication::quit();
}

/*----BERLIN----*/
void MainWindow::on_pushButton_berlin_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
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
void MainWindow::on_pushButton_paris_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
}

void MainWindow::on_pushButton_paris_continue_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PURCHASE);
}

/*----CUSTOM-----*/
void MainWindow::on_pushButton_custom_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
}

void MainWindow::on_pushButton_custom_continue_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PURCHASE);
}

void MainWindow::on_comboBox_custom_startingCity_activated(int index)
{
    // hiding/showing for custom trip page (will move to a tablemanager function)
    ui->label_custom_otherCities->show();
    ui->comboBox_custom_otherCities->show();
    ui->pushButton_custom_add->show();
}

/*----PURCHASE----*/
void MainWindow::on_pushButton_purchase_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
}

void MainWindow::on_pushButton_purchase_continue_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(RECEIPT);

    // Collect data from spinboxes and populate final form of cities objects
    CreateReceipt(cities);

    // Initialize (to blank), receipt table

    // Populate table with data
}

/*----RECEIPT----*/
void MainWindow::on_pushButton_receipt_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
}

/*----ADMIN----*/
void MainWindow::on_pushButton_login_continue_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(ADMIN);
    TableManager::instance()->InitializeAdminTable(ui->tableView_database);
}

void MainWindow::on_pushButton_admin_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    ui->tabWidget_pages->setCurrentIndex(HOME);
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

void MainWindow::on_pushButton_admin_import_clicked()
{
    DBManager::instance()->ImportCities(this);
    TableManager::instance()->InitializeAdminTable(ui->tableView_database);
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
