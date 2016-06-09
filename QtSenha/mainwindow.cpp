#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tecla1 = new Tecla();
    tecla2 = new Tecla();
    tecla3 = new Tecla();
    tecla4 = new Tecla();
    tecla5 = new Tecla();
    tecla6 = new Tecla();
    tecla7 = new Tecla();
    tecla8 = new Tecla();
    tecla9 = new Tecla();
    tecla10 = new Tecla();
    tecla11 = new Tecla();
    tecla12 = new Tecla();


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   ui->pushButton = tecla1;
}

void MainWindow::on_pushButton_2_clicked()
{
     ui->pushButton_2 = tecla2;
}

void MainWindow::on_pushButton_3_clicked()
{
     ui->pushButton_3 = tecla3;
}

void MainWindow::on_pushButton_4_clicked()
{
     ui->pushButton_4 = tecla4;
}

void MainWindow::on_pushButton_5_clicked()
{
     ui->pushButton_5 = tecla5;
}

void MainWindow::on_pushButton_6_clicked()
{
     ui->pushButton_6 = tecla6;
}

void MainWindow::on_pushButton_7_clicked()
{
     ui->pushButton_7 = tecla7;
}

void MainWindow::on_pushButton_8_clicked()
{
     ui->pushButton_8 = tecla8;
}

void MainWindow::on_pushButton_9_clicked()
{
     ui->pushButton_9 = tecla9;
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->pushButton_10 = tecla10;
}

void MainWindow::on_pushButton_11_clicked()
{
     ui->pushButton_11 = tecla11;
}

void MainWindow::on_pushButton_12_clicked()
{
     ui->pushButton_12 = tecla12;
}
