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
