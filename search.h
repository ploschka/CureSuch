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
    explicit Search(QWidget *parent = nullptr, QString title = "", QTreeWidget* widget = nullptr);
    ~Search();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Search *ui;
    QTreeWidget* wg;
    bool fl = false;
};

#endif // SEARCH_H
