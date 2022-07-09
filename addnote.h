#ifndef ADDNOTE_H
#define ADDNOTE_H

#include <QDialog>
#include "mainwindow.h"
#include "Note.h"

namespace Ui {
class AddNote;
}

class AddNote : public QDialog
{
    Q_OBJECT

public:
    explicit AddNote(QWidget *parent = nullptr);
    ~AddNote();
    Note* getNewNote();



private slots:
    void on_AddButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::AddNote *ui;
    Note* newNote;
};

#endif // ADDNOTE_H
