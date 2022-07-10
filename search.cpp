#include "search.h"
#include "ui_search.h"

Search::Search(QWidget *parent, QString title) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    ui->tree->header()->setSectionsMovable(false);
}

Search::~Search()
{
    delete ui;
}

void Search::ggg(QTreeWidget* wgg)
{
    this->wg = wgg;
    ui->tree->setColumnCount(wg->columnCount());
    ui->tree->setHeaderItem(wg->headerItem()->clone());

    ui->label_1->setText(wg->headerItem()->text(0));
    ui->label_2->setText(wg->headerItem()->text(1));
    ui->label_3->setText(wg->headerItem()->text(2));

    if (wg->columnCount() == 3)
    {
        ui->label_4->hide();
        ui->line_4->hide();
    }
    else
    {
        ui->label_4->setText(wg->headerItem()->text(3));
    }
}
