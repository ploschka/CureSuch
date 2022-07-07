#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "report.h"
#include "addseller.h"
#include "addnote.h"
#include <QFileDialog>

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

void MainWindow::on_AddNote_clicked()
{
    /*
     * Открывать окошко с полями для добавления
     * Введённые данные проверять сразу, перед созданием объекта
     * Если данные не соответствуют спецификации, то открывать окошко с ошибкой
     * Если данные соответствуют, то создавать объект и добавлять в дерево
     * После этого добавить объект в список сразу на своё место
     * Список сортировать по алфавиту
     */
    AddNote add(this);
    add.setModal(true);
    add.exec();
}


void MainWindow::on_DeleteNote_clicked()
{
    /*
     * Открыть окно с подтверждением удаления
     * Если не подтверждено, то закрыть окно и ничего не делать
     * Если подтверждено, то перейти к следующим шагам
     * Удалить выделенный в списке объект
     * Найти его в дереве и удалить
     * Вот и всё
     */
}


void MainWindow::on_AddSeller_clicked()
{
    /*
     * Открывать окошко с полями для добавления
     * Введённые данные проверять сразу, перед созданием объекта
     * Если данные не соответствуют спецификации, то открывать окошко с ошибкой
     * Если данные соответствуют, то создавать объект и проверять его наличие в хэш таблице
     * Если объект уже существует, открывать окошко с ошибкой
     * Если такого объекта нет, то добавлять в хэш таблицу
     * После этого добавить объект в список сразу на своё место
     * Список сортирован по алфавиту
     */
    AddSeller add(this);
    add.setModal(true);
    add.exec();
}


void MainWindow::on_DeleteSeller_clicked()
{
    /*
     * Открыть окно с подтверждением удаления
     * Если не подтверждено, то закрыть окно и ничего не делать
     * Если подтверждено, то перейти к следующим шагам
     * Удалить выделенный в списке объект
     * Найти его в хт и удалить
     * Вот и всё
     */
}


void MainWindow::on_ReportButton_clicked()
{
    /*
     * Открывается окно с полями для ввода
     * После этого выполняется поиск по заданным полям и формируется отчёт
     * Если в итоге отчёт пустой, то это сразу выводится в отдельном окошечке
     * Отчёт выводится в отдельном окне
     */
    Report rep(this);
    rep.setModal(true);
    rep.exec();
}


void MainWindow::on_NoteImport_clicked()
{

}


void MainWindow::on_NoteExport_clicked()
{

}


void MainWindow::on_SellerImport_clicked()
{

}


void MainWindow::on_SellerExport_clicked()
{

}


void MainWindow::on_DebugButton_clicked()
{

}

