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
    void on_pushButton_home_cities_clicked();

    void on_pushButton_home_food_clicked();

    void on_pushButton_home_berlin_clicked();

    void on_pushButton_home_paris_clicked();

    void on_pushButton_home_custom_clicked();

    void on_pushButton_cities_back_clicked();

    void on_pushButton_food_back_clicked();

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
