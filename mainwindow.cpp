#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->button_0->setProperty("id", 0);
    ui->button_1->setProperty("id", 1);
    ui->button_2->setProperty("id", 2);
    ui->button_3->setProperty("id", 3);
    ui->button_4->setProperty("id", 4);
    ui->button_5->setProperty("id", 5);
    ui->button_6->setProperty("id", 6);
    ui->button_7->setProperty("id", 7);
    ui->button_8->setProperty("id", 8);
    ui->button_9->setProperty("id", 9);
    ui->button_decimal->setProperty("id", 10);
    ui->button_add->setProperty("action", 0);
    ui->button_sub->setProperty("action", 1);
    ui->button_mul->setProperty("action", 2);
    ui->button_div->setProperty("action", 3);
    ui->button_equals->setProperty("action", 4);
    ui->button_clear->setProperty("action", 5);
    ui->button_all_clear->setProperty("action", 6);

    QObject::connect(ui->button_0, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_1, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_2, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_3, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_4, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_5, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_6, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_7, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_8, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_9, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));
    QObject::connect(ui->button_decimal, SIGNAL(clicked()), this, SLOT(onNumericButtonClicked()));

    QObject::connect(ui->button_add, SIGNAL(clicked()), this, SLOT(onActionButtonClicked()));
    QObject::connect(ui->button_sub, SIGNAL(clicked()), this, SLOT(onActionButtonClicked()));
    QObject::connect(ui->button_mul, SIGNAL(clicked()), this, SLOT(onActionButtonClicked()));
    QObject::connect(ui->button_div, SIGNAL(clicked()), this, SLOT(onActionButtonClicked()));
    QObject::connect(ui->button_equals, SIGNAL(clicked()), this, SLOT(onActionButtonClicked()));
    QObject::connect(ui->button_clear, SIGNAL(clicked()), this, SLOT(onActionButtonClicked()));
    QObject::connect(ui->button_all_clear, SIGNAL(clicked()), this, SLOT(onActionButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNumericButtonClicked(){
    QVariant property = sender()->property("id");
    if(property.isValid()){
        int id = property.toInt();
        if(ui->label->text().count() == 10) return;
        else if(id == 10) {
                if(!ui->label->text().contains(".")) {
                    ui->label->setText(ui->label->text() + ".");
                }
        }
        else if((ui->label->text().length() == 1) && (ui->label->text().back() == "0")) {
            ui->label->setText(QString::number(id));
        }
        else if(reset_view_) {
            ui->label->setText("");
            ui->label->setText(ui->label->text() + QString::number(id));
            reset_view_ = false;
        }
        else if (!reset_view_) {
            ui->label->setText(ui->label->text() + QString::number(id));
        }
        component_ = ui->label->text().toDouble();
    }else qDebug() << "Invalid property";
}

void MainWindow::onActionButtonClicked(){
    QVariant property = sender()->property("action");
    if(property.isValid()){
        int action = property.toInt();
        if(action == 5) {
            if(equals_pressed_)
                return;
            if(ui->label->text().size() > 1) ui->label->setText(ui->label->text().remove(ui->label->text().size()-1,1));
            else ui->label->setNum(0);
            return;
        }
        else if((action == 0) || (action == 1) || (action == 2) ||(action == 3)){
            if(!equals_pressed_)
                calculate(action_);
            ui->label->setText(QString::number(result_));
            reset_view_ = true;
            equals_pressed_ = false;
            action_ = action;
        }
        else if(action == 4){
            calculate(action_);
            ui->label->setText(QString::number(result_));
            reset_view_ = true;
            equals_pressed_ = true;
        }
        else if(action == 6){
            result_= component_= 0;
            ui->label->setText(QString::number(result_));
            reset_view_ = false;
            equals_pressed_ = false;
        }
    }
}

void MainWindow::calculate(int action){
    if(action == 0) result_+=component_;
    else if(action == 1) result_-=component_;
    else if(action == 2) result_*=component_;
    else if(action == 3){
        if(component_ == 0) result_ = 0;
        else result_/=component_;
    }
}
