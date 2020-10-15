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

    /*!
     * @brief Default MainWindow object constructor
     * @param parent; Pointer to parent object (null)
     */
	MainWindow(QWidget *parent = nullptr);

    /*!
     * @brief Destructor
     */
	~MainWindow();

private:
    /*---- BEGIN ENUMS----*/

    /// enums for navigation through primary stackedwidget
    enum page
    {
		HOME,
        BERLIN,
        PARIS,
        CUSTOM,
        PURCHASE,
        RECEIPT,
        ADMIN
    };

    /// enums for navigation through admin tabs
    enum adminPage
    {
        ADMINTAB,
        FOODTAB
    };

    /// enum to track tab navigation
    enum tabs
    {
        T_HOME,
        T_CITIES,
        T_FOODS,
        T_ADMIN
    };
    /*---- END ENUMS ----*/

    /*---- BEGIN HELPER FUNCTIONS ----*/

    /*!
     * @brief Reset all user inputs from fields
     */
	void ClearFields();

    /*!
     * @brief Destroys list of cities list used in purchasing and receipt tables
     */
	void DestroyCities();

    /*!
     * @brief Create receipt to print on receipt page
     * @param cities; List of City objects used to create receipt
     */
	void CreateReceipt(QVector<City>* cities);

    /*!
     * @brief Updates administrator section's food table when food information
     * changes
     */
	void UpdateAdminFoodTable();
    /*---- END HELPER FUNCTIONS ----*/

private slots:

    /*---- BEGIN NAVIGATION ----*/

    /*!
     * @brief Navigates from homepage to berlin trip planning page
     */
    void on_pushButton_home_berlin_clicked();

    /*!
     * @brief Navigates from homepage to paris trip planning page
     */
    void on_pushButton_home_paris_clicked();

    /*!
     * @brief Navigates from homepage to custom trip planning page
     */
    void on_pushButton_home_custom_clicked();

    /*!
     * @brief Quits program from homepage
     */
    void on_pushButton_home_exit_clicked();

    /*!
     * @brief Navigates from berlin trip planning page to home page
     */
    void on_pushButton_berlin_back_clicked();

    /*!
     * @brief Navigates from berlin trip planning page to purchase page
     */
    void on_pushButton_berin_continue_clicked();

    /*!
     * @brief Alters number of cities listed in paris planning table
     */
    void on_spinBox_paris_select_valueChanged(int citiesToVisit);

    /*!
     * @brief Navigates from paris trip planning page to home page
     */
    void on_pushButton_paris_back_clicked();

    /*!
     * @brief Navigates from paris trip planning page to purchase page
     */
    void on_pushButton_paris_continue_clicked();

    /*!
     * @brief Navigates from custom trip planning page to home page
     */
    void on_pushButton_custom_back_clicked();

    /*!
     * @brief Navigates from custom trip planning page to purchase page
     */
    void on_pushButton_custom_continue_clicked();

    /*!
     * @brief Chooses initial city in custom trip planning page
     */
    void on_comboBox_custom_startingCity_activated(int index);

    /*!
     * @brief Navigates from purchase page to home page
     */
    void on_pushButton_purchase_back_clicked();

    /*!
     * @brief Navigates from purchase page to receipt page
     */
    void on_pushButton_purchase_continue_clicked();

    /*!
     * @brief Navigates from receipt page to home page
     */
    void on_pushButton_receipt_back_clicked(); // receipt

    /*!
     * @brief Navigates from admin login page to admin main page
     */
    void on_pushButton_login_continue_clicked();

    /*!
     * @brief Navigates from main admin page to home page
     */
    void on_pushButton_admin_back_clicked();

    /*!
     * @brief Navigates from admin food section to home page
     */
    void on_pushButton_admin_food_back_clicked();

    /*!
     * @brief Imports new cities and their traditional food into database from file
     */
    void on_pushButton_admin_import_clicked();

    /*!
     * @brief Attempts to add new traditional food via manual input
     */
	void on_pushButton_admin_add_clicked();

    /*!
     * @brief Attempts to delete traditional food via manual input
     */
	void on_pushButton_admin_delete_clicked();

    /*!
     * @brief Attempts to edit traditional food price via manual input
     */
	void on_pushButton_admin_edit_clicked();

    /*!
     * @brief Navigates between administrator pages
     */
	void on_tabWidget_admin_pages_currentChanged(int index);

    /*!
     * @brief Adds selected city to custom trip list on custom trip planning page
     */
    void on_pushButton_custom_add_clicked();

    /*!
     * @brief Finalizes custom trip and sorts cities on custom trip planning page
     */
    void on_pushButton_custom_finalize_clicked();

    /*!
     * @brief Navigates between primary (non-administrator) pages
     */
    void on_tabWidget_home_pages_currentChanged(int index);
    /*----END NAVIGATION----*/

private:
    Ui::MainWindow *ui;                     /// Primary ui object containing program's primary view
    QVector<City> cities;                   /// Reusable list of cities
    QStringList customTripCities;           /// Custom trip city names
    QStringList customTripComboBoxCities;   /// Custom trip combobox labels
    int parisSpinBoxPreviousVal{0};         /// Previous index stored in memory for use in paris trip planning
};
#endif // MAINWINDOW_H
