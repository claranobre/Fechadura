#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int tecla1, tecla2, tecla3, tecla4, tecla5, tecla6, tecla7, tecla8, tecla9, tecla10;
    String tecla11;
    String tecla12;
    String senha[4];

    tecla1 = new Tecla(1);
    tecla2 = new Tecla(2);
    tecla3 = new Tecla(3);
    tecla4 = new Tecla(4);
    tecla5 = new Tecla(5);
    tecla6 = new Tecla(6);
    tecla7 = new Tecla(7);
    tecla8 = new Tecla(8);
    tecla9 = new Tecla(9);
    tecla10 = new Tecla(0);
    tecla11 = new Tecla(*);
    tecla12 = new Tecla(#);
}

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

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    senha[] = ui -> lineEdit->text().toString();
}
