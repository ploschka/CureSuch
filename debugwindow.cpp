#include "debugwindow.h"
#include "ui_debugwindow.h"
#include <QStringList>
#include <sstream>
#include <utility>

template<typename T1, typename T2>
void showTree(Tree<T1, T2>* tree, QPlainTextEdit* Text)
{
    Text->clear();
    std::stringstream ss;
    tree->print(ss);
    std::string tmp;
    while(!ss.eof())
    {
        std::getline(ss, tmp, '\n');
        Text->appendPlainText(QString::fromStdString(tmp));
    }
}

template<typename T1, typename T2>
void showTable(HashTable<T1, T2>* table, QPlainTextEdit* Text)
{
    Text->clear();
    std::stringstream ss;
    ss << *(table);
    std::string tmp;
    while(!ss.eof())
    {
        std::getline(ss, tmp, '\n');
        Text->appendPlainText(QString::fromStdString(tmp));
    }
}

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

    connect(ui->AddressTree, SIGNAL(clicked()), this, SLOT(showAddressTree()));
    connect(ui->DispTree, SIGNAL(clicked()), this, SLOT(showDispTree()));
    connect(ui->NameTree, SIGNAL(clicked()), this, SLOT(showNameTree()));
    connect(ui->NumberTree, SIGNAL(clicked()), this, SLOT(showNumberTree()));
    connect(ui->PriceTree, SIGNAL(clicked()), this, SLOT(showPriceTree()));
    connect(ui->ThemeTree, SIGNAL(clicked()), this, SLOT(showThemeTree()));
    connect(ui->NumberTable, SIGNAL(clicked()), this, SLOT(showNumberTable()));
}

DebugWindow::~DebugWindow()
{
    delete ui;
}

void DebugWindow::showAddressTree()
{
    showTree(par->address, ui->Text);
}

void DebugWindow::showDispTree()
{
    showTree(par->dis, ui->Text);
}

void DebugWindow::showNameTree()
{
    showTree(par->name, ui->Text);
}

void DebugWindow::showNumberTree()
{
    showTree(par->tnum, ui->Text);
}

void DebugWindow::showPriceTree()
{
    showTree(par->price, ui->Text);
}

void DebugWindow::showThemeTree()
{
    showTree(par->theme, ui->Text);
}


void DebugWindow::showNumberTable()
{
    showTable(par->hnum, ui->Text);
}




