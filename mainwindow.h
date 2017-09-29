#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QLineEdit>
#include <QFont>

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

    QPushButton *p_button_plus;
    QPushButton *p_button_minus;
    QPushButton *p_button_multiplication;
    QPushButton *p_button_division;
    QPushButton *p_button_equalse;
    QPushButton *p_button_clear;
    QPushButton *p_button_dot;

    enum operations {plus, minus, multiplication, division, none};

    operations operation;

    QSignalMapper *digit_buttons_mapper;
    QSignalMapper *operation_buttons_mapper;

    double next_number;
    double result;
    double first;
    double second;

public slots:

    void slotClearButtonPressed();
    void slotDigitButtonPressed(int digit);
    void slotOperationButtonPressed(int operation_id);
    void slotEqualButtonPressed();
    void slotDotButtonPressed();
    void LCDError();
};

#endif // MAINWINDOW_H
