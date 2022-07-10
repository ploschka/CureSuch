#include "search.h"
#include "ui_search.h"
#include "mainwindow.h"

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
        fl = true;
        ui->label_3->setText("Макс. цена");
        ui->label_4->setText(wg->headerItem()->text(3));
    }
}

template<typename T, bool fl>
std::vector<T*>* srch(MainWindow* par, Ui::Search* ui);

template<>
std::vector<Person*>* srch<Person, true>(MainWindow* par, Ui::Search* ui)
{
    std::vector<Person*>* res = new std::vector<Person*>;
    List<Person*>* list;

    bool l1 = !ui->line_1->text().isEmpty();
    bool l2 = !ui->line_2->text().isEmpty();
    bool l3 = !ui->line_3->text().isEmpty();
    bool l4 = !ui->line_4->text().isEmpty();
    if(l1 || l2 || l3 || l4)
    {
        std::string lt1 = ui->line_1->text().toStdString();
        std::string lt2 = ui->line_2->text().toStdString();
        std::string lt3 = ui->line_3->text().toStdString();
        std::string lt4 = ui->line_4->text().toStdString();
        std::vector<List<Person*>*>* pervec = nullptr;

        if(l2)
        {
            res->push_back(par->hnum->find(lt2).second);
        }
        else if(l1)
            list = par->name->find(lt1);
        else if(l4)
            list = par->address->find(lt4);
        else
            pervec = par->price->lessOrEqualThan(std::stoul(lt3));

        if(pervec)
            for(auto& i: *(pervec))
            {
                auto el = i->index(0);
                while(el)
                {
                    res->push_back(el->getValue());
                    el = el->next;
                }
            }
        else
        {
            auto el = list->index(0);
            while(el)
            {
                res->push_back(el->getValue());
                el = el->next;
            }
        }
        if(l1)
            for(auto iter = res->begin(); iter != res->end();)
                {
                if((**iter).getName() != lt1)
                    iter = res->erase(iter);
                else
                    iter++;
                }
        if(l3)
            for(auto iter = res->begin(); iter != res->end();)
                {
                if((**iter).getPrice() > std::stoul(lt3))
                    iter = res->erase(iter);
                else
                    iter++;
                }
        if(l4)
            for(auto iter = res->begin(); iter != res->end();)
                {
                if((**iter).getAddress() != lt4)
                    iter = res->erase(iter);
                else
                    iter++;
                }
        return res;
    }
    return nullptr;
}

template<>
std::vector<Note*>* srch<Note, false>(MainWindow* par, Ui::Search* ui)
{
    std::vector<Note*>* res = new std::vector<Note*>;
    List<Note*>* list;

    bool l1 = !ui->line_1->text().isEmpty();
    bool l2 = !ui->line_2->text().isEmpty();
    bool l3 = !ui->line_3->text().isEmpty();
    if(l1 || l2 || l3)
    {
        std::string lt1 = ui->line_1->text().toStdString();
        std::string lt2 = ui->line_2->text().toStdString();
        std::string lt3 = ui->line_3->text().toStdString();

        if(l3)
            list = par->tnum->find(lt3);
        else if(l1)
            list = par->dis->find(lt1);
        else
            list = par->theme->find(lt2);

        auto el = list->index(0);
        while(el)
        {
            res->push_back(el->getValue());
            el = el->next;
        }

        if(l1)
            for(auto iter = res->begin(); iter != res->end();)
            {
                if((**iter).getDiscipline() != lt1)
                    iter = res->erase(iter);
                else
                    iter++;
            }
        if(l2)
            for(auto iter = res->begin(); iter != res->end();)
            {
                if((**iter).getTheme() != lt2)
                    iter = res->erase(iter);
                else
                    iter++;
            }
        if(l3)
            for(auto iter = res->begin(); iter != res->end();)
            {
                if((**iter).getNumber() != lt3)
                    iter = res->erase(iter);
                else
                    iter++;
            }
        return res;
    }
    return nullptr;
}

void Search::on_pushButton_clicked()
{
    MainWindow* par = dynamic_cast<MainWindow*>(this->parent());
    ui->tree->clear();
    if(fl)
    {
        auto vec = srch<Person, true>(par, ui);
        for(auto& i: *vec)
            ui->tree->addTopLevelItem(par->rpersons[i]->clone());
        delete vec;
    }
    else
    {
        auto vec = srch<Note, false>(par, ui);
        for(auto& i: *vec)
            ui->tree->addTopLevelItem(par->rnotes[i]->clone());
        delete vec;
    }
}
