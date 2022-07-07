#ifndef ADDNOTE_H
#define ADDNOTE_H

#include <QDialog>

namespace Ui {
class AddNote;
}

class AddNote : public QDialog
{
    Q_OBJECT

public:
    explicit AddNote(QWidget *parent = nullptr);
    ~AddNote();

private:
    Ui::AddNote *ui;
};

#endif // ADDNOTE_H
