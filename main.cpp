#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Обмен конспектами");
    QIcon ico(":/res/icons/notebook_icon-icons.com_49834.ico");
    w.setWindowIcon(ico);
    w.show();
    return a.exec();
}
