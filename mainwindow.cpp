#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ht = new HashTable<Person>(50, to_number);
    rb = new Tree<Note>;
}

MainWindow::~MainWindow()
{
    delete ui;
}
