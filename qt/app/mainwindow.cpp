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
    
    // Create Database
	DBManager::instance();

    // Create TableManager
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
	DBManager::instance()->GetCities(unsorted);
	unsorted.removeAll("Berlin");
	unsorted.push_front("Berlin");

	algorithm::sort(unsorted, sorted);
	TableManager::instance()->PopulateTripTable(ui->tableView_berlin_cities, sorted);

	int total = 0;
	for (int i = 0; i < sorted.length() - 1; i++) {
		total += DBManager::instance()->GetDistances(sorted[i], sorted[i + 1]);
	}

    ui->label_berlin_total_distance->setText("Total Distance(km): " + QString::number(total));
    ui->label_berlin_total_distance->adjustSize();
}

void MainWindow::on_pushButton_home_paris_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PARIS);
    ui->spinBox_paris_select->setValue(1);
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

    ui->spinBox_paris_select->setMaximum(sorted.length() - 1); // fills the spinbox with max number of cities to visit

    for (int i = 0; i < citiesToVisit + 1; i++) // fills trip list with sorted list
    {
        trip.push_back(sorted.front());
        sorted.pop_front();
    }

    TableManager::instance()->PopulateTripTable(ui->tableView_paris_cities, trip);

    int total = 0;
    for (int i = 0; i < trip.length() - 1; i++) {
        total += DBManager::instance()->GetDistances(trip[i], trip[i + 1]);
    }

    ui->label_paris_total_distance->setText("Total Distance(km): " + QString::number(total));
    ui->label_paris_total_distance->adjustSize();
}

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
/*----END NAVIGATION----*/


/*----HELPER FUNCTIONS----*/

// Destroy cities list used in purchasing and receipt page
void MainWindow::DestroyCities()
{
    for(int index = 0; index < cities->size(); index++)
    {
        cities->operator[](index).DestroyCity();
    }
}

// Clear fields on admin page for add/edit/remove food items
void ClearFields()
{

}

void MainWindow::on_pushButton_admin_import_clicked()
{
	DBManager::instance()->ImportCities(this);
    TableManager::instance()->InitializeAdminTable(ui->tableView_admin_cities);
}
/*----END NAVIGATION----*/


