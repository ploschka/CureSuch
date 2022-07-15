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
#include <QMessageBox>

size_t num_to_num(const std::string& s)
{
    size_t result = 0;
    std::string combined = s;
    for(auto i: combined)
    {
        result += i;
    }
    return result;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->NotesList->header()->setSectionsMovable(false);
    ui->SellerList->header()->setSectionsMovable(false);

    name = new Tree<std::string, Person*>;
    hnum = new HashTable<std::string, Person*>(1000, num_to_num);
    price = new Tree<size_t, Person*>;
    address = new Tree<std::string, Person*>;

    dis = new Tree<std::string, Note*>;
    theme = new Tree<std::string, Note*>;
    tnum = new Tree<std::string, Note*>;

    parser = new CSVParser;
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

    delete parser;
}

void MainWindow::purge(QTreeWidgetItem* item, Note* victim)
{
    ui->NotesList->setCurrentItem(nullptr);
    ui->DeleteNote->setEnabled(false);
    this->dis->remove(victim->getDiscipline(), victim);
    this->theme->remove(victim->getTheme(), victim);
    this->tnum->remove(victim->getNumber(), victim);
}

void MainWindow::purge(QTreeWidgetItem* item, Person* victim)
{
    ui->SellerList->setCurrentItem(nullptr);
    ui->DeleteSeller->setEnabled(false);
    this->name->remove(victim->getName(), victim);
    this->hnum->remove(victim->getNumber());
    this->price->remove(victim->getPrice(), victim);
    this->address->remove(victim->getAddress(), victim);
}

bool MainWindow::add(Note* note)
{
    try
    {
        hnum->find(note->getNumber());
    }
    catch(std::runtime_error error)
    {
        QString str("Невозможно создать конспект для несуществующего продавца");
        QMessageBox::critical(this, "Ошибка создания конспекта", str);
        delete note;
        return false;
    }
    auto numList = tnum->find(note->getNumber());
    bool hasCopy = false;
    if(numList)
    {
        auto el = numList->index(0);
        while(el && !hasCopy)
        {
            if(el->getValue()->getDiscipline() == note->getDiscipline() && el->getValue()->getTheme() == note->getTheme())
            {
                hasCopy = true;
            }
            el = el->next;
        }
        if(hasCopy)
        {
            QString str("Невозможно добавить копию конспекта");
            QMessageBox::critical(this, "Ошибка создания конспекта", str);
            delete note;
            return false;
        }
    }
    dis->insert(note->getDiscipline(), note);
    theme->insert(note->getTheme(), note);
    tnum->insert(note->getNumber(), note);

    QStringList list;
    list << QString::fromStdString(note->getDiscipline()) << QString::fromStdString(note->getTheme())
         << QString::fromStdString(note->getNumber());
    auto item = new QTreeWidgetItem(list);
    notes[item] = note;
    rnotes[note] = item;
    ui->NotesList->addTopLevelItem(item);
    return true;
}

bool MainWindow::add(Person* seller)
{
    try
    {
        hnum->write(seller->getNumber(), seller);
    }
    catch(std::runtime_error error)
    {
        QString str("Продавец с таким номером телефона уже в таблице");
        QMessageBox::critical(this, "Ошибка создания продавца", str);
        delete seller;
        return false;
    }
    name->insert(seller->getName(), seller);
    price->insert(seller->getPrice(), seller);
    address->insert(seller->getAddress(), seller);

    QStringList list;
    list << QString::fromStdString(seller->getName()) << QString::fromStdString(seller->getNumber())
         << QString::fromStdString(std::to_string(seller->getPrice())) << QString::fromStdString(seller->getAddress());
    auto item = new QTreeWidgetItem(list);
    persons[item] = seller;
    rpersons[seller] = item;
    ui->SellerList->addTopLevelItem(item);
    return true;
}

void MainWindow::delSellerBtn(QTreeWidgetItem* curr)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Удаление продавца", "Вы уверены, что хотите удалить продавца:\n" +
                                                              curr->text(0) + ' ' + curr->text(1) + ' ' + curr->text(2) + '?',
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Person* victim = persons[curr];
        auto list = tnum->find(victim->getNumber());
        if(list)
        {
            QString str;
            size_t len = list->length();
            auto cr = list->index(0);
            for(size_t i = 0; i < len; i++)
            {
                str += QString::fromStdString(cr->getValue()->getDiscipline() + ' ' + cr->getValue()->getTheme() + ' '
                                              + cr->getValue()->getNumber() + '\n');
                cr = cr->next;
            }
            QMessageBox::StandardButton reply2 =
                    QMessageBox::question(this, "Удаление связей", "Также будут удалены следующие записи конспектов:\n" +
                                          str + "\nПродолжить?",
                                          QMessageBox::Yes | QMessageBox::No);
            if(reply2 == QMessageBox::Yes)
            {
                cr = list->index(0);
                for(size_t i = 0; i < len; i++)
                {
                    Note* linkvictim = cr->getValue();
                    auto item = rnotes[linkvictim];
                    purge(item, linkvictim);
                    delete item;
                    delete linkvictim;
                    cr = cr->next;
                }
            }
        }
        purge(curr, victim);
        delete curr;
        delete victim;
    }
}

void MainWindow::delNoteBtn(QTreeWidgetItem* curr)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Удаление конспекта", "Вы уверены, что хотите удалить конспект:\n" +
                                                              curr->text(0) + ' ' + curr->text(1) + ' ' + curr->text(2) + '?',
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Note* victim = notes[curr];
        purge(curr, victim);
        delete curr;
        delete victim;
    }
}

void MainWindow::on_AddNote_clicked()
{
    AddNote add(this);
    add.setModal(true);
    if(add.exec() == QDialog::Accepted)
    {
        Note* note = add.getNewNote();
        this->add(note);
    }
}


void MainWindow::on_DeleteNote_clicked()
{
    auto curr =(ui->NotesList->currentItem());
    delNoteBtn(curr);
}


void MainWindow::on_AddSeller_clicked()
{
    AddSeller add(this);
    add.setModal(true);
    if(add.exec() == QDialog::Accepted)
    {
        Person* seller = add.getNewSeller();
        this->add(seller);
    }
}

void MainWindow::on_DeleteSeller_clicked()
{
    auto curr =(ui->SellerList->currentItem());
    delSellerBtn(curr);
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
    if(!path.empty())
    {
        parsed_strings strs = parser->parse(path);
        for(auto& i: strs)
        {
            std::string dis = i[0];
            std::string theme = i[1];
            std::string number = i[2];
            if (!add(new Note(dis, theme, number)))
            {
                break;
            }
        }
    }
}

void MainWindow::on_NoteExport_clicked()
{
    std::string path = QFileDialog::getSaveFileName(this, "Сохранить файл с конспектами", "", "*.txt").toStdString();
    if(!path.empty())
    {
        auto list = ui->NotesList->findItems("", Qt::MatchStartsWith, 0);
        std::ofstream file(path);
        for(auto& i: list)
        {
            file << i->text(0).toStdString() << "; " << i->text(1).toStdString()<< "; "
                 << i->text(2).toStdString() << '\n';
        }
        file.flush();
        file.close();
    }
}

void MainWindow::on_SellerImport_clicked()
{
    std::string path = QFileDialog::getOpenFileName(this, "Открыть файл с продавцами", "", "*.txt").toStdString();
    if(!path.empty())
    {
        parsed_strings strs = parser->parse(path);
        for(auto& i: strs)
        {
            std::string name = i[0];
            std::string number = i[1];
            size_t price = std::stoul(i[2]);
            std::string address = i[3];
            if(!add(new Person(name, number, price, address)))
            {
                break;
            }
        }
    }
}

void MainWindow::on_SellerExport_clicked()
{
    std::string path = QFileDialog::getSaveFileName(this, "Сохранить файл с продавцами", "", "*.txt").toStdString();
    if(!path.empty())
    {
        auto list = ui->SellerList->findItems("", Qt::MatchStartsWith, 0);
        std::ofstream file(path);
        for(auto& i: list)
        {
            file << i->text(0).toStdString() << "; " << i->text(1).toStdString() << "; "
                 << i->text(2).toStdString() << "; " << i->text(3).toStdString() << '\n';
        }
        file.flush();
        file.close();
    }
}

void MainWindow::on_DebugButton_clicked()
{
    DebugWindow debug(this);
    debug.setModal(true);
    debug.exec();
}

void MainWindow::on_NoteSearchButton_clicked()
{
    Search search(this, "Поиск конспектов", ui->NotesList);
    search.setModal(false);
    search.exec();
}

void MainWindow::on_SellerSearchButton_clicked()
{
    Search search(this, "Поиск продавцов", ui->SellerList);
    search.setModal(true);
    search.exec();
}

void MainWindow::on_NotesList_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->DeleteNote->setEnabled(true);
}


void MainWindow::on_SellerList_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->DeleteSeller->setEnabled(true);
}
