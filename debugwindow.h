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

private:
    Ui::DebugWindow *ui;
    MainWindow* par;

private slots:

    void showAddressTree();
    void showDispTree();
    void showNameTree();
    void showNumberTree();
    void showPriceTree();
    void showThemeTree();
    void showNumberTable();};

#endif // DEBUGWINDOW_H
