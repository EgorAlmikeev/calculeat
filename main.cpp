#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setPalette(QPalette(QColor(Qt::white)));
    w.setAutoFillBackground(true);
    w.setFixedSize(230, 300);
    w.setWindowTitle("Calculeat");
    w.show();

    return a.exec();
}
