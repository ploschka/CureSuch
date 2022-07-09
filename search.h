#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr, QString title = "");
    ~Search();

    void ggg(QTreeWidget* wgg);

private:
    Ui::Search *ui;
    QTreeWidget* wg;
};

#endif // SEARCH_H
