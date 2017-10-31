#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setPalette(QPalette(QColor(Qt::white)));
    w.setAutoFillBackground(true);
    w.setFixedSize(230, 300);
    w.setWindowTitle("Calculeat");

    w.setStyleSheet(
                "MainWindow {background-color : rgba(25, 55, 155, 0.5);}"
                "QPushButton {background-color : rgba(255, 255, 255, 0.5); border : 1px solid black; border-radius : 5px;}"
                );

    return a.exec();
}
