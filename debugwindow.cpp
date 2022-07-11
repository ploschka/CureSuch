#include "debugwindow.h"
#include "ui_debugwindow.h"
#include <QStringList>
#include <sstream>
#include <utility>

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2*> p)
{
    os << p.first << ": " << *(p.second);
    return os;
}

DebugWindow::DebugWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebugWindow)
{
    ui->setupUi(this);
    par = dynamic_cast<MainWindow*>(this->parent());
}

DebugWindow::~DebugWindow()
{
    delete ui;
}

void DebugWindow::on_AddressTree_clicked()
{
    ui->Text->clear();
    std::stringstream ss;
    par->address->print(ss);
    std::string tmp;
    while(!ss.eof())
    {
        std::getline(ss, tmp, '\n');
        ui->Text->appendPlainText(QString::fromStdString(tmp));
    }
}


void DebugWindow::on_DispTree_clicked()
{
    ui->Text->clear();
    std::stringstream ss;
    par->dis->print(ss);
    std::string tmp;
    while(!ss.eof())
    {
        std::getline(ss, tmp, '\n');
        ui->Text->appendPlainText(QString::fromStdString(tmp));
    }
}


void DebugWindow::on_NameTree_clicked()
{
    ui->Text->clear();
    std::stringstream ss;
    par->name->print(ss);
    std::string tmp;
    while(!ss.eof())
    {
        std::getline(ss, tmp, '\n');
        ui->Text->appendPlainText(QString::fromStdString(tmp));
    }
}


void DebugWindow::on_NumberTable_clicked()
{
    ui->Text->clear();
    std::stringstream ss;
    ss << *(par->hnum);
    std::string tmp;
    while(!ss.eof())
    {
        std::getline(ss, tmp, '\n');
        ui->Text->appendPlainText(QString::fromStdString(tmp));
    }
}


void DebugWindow::on_NumberTree_clicked()
{
    ui->Text->clear();
    std::stringstream ss;
    par->tnum->print(ss);
    std::string tmp;
    while(!ss.eof())
    {
        std::getline(ss, tmp, '\n');
        ui->Text->appendPlainText(QString::fromStdString(tmp));
    }
}


void DebugWindow::on_PriceTree_clicked()
{
    ui->Text->clear();
    std::stringstream ss;
    par->price->print(ss);
    std::string tmp;
    while(!ss.eof())
    {
        std::getline(ss, tmp, '\n');
        ui->Text->appendPlainText(QString::fromStdString(tmp));
    }
}


void DebugWindow::on_ThemeTree_clicked()
{
    ui->Text->clear();
    std::stringstream ss;
    par->theme->print(ss);
    std::string tmp;
    while(!ss.eof())
    {
        std::getline(ss, tmp, '\n');
        ui->Text->appendPlainText(QString::fromStdString(tmp));
    }
}

