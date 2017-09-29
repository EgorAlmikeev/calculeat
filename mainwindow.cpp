#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    p_central_widget = new QWidget;
    p_central_layout = new QGridLayout;
    p_central_widget->setLayout(p_central_layout);
    setCentralWidget(p_central_widget);

    buttons_font.setFamily("Arial");
    buttons_font.setWeight(15);
    buttons_font.setPixelSize(15);

    p_screen = new QLineEdit;

    digit_buttons_mapper = new QSignalMapper;
    operation_buttons_mapper = new QSignalMapper;

    for(int i = 0; i < 10; ++i)
    {
        digits_buttons[i] = new QPushButton(QString::number(i));
        digits_buttons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        digits_buttons[i]->setFont(buttons_font);

        digit_buttons_mapper->setMapping(digits_buttons[i], i);
        connect(digits_buttons[i], SIGNAL(clicked()), digit_buttons_mapper, SLOT(map()), Qt::UniqueConnection);
    }

    connect(digit_buttons_mapper, SIGNAL(mapped(int)), this, SLOT(slotDigitButtonPressed(int)), Qt::UniqueConnection);

    p_button_plus = new QPushButton("+");
    p_button_minus = new QPushButton("-");
    p_button_multiplication = new QPushButton("x");
    p_button_division = new QPushButton("÷");
    p_button_equalse = new QPushButton("=");
    p_button_clear = new QPushButton("Clear");
    p_button_dot = new QPushButton(".");

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


    connect(p_button_clear, SIGNAL(clicked()), this, SLOT(slotClearButtonPressed()), Qt::UniqueConnection);
    connect(p_button_equalse, SIGNAL(clicked()), this, SLOT(slotEqualButtonPressed()), Qt::UniqueConnection);

    connect(p_button_plus, SIGNAL(clicked()), operation_buttons_mapper, SLOT(map()), Qt::UniqueConnection);
    connect(p_button_minus, SIGNAL(clicked()), operation_buttons_mapper, SLOT(map()), Qt::UniqueConnection);
    connect(p_button_multiplication, SIGNAL(clicked()), operation_buttons_mapper, SLOT(map()), Qt::UniqueConnection);
    connect(p_button_division, SIGNAL(clicked()), operation_buttons_mapper, SLOT(map()), Qt::UniqueConnection);

    operation_buttons_mapper->setMapping(p_button_plus, 1);
    operation_buttons_mapper->setMapping(p_button_minus, 2);
    operation_buttons_mapper->setMapping(p_button_multiplication, 3);
    operation_buttons_mapper->setMapping(p_button_division, 4);

    connect(operation_buttons_mapper, SIGNAL(mapped(int)), this, SLOT(slotOperationButtonPressed(int)), Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{}

void MainWindow::slotClearButtonPressed()
{
    p_screen->setText(QString::number(0));
    next_number = 0;
    result = 0;
    first = 0;
    second = 0;
}

void MainWindow::slotDigitButtonPressed(int digit)
{
    if(digit == 0 && p_screen->text().isEmpty())
        return;

    if(p_screen->text().contains(p_button_dot->text()))
    {
        for(int i = p_screen->text().indexOf(p_button_dot->text()); i < p_screen->text().length(); ++i)
            digit /= 10;
        next_number += digit;
    }
    else
    {
        next_number *= 10.0;
        next_number += digit;
    }

    p_screen->setText(QString::number(next_number));
}

void MainWindow::slotOperationButtonPressed(int operation_id)
{
    if(!first)
        first = next_number;
    next_number = 0;

    switch(operation_id)
    {
    case 1 : operation = plus; break;
    case 2 : operation = minus; break;
    case 3 : operation = multiplication; break;
    case 4 : operation = division; break;
    }
}

void MainWindow::slotEqualButtonPressed()
{
    second = next_number;

    switch(operation)
    {
    case plus : result = first + second; break;
    case minus : result = first - second; break;
    case multiplication : result = first * second; break;
    case division : if(second == 0) { LCDError(); break; } result = first / second; break;
    case none : break;
    }

    p_screen->setText(QString::number(result));
    first = result;

    if(result == 0)
        emit slotClearButtonPressed();
    if(result > 99999)
        LCDError();
}

void MainWindow::slotDotButtonPressed()
{}

void MainWindow::LCDError()
{
    p_screen->setText("Error");
}
