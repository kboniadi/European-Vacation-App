#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>
#include "sortalgorithm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DBManager;
class TableManager;
class City;

/*!
 * @class MainWindow
 * @brief The Mainwindow class is the primary view and interface for all
 * program functionality, including other classes and objects.
 */

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
    /*----END FUNCTIONS----*/

private:
    /*----ENUMS----*/
    enum page // enums for navigation through stackedwidget
    {
		HOME,
        BERLIN,
        PARIS,
        CUSTOM,
        PURCHASE,
        RECEIPT,
        ADMIN
    };

    enum adminPage // enums for navigation through admin tabs
    {
        ADMINTAB,
        FOODTAB
    };

    enum tabs // enum to track tab navigation
    {
        T_HOME,
        T_CITIES,
        T_FOODS,
        T_ADMIN
    };
	/*----END ENUMS----*/

	/*----FUNCTIONS----*/

	// function to reset all tables and user inputs
	void ClearFields();

	// Destroy list of cities list used in purchasing and receipt
	void DestroyCities();

	// Create receipt to print on receipt page
	void CreateReceipt(QVector<City>* cities);
	void UpdateAdminFoodTable();
	/*----END FUNCTIONS----*/

private slots:
    /*----NAVIGATION----*/
    void on_pushButton_home_berlin_clicked(); // home

    void on_pushButton_home_paris_clicked();

    void on_pushButton_home_custom_clicked();

    void on_pushButton_home_exit_clicked();

    void on_pushButton_berlin_back_clicked(); // berlin

    void on_pushButton_berin_continue_clicked();

    void on_spinBox_paris_select_valueChanged(int citiesToVisit); // paris

    void on_pushButton_paris_back_clicked();

    void on_pushButton_paris_continue_clicked();

    void on_pushButton_custom_back_clicked(); // custom

    void on_pushButton_custom_continue_clicked();

    void on_comboBox_custom_startingCity_activated(int index);

    void on_pushButton_purchase_back_clicked(); // purchase

    void on_pushButton_purchase_continue_clicked();

    void on_pushButton_receipt_back_clicked(); // receipt

    void on_pushButton_login_continue_clicked(); // login

    void on_pushButton_admin_back_clicked(); // admin

    void on_pushButton_admin_food_back_clicked();

    void on_pushButton_admin_import_clicked();

	void on_pushButton_admin_add_clicked();

	void on_pushButton_admin_delete_clicked();

	void on_pushButton_admin_edit_clicked();

	void on_tabWidget_admin_pages_currentChanged(int index);

    void on_pushButton_custom_add_clicked();

    void on_pushButton_custom_finalize_clicked();
    /*----END NAVIGATION----*/


    void on_tabWidget_home_pages_currentChanged(int index);

private:
	Ui::MainWindow *ui;

	QVector<City> cities;
    QStringList customTripCities;
    QStringList customTripComboBoxCities;

	int parisSpinBoxPreviousVal{0};
};
#endif // MAINWINDOW_H
