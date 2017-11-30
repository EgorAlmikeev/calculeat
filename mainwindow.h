#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QLineEdit>
#include <QFont>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget *p_central_widget;
    QGridLayout *p_central_layout;
    QLineEdit *p_screen;

    QFont buttons_font;

    QPushButton *digits_buttons [10];

    QPushButton *p_button_percent;
    QPushButton *p_button_plus_minus;
    QPushButton *p_button_plus;
    QPushButton *p_button_minus;
    QPushButton *p_button_multiplication;
    QPushButton *p_button_division;
    QPushButton *p_button_equalse;
    QPushButton *p_button_clear;
    QPushButton *p_button_dot;

    enum operations {plus, minus, multiplication, division, none};

    QSignalMapper *digit_buttons_mapper;
    QSignalMapper *operation_buttons_mapper;

    QString displayable_value = "NULL";
    QString first_argument = "0.0";
    QString second_argument = "0.0";
    int operation = none;
    bool flag;

    void createElements();
    void createDesign();
    void createConnections();
    void printDebugInfo();

private slots:

    void clearButtonPressed();
    void digitButtonPressed(QString digit);
    void operationButtonPressed(int operation_id);
    void dotButtonPressed();
    void percentButtonPressed();
    void plusMinusButtonPressed();
    void lcdError();
    void calculate();
};

#endif // MAINWINDOW_H
