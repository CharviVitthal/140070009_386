#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "syntax_checker.cpp"
#include "elementary_functions.cpp"
#include "final_rpn_tokenizer.cpp"
#include "newton_raphson.cpp"
#include <sstream>
#include "help_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString d_start=ui->domain_start->text();
    QString d_end=ui->domain_end->text();
    string d_start1=d_start.toStdString();
    string d_end1=d_end.toStdString();
    double start,end;
    if(!d_start1.empty()&&!d_end1.empty()) {
        if(start<-1000||end>1000) {
            QMessageBox::critical(this, tr("Error"), tr("Enter domain in range -1000 to 1000 only"));
        }
        start=atof(&d_start1[0]);
        end=atof(&d_end1[0]);
    }
    else {
        start=-1000;
        end=1000;
    }


    QString s=ui->equation_line->text();
    QString var=ui->variable_line->text();

    string def_var=var.toStdString();
    if(def_var.empty()) {
        def_var="x";
    }
    string str=s.toStdString();
    str=remove_whitespaces(str);
    str=convert_brackets(str);
    vector<string> expression=tokenizer(str);
    expression=convert_variable(expression, def_var);
    expression=equation_to_function(expression);
    if(check_syntax(expression))
    {
        vector<string> expr=get_rpn_expression(expression);
        recursive_solve(expr, start, end);
        sort(roots.rbegin(),roots.rend());
        roots=remove_repeated_roots(roots);
        ostringstream oss1;
        oss1<<roots.size();
        ui->lineEdit_4->setText(oss1.str().c_str());
        ostringstream oss;
        oss<<roots[0];
        for(int i=1;i<roots.size();i++)
        {
            oss<<", "<<roots[i];
        }
        ui->textEdit->setText(oss.str().c_str());
        roots.clear();

    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Syntax Error"));
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    Help_Window *hw = new Help_Window(this);
    hw->show();
}
