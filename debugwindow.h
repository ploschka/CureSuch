#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DebugWindow;
}

class DebugWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DebugWindow(QWidget *parent = nullptr);
    ~DebugWindow();

private slots:

    void on_AddressTree_clicked();

    void on_DispTree_clicked();

    void on_NameTree_clicked();

    void on_NumberTable_clicked();

    void on_NumberTree_clicked();

    void on_PriceTree_clicked();

    void on_ThemeTree_clicked();

private:
    Ui::DebugWindow *ui;
    MainWindow* par;
};

#endif // DEBUGWINDOW_H
