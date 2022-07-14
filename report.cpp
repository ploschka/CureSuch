#include "report.h"
#include "ui_report.h"
#include "mainwindow.h"
#include <QStringList>
#include <QFileDialog>
#include <fstream>

Report::Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);
    ui->reportList->header()->setSectionsMovable(false);
}

Report::~Report()
{
    delete ui;
}

void Report::on_SaveButton_clicked()
{
    std::string path = QFileDialog::getSaveFileName(this, "Сохранить файл с отчётом", "", "*.txt").toStdString();
    if(!path.empty())
    {
        auto list = ui->reportList->findItems("", Qt::MatchStartsWith, 0);
        std::ofstream file(path);
        for(auto& i: list)
        {
            file << i->text(0).toStdString() << "; " << i->text(1).toStdString()<< "; "
                 << i->text(2).toStdString() << '\n';
        }
        file.flush();
        file.close();
    }
}

void Report::on_ReportButton_clicked()
{
    ui->reportList->clear();
    if(!ui->DiscipLine->text().isEmpty() && !ui->ThemeLine->text().isEmpty() && !ui->BuildingLine->text().isEmpty())
    {
        MainWindow* par = dynamic_cast<MainWindow*>(this->parent());
        if(!ui->DiscipLine->text().isEmpty() && !ui->ThemeLine->text().isEmpty() && !ui->BuildingLine->text().isEmpty())
        {
            auto list = par->dis->find(ui->DiscipLine->text().toStdString());
            if(list)
            {
                auto cr = list->index(0);
                while(cr)
                {
                    if(cr->getValue()->getTheme() == ui->ThemeLine->text().toStdString())
                    {
                        Person* per = par->hnum->find(cr->getValue()->getNumber()).second;
                        if(per->getAddress() == ui->BuildingLine->text().toStdString())
                        {
                            QStringList str;
                            str << QString::fromStdString(std::to_string(per->getPrice())) << QString::fromStdString(per->getName())
                                << QString::fromStdString(per->getNumber());
                            ui->reportList->addTopLevelItem(new QTreeWidgetItem(str));
                        }
                    }
                    cr = cr->next;
                }
            }
        }
    }
}

