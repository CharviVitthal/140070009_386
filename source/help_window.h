#ifndef HELP_WINDOW_H
#define HELP_WINDOW_H

#include <QMainWindow>

namespace Ui {
class Help_Window;
}

class Help_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Help_Window(QWidget *parent = 0);
    ~Help_Window();

private:
    Ui::Help_Window *ui;
};

#endif // HELP_WINDOW_H
