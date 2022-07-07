#include "addseller.h"
#include "ui_addseller.h"

AddSeller::AddSeller(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSeller)
{
    ui->setupUi(this);
}

AddSeller::~AddSeller()
{
    delete ui;
}
