#include "report.h"
#include "ui_report.h"

Report::Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);
    ui->treeWidget->header()->setSectionsMovable(false);
}

Report::~Report()
{
    delete ui;
}

void Report::on_SaveButton_clicked()
{
    /*
     * Отчёт сохраняется в файле Report
     */
}


void Report::on_OKButton_clicked()
{
    this->close();
}
