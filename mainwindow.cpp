#include "mainwindow.h"
#include "QDebug"
#include "QThread"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createElements();
    createConnections();
    createDesign();
    emit clearButtonPressed();
}

MainWindow::~MainWindow()
{}

void MainWindow::clearButtonPressed()
{
    displayable_value = "0.0";
    first_argument = "NULL";
    second_argument = "NULL";
    operation = none;
    flag = false;
    p_screen->setText(displayable_value);

    printDebugInfo();
}

void MainWindow::digitButtonPressed(QString digit)
{
    if(displayable_value == "Overflow" || displayable_value == "Error")
        return;

    if(flag)
    {
        flag = false;
        displayable_value = digit;
        second_argument = displayable_value;
    }
    else if(displayable_value == "0.0")
        second_argument = displayable_value = digit;
    else
    {
        displayable_value += digit;
        second_argument = displayable_value;
    }
    p_screen->setText(displayable_value);

    printDebugInfo();
}

void MainWindow::operationButtonPressed(int operation_id)
{
    flag = true;
    first_argument = displayable_value;
    operation = operation_id;

    printDebugInfo();
}

void MainWindow::dotButtonPressed()
{
    if(displayable_value == "Overflow" || displayable_value == "Error")
        return;

    if(!displayable_value.contains("."))
        displayable_value.append(".");
    p_screen->setText(displayable_value);

    printDebugInfo();
}

void MainWindow::lcdError()
{
    displayable_value = "Error";
    p_screen->setText(displayable_value);
    qDebug() << "error generated";
}

void MainWindow::calculate()
{
    if(first_argument == "NULL")
        return;

    double x = first_argument.toDouble();
    double y = second_argument.toDouble();
    double result;

    switch(operation)
    {
    case plus: result = x + y; break;
    case minus: result = x - y; break;
    case multiplication: result = x * y; break;
    case division:
        if(y == 0.0)
        { lcdError(); return; }
        result = x / y; break;
    }

    first_argument = QString::number(result);

    if(first_argument == "inf" || first_argument == "-inf")
    {
        displayable_value = "Overflow";
        p_screen->setText(displayable_value);
        return;
    }

    displayable_value = first_argument;
    p_screen->setText(displayable_value);

    printDebugInfo();
}

void MainWindow::createDesign()
{
    p_central_layout->setMargin(5);
    p_central_layout->setSpacing(5);

    buttons_font.setFamily("Arial");
    buttons_font.setWeight(15);
    buttons_font.setPixelSize(15);

    p_button_plus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p_button_minus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p_button_multiplication->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p_button_division->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p_button_equalse->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p_button_clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p_button_dot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p_screen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    p_button_plus->setFont(buttons_font);
    p_button_minus->setFont(buttons_font);
    p_button_multiplication->setFont(buttons_font);
    p_button_division->setFont(buttons_font);
    p_button_equalse->setFont(buttons_font);
    p_button_clear->setFont(buttons_font);
    p_button_dot->setFont(buttons_font);

    p_central_layout->addWidget(p_screen, 0, 0, 1, 4);
    p_central_layout->addWidget(p_button_clear, 1, 0, 1, 3);

    p_central_layout->addWidget(digits_buttons[0], 5, 0, 1, 2);

    p_central_layout->addWidget(digits_buttons[1], 4, 0, 1, 1);
    p_central_layout->addWidget(digits_buttons[2], 4, 1, 1, 1);
    p_central_layout->addWidget(digits_buttons[3], 4, 2, 1, 1);

    p_central_layout->addWidget(digits_buttons[4], 3, 0, 1, 1);
    p_central_layout->addWidget(digits_buttons[5], 3, 1, 1, 1);
    p_central_layout->addWidget(digits_buttons[6], 3, 2, 1, 1);

    p_central_layout->addWidget(digits_buttons[7], 2, 0, 1, 1);
    p_central_layout->addWidget(digits_buttons[8], 2, 1, 1, 1);
    p_central_layout->addWidget(digits_buttons[9], 2, 2, 1, 1);

    p_central_layout->addWidget(p_button_division, 1, 3, 1, 1);
    p_central_layout->addWidget(p_button_multiplication, 2, 3, 1, 1);
    p_central_layout->addWidget(p_button_minus, 3, 3, 1, 1);
    p_central_layout->addWidget(p_button_plus, 4, 3, 1, 1);
    p_central_layout->addWidget(p_button_equalse, 5, 3, 1, 1);
    p_central_layout->addWidget(p_button_dot, 5, 2, 1, 1);

    p_central_layout->setRowStretch(0, 2);
    p_central_layout->setRowStretch(1, 1);
    p_central_layout->setRowStretch(2, 1);
    p_central_layout->setRowStretch(3, 1);
    p_central_layout->setRowStretch(4, 1);
    p_central_layout->setRowStretch(5, 1);

    p_central_layout->setColumnStretch(0, 1);
    p_central_layout->setColumnStretch(1, 1);
    p_central_layout->setColumnStretch(2, 1);
    p_central_layout->setColumnStretch(3, 1);
}

void MainWindow::createElements()
{
    p_central_widget = new QWidget;
    p_central_layout = new QGridLayout;
    p_central_widget->setLayout(p_central_layout);
    setCentralWidget(p_central_widget);

    p_screen = new QLineEdit;
    p_screen->setReadOnly(true);
//    p_screen->setPlaceholderText("sample text");

    p_button_plus = new QPushButton("+");
    p_button_minus = new QPushButton("-");
    p_button_multiplication = new QPushButton("x");
    p_button_division = new QPushButton("÷");
    p_button_equalse = new QPushButton("=");
    p_button_clear = new QPushButton("Clear");
    p_button_dot = new QPushButton(".");
}

void MainWindow::createConnections()
{
    digit_buttons_mapper = new QSignalMapper;
    operation_buttons_mapper = new QSignalMapper;

    for(int i = 0; i < 10; ++i)
    {
        digits_buttons[i] = new QPushButton(QString::number(i));
        digits_buttons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        digits_buttons[i]->setFont(buttons_font);

        digit_buttons_mapper->setMapping(digits_buttons[i], QString::number(i));
        connect(digits_buttons[i], SIGNAL(clicked()), digit_buttons_mapper, SLOT(map()), Qt::UniqueConnection);
    }

    connect(digit_buttons_mapper, SIGNAL(mapped(QString)), this, SLOT(digitButtonPressed(QString)), Qt::UniqueConnection);


    connect(p_button_clear, SIGNAL(clicked()), this, SLOT(clearButtonPressed()), Qt::UniqueConnection);
    connect(p_button_equalse, SIGNAL(clicked()), this, SLOT(calculate()), Qt::UniqueConnection);
    connect(p_button_dot, SIGNAL(clicked()), this, SLOT(dotButtonPressed()), Qt::UniqueConnection);

    connect(p_button_plus, SIGNAL(clicked()), operation_buttons_mapper, SLOT(map()), Qt::UniqueConnection);
    connect(p_button_minus, SIGNAL(clicked()), operation_buttons_mapper, SLOT(map()), Qt::UniqueConnection);
    connect(p_button_multiplication, SIGNAL(clicked()), operation_buttons_mapper, SLOT(map()), Qt::UniqueConnection);
    connect(p_button_division, SIGNAL(clicked()), operation_buttons_mapper, SLOT(map()), Qt::UniqueConnection);

    operation_buttons_mapper->setMapping(p_button_plus, operations::plus);
    operation_buttons_mapper->setMapping(p_button_minus, operations::minus);
    operation_buttons_mapper->setMapping(p_button_multiplication, operations::multiplication);
    operation_buttons_mapper->setMapping(p_button_division, operations::division);

    connect(operation_buttons_mapper, SIGNAL(mapped(int)), this, SLOT(operationButtonPressed(int)), Qt::UniqueConnection);
}

void MainWindow::printDebugInfo()
{
    QString local_operation =   (operation == plus) ? "+" :
                                (operation == minus) ? "-" :
                                (operation == multiplication) ? "*" :
                                (operation == division) ? "/" : "none";

    qDebug() << "=========================================";
    qDebug() << "screen          : " << displayable_value;
    qDebug() << "first argument  : " << first_argument;
    qDebug() << "second argument : " << second_argument;
    qDebug() << "operation       : " << local_operation;
    qDebug() << "flag            : " << flag;
}
