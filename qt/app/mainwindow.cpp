#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->stackedWidget_pages->setCurrentIndex(HOME); // setCurrentIndex cycles through the stackedwidget
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

void MainWindow::on_pushButton_home_berlin_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PURCHASE);
}

void MainWindow::on_pushButton_home_paris_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PARIS);
}

void MainWindow::on_pushButton_home_custom_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(CUSTOM);
}

void MainWindow::on_pushButton_home_exit_clicked()
{
    QCoreApplication::quit();
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

void MainWindow::on_pushButton_login_continue_clicked()
{
	ui->stackedWidget_pages->setCurrentIndex(ADMIN);
}

/*----ADMIN----*/

void MainWindow::on_pushButton_admin_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
}
/*----END NAVIGATION----*/



