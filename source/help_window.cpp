#include "help_window.h"
#include "ui_help_window.h"

Help_Window::Help_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Help_Window)
{
    ui->setupUi(this);
}

Help_Window::~Help_Window()
{
    delete ui;
}
