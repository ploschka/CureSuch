#ifndef REPORT_H
#define REPORT_H

#include <QDialog>

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();

private slots:
    void on_SaveButton_clicked();

    void on_ReportButton_clicked();

private:
    Ui::Report *ui;
};

#endif // REPORT_H
