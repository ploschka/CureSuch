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

Person* AddSeller::getNewSeller()
{
    return newSeller;
}

void AddSeller::on_AddButton_clicked()
{
    newSeller = new Person(ui->NameLine->text().toStdString(), ui->NumberLine->text().toStdString(),
                           ui->PriceLine->text().toULong(), ui->BuildingLine->text().toStdString());
    this->accept();
}


void AddSeller::on_CancelButton_clicked()
{
    this->reject();
}

