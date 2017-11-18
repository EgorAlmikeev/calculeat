#include "mainwindow.h"

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
    p_screen->setText(displayable_value);
}

void MainWindow::digitButtonPressed(QString digit)
{
    if(displayable_value == "0.0")
        displayable_value = digit;
    else
        displayable_value += digit;
    p_screen->setText(displayable_value);
}

void MainWindow::operationButtonPressed(int operation_id)
{
    if(first_argument == "NULL" && second_argument == "NULL" && displayable_value == "0.0")
        return;

    if(operation == none)
    {
        first_argument = displayable_value;
        operation = operation_id;
    }
    else if(second_argument == "NULL")
        operation = operation_id;
    else
    {
        second_argument = displayable_value;
        calculate();
        operation = operation_id;
        first_argument = displayable_value;
    }

    if(first_argument != "NULL")
    {
        displayable_value = "0.0";
        p_screen->setText(displayable_value);
    }
}

void MainWindow::dotButtonPressed()
{
    if(!displayable_value.contains("."))
        displayable_value.append(".");
    p_screen->setText(displayable_value);
}

void MainWindow::lcdError()
{
    p_screen->setText("Error");
}

void MainWindow::calculate()
{
    static double local_first_argument = 0.0;
    static double local_second_argument = 0.0;

    if(operation == none)
        return;

    local_first_argument = first_argument.toDouble();

    if(second_argument == "NULL")
    {
        local_second_argument = displayable_value.toDouble();
        second_argument = displayable_value;
    }

    switch(operation)
    {
    case plus : local_first_argument += local_second_argument; break;
    case minus : local_first_argument -= local_second_argument; break;
    case division : local_first_argument /= local_second_argument; break;
    case multiplication : local_first_argument *= local_second_argument; break;
    }

    first_argument = QString::number(local_first_argument);
    second_argument = QString::number(local_second_argument);

    displayable_value = first_argument;
    p_screen->setText(displayable_value);
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
