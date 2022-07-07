#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "HashTable.h"
#include "Tree.h"
#include "Person.h"
#include "Note.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddNote_clicked();

    void on_DeleteNote_clicked();

    void on_AddSeller_clicked();

    void on_DeleteSeller_clicked();

    void on_ReportButton_clicked();

private:
    Ui::MainWindow *ui;
    HashTable<Person>* ht;
    Tree<Note>* rb;
};
#endif // MAINWINDOW_H
