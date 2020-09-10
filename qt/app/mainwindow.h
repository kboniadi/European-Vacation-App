#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

    void clearFields() // function to reset all tables and user inputs
    {

    }

    enum page // enums for navigation through stackedwidget
    {
        HOME,
        CITIES,
        FOOD,
        PARIS,
        CUSTOM,
        PURCHASE,
        RECEIPT,
        LOGIN,
        ADMIN
    };

private slots:
    /*----NAVIGATION----*/
    void on_pushButton_home_cities_clicked(); // home

    void on_pushButton_home_food_clicked();

    void on_pushButton_home_berlin_clicked();

    void on_pushButton_home_paris_clicked();

    void on_pushButton_home_custom_clicked();

    void on_pushButton_cities_back_clicked(); // cities

    void on_pushButton_food_back_clicked(); // food

    void on_pushButton_paris_back_clicked(); //paris

    void on_pushButton_paris_continue_clicked();

    void on_pushButton_custom_back_clicked(); // custom

    void on_pushButton_custom_continue_clicked();

    void on_pushButton_purchase_back_clicked(); // purchase

    void on_pushButton_purchase_continue_clicked();

    void on_pushButton_receipt_back_clicked(); // receipt
    /*----END NAVIGATION----*/

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
