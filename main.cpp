#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString styleSheet = "QWidget { font-size: 20px; }";
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
