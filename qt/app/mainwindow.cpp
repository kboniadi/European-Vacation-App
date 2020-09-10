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

/*----PAGE NAVIGATION----*/
/*----HOME----*/
void MainWindow::on_pushButton_home_cities_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(CITIES);
}

void MainWindow::on_pushButton_home_food_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(FOOD);
}

void MainWindow::on_pushButton_home_berlin_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(BERLIN);
}

void MainWindow::on_pushButton_home_paris_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PARIS);
}

void MainWindow::on_pushButton_home_custom_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(CUSTOM);
}

/*----CITIES----*/
void MainWindow::on_pushButton_cities_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
}

/*----FOOD----*/
void MainWindow::on_pushButton_food_back_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
}
