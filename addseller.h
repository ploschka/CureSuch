#ifndef ADDSELLER_H
#define ADDSELLER_H

#include <QDialog>

namespace Ui {
class AddSeller;
}

class AddSeller : public QDialog
{
    Q_OBJECT

public:
    explicit AddSeller(QWidget *parent = nullptr);
    ~AddSeller();

private:
    Ui::AddSeller *ui;
};

#endif // ADDSELLER_H
