#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define TYPE2POINTER
#include "HashTable.h"
#include "Tree.h"
#include "Person.h"
#include "Note.h"
#include <QTreeWidgetItem>
#include <utility>
#include <map>
#include "Parser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Tree<std::string, Person*>* name;
    HashTable<std::string, Person*>* hnum;
    Tree<size_t, Person*>* price;
    Tree<std::string, Person*>* address;

    Tree<std::string, Note*>* dis;
    Tree<std::string, Note*>* theme;
    Tree<std::string, Note*>* tnum;

    std::map<QTreeWidgetItem*, Person*> persons;
    std::map<QTreeWidgetItem*, Note*> notes;

    std::map<Person*, QTreeWidgetItem*> rpersons;
    std::map<Note*, QTreeWidgetItem*> rnotes;

    void delSellerBtn(QTreeWidgetItem* curr);
    void delNoteBtn(QTreeWidgetItem* curr);



private slots:
    void on_AddNote_clicked();

    void on_DeleteNote_clicked();

    void on_AddSeller_clicked();

    void on_DeleteSeller_clicked();

    void on_ReportButton_clicked();

    void on_NoteImport_clicked();

    void on_NoteExport_clicked();

    void on_SellerImport_clicked();

    void on_SellerExport_clicked();

    void on_DebugButton_clicked();

    void on_NoteSearchButton_clicked();

    void on_SellerSearchButton_clicked();

    void on_NotesList_itemClicked(QTreeWidgetItem *item, int column);

    void on_SellerList_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;

    IParser* parser;

    void purge(QTreeWidgetItem* item, Note* victim);
    void purge(QTreeWidgetItem* item, Person* victim);
    bool add(Note* newNote);
    bool add(Person* newPerson);
};
#endif // MAINWINDOW_H
