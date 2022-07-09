#ifndef ADDSELLER_H
#define ADDSELLER_H

#include <QDialog>
#include "Person.h"

namespace Ui {
class AddSeller;
}

class AddSeller : public QDialog
{
    Q_OBJECT

public:
    explicit AddSeller(QWidget *parent = nullptr);
    ~AddSeller();
    Person* getNewSeller();

private slots:

    void on_AddButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::AddSeller *ui;
    Person* newSeller;
};

#endif // ADDSELLER_H
