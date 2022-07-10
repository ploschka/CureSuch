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

    Tree<std::string, Person*>* name;
    HashTable<per_by_number>* hnum;
    Tree<size_t, Person*>* price;
    Tree<std::string, Person*>* address;

    Tree<std::string, Note*>* dis;
    Tree<std::string, Note*>* theme;
    Tree<std::string, Note*>* tnum;

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
