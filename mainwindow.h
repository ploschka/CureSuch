#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "HashTable.h"
#include "Tree.h"
#include "Person.h"
#include "Note.h"
#include <QListWidget>
#include <QTreeWidgetItem>
#include <utility>

typedef std::pair<std::string, Note*> note_by_dis;
typedef std::pair<std::string, Note*> note_by_theme;
typedef std::pair<std::string, Note*> note_by_number;

typedef std::pair<std::string, Person*> per_by_name;
typedef std::pair<std::string, Person*> per_by_number;
typedef std::pair<size_t, Person*> per_by_price;
typedef std::pair<std::string, Person*> per_by_address;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Tree<per_by_name>* name;
    HashTable<per_by_number>* hnum;
    Tree<per_by_price>* price;
    Tree<per_by_address>* address;

    Tree<note_by_dis>* dis;
    Tree<note_by_theme>* theme;
    Tree<note_by_number>* tnum;

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
