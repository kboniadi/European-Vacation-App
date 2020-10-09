#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
    showPassword = false;

	ui->setupUi(this);

	ui->stackedWidget_pages->setCurrentIndex(HOME); // setCurrentIndex cycles through the stackedwidget
    ui->tabWidget_pages->setCurrentIndex(HOME); // setCurrentIndex cycles through the tabWidget
    ui->label_incorrect->hide();    // do not show that the password is incorrect
    
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString path = (QDir::currentPath() + "/DataBase/Data.db");
    database.setDatabaseName(path);

	DBManager::instance();
    TableManager::instance();
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

/*----ADMIN----*/

void MainWindow::on_pushButton_login_continue_clicked()
{
    if (ui->lineEdit_login_username->text() == "admin" && ui->lineEdit_username_password->text() == "admin")
    {
        ui->stackedWidget_pages->setCurrentIndex(ADMIN);
        ui->label_incorrect->hide();

        ui->lineEdit_login_username->setText("");
        ui->lineEdit_username_password->setText("");
    }
    else
        ui->label_incorrect->show();
}

void MainWindow::on_pushButton_admin_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    ui->tabWidget_pages->setCurrentIndex(HOME);
    ui->label_incorrect->hide();
}

void MainWindow::on_lineEdit_username_password_textChanged()
{
    if (!showPassword)
        ui->lineEdit_username_password->setEchoMode(QLineEdit::Password);
    else
        ui->lineEdit_username_password->setEchoMode(QLineEdit::Normal);
}

void MainWindow::on_pushButton_show_password_clicked()
{
    showPassword = !showPassword;

    if (!showPassword)
        ui->lineEdit_username_password->setEchoMode(QLineEdit::Password);
    else
        ui->lineEdit_username_password->setEchoMode(QLineEdit::Normal);
}

/*----END NAVIGATION----*/
