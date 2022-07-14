#include "addnote.h"
#include "ui_addnote.h"

AddNote::AddNote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNote)
{
    ui->setupUi(this);
}

AddNote::~AddNote()
{
    delete ui;
}

Note* AddNote::getNewNote()
{
    return newNote;
}

void AddNote::on_AddButton_clicked()
{
    if(!ui->Discipline->text().isEmpty() && !ui->ThemeLine->text().isEmpty()
            && !ui->NumberLine->text().isEmpty())
    {
        newNote = new Note(ui->Discipline->text().toStdString(), ui->ThemeLine->text().toStdString(), ui->NumberLine->text().toStdString());
        this->accept();
    }
}


void AddNote::on_CancelButton_clicked()
{
    this->reject();
}
