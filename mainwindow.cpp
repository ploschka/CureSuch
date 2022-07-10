#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "report.h"
#include "addseller.h"
#include "addnote.h"
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QFileDialog>
#include <fstream>
#include "search.h"
#include "debugwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    name = new Tree<per_by_name>;
    hnum = new HashTable<per_by_number>(1000, num_to_num);
    price = new Tree<per_by_price>;
    address = new Tree<per_by_address>;

    dis = new Tree<note_by_dis>;
    theme = new Tree<note_by_theme>;
    tnum = new Tree<note_by_number>;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete name;
    delete hnum;
    delete price;
    delete address;
    delete dis;
    delete theme;
    delete tnum;
}

void MainWindow::on_AddNote_clicked()
{
    AddNote add(this);
    add.setModal(true);
    if(add.exec() == QDialog::Accepted)
    {
        Note* note = add.getNewNote();
        dis->insert(std::make_pair(note->getDiscipline(), note));
        theme->insert(std::make_pair(note->getTheme(), note));
        tnum->insert(std::make_pair(note->getNumber(), note));

        QStringList list;
        list << QString::fromStdString(note->getDiscipline()) << QString::fromStdString(note->getTheme()) << QString::fromStdString(note->getNumber());
        ui->NotesList->addTopLevelItem(new QTreeWidgetItem(list));
    }
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
    delete (ui->NotesList->currentItem());
    ui->NotesList->setCurrentItem(nullptr);
    ui->DeleteNote->setEnabled(false);
}


void MainWindow::on_AddSeller_clicked()
{
    AddSeller add(this);
    add.setModal(true);
    if(add.exec() == QDialog::Accepted)
    {
        Person* seller = add.getNewSeller();
        name->insert(std::make_pair(seller->getName(), seller));
        hnum->write(std::make_pair(seller->getNumber(), seller));
        price->insert(std::make_pair(seller->getPrice(), seller));
        address->insert(std::make_pair(seller->getAddress(), seller));

        QStringList list;
        list << QString::fromStdString(seller->getName()) << QString::fromStdString(seller->getNumber())
             << QString::fromStdString(std::to_string(seller->getPrice())) << QString::fromStdString(seller->getAddress());
        ui->SellerList->addTopLevelItem(new QTreeWidgetItem(list));
    }
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
    Report rep(this);
    rep.setModal(true);
    rep.exec();
}

void MainWindow::on_NoteImport_clicked()
{
    std::string path = QFileDialog::getOpenFileName(this, "Открыть файл с конспектами", "", "*.txt").toStdString();
}

void MainWindow::on_NoteExport_clicked()
{
    std::string path = QFileDialog::getSaveFileName(this, "Сохранить файл с конспектами", "", "*.txt").toStdString();
}

void MainWindow::on_SellerImport_clicked()
{
    std::string path = QFileDialog::getOpenFileName(this, "Открыть файл с продавцами", "", "*.txt").toStdString();
}

void MainWindow::on_SellerExport_clicked()
{
    std::string path = QFileDialog::getSaveFileName(this, "Сохранить файл с продавцами", "", "*.txt").toStdString();
}

void MainWindow::on_DebugButton_clicked()
{
    DebugWindow debug(this);
    debug.setModal(true);
    debug.exec();
}

void MainWindow::on_NoteSearchButton_clicked()
{
    Search search(this, "Поиск конспектов");
    search.ggg(ui->NotesList);
    search.setModal(true);
    search.exec();
}

void MainWindow::on_SellerSearchButton_clicked()
{
    Search search(this, "Поиск продавцов");
    search.ggg(ui->SellerList);
    search.setModal(true);
    search.exec();
}

void MainWindow::on_NotesList_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->DeleteNote->setEnabled(true);
}

