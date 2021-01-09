#include "calculator.h"
#include "ui_calculator.h"
#include<QDebug>

Calculator::Calculator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Popup);

    userIsTypingSecondNumber=false;


    connect(ui->Button0,SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->Button1,SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->Button2,SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->Button3,SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->Button4,SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->Button5,SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->Button6,SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->Button7,SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->Button8,SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->Button9,SIGNAL(released()),this,SLOT(buttonPressed()));

    connect(ui->ButtonMod,SIGNAL(released()),this,SLOT(binaryOperationPressed()));
    connect(ui->ButtonDivide,SIGNAL(released()),this,SLOT(binaryOperationPressed()));
    connect(ui->ButtonMultiply,SIGNAL(released()),this,SLOT(binaryOperationPressed()));
    connect(ui->ButtonMinus,SIGNAL(released()),this,SLOT(binaryOperationPressed()));
    connect(ui->ButtonPlus,SIGNAL(released()),this,SLOT(binaryOperationPressed()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::buttonPressed()
{
    QPushButton *button=(QPushButton *)sender();
    double labelNumber;
    QString newLabel;
    if((ui->ButtonPlus->isChecked() || ui->ButtonMinus->isChecked() || ui->ButtonMultiply->isChecked() || ui->ButtonDivide->isChecked() || ui->ButtonMod->isChecked()) && !userIsTypingSecondNumber)
    {
        labelNumber=button->text().toDouble();
        userIsTypingSecondNumber=true;
        newLabel=QString::number(labelNumber,'g',15);
    }
    else
    {
        if(ui->displayText->text().contains(".") && button->text()=="0")
        {
            newLabel=ui->displayText->text()+button->text();

        }
        else
        {
            labelNumber=(ui->displayText->text()+button->text()).toDouble();
            newLabel=QString::number(labelNumber,'g',15);
        }
    }

    ui->displayText->setText(newLabel);


}

void Calculator::on_ButtonDot_released()
{
    this->ui->displayText->setText(this->ui->displayText->text()+ ".");
}

void Calculator::on_ButtonClear_released()
{
    this->ui->ButtonMod->setChecked(false);
    this->ui->ButtonDivide->setChecked(false);
    this->ui->ButtonMultiply->setChecked(false);
    this->ui->ButtonMinus->setChecked(false);
    this->ui->ButtonPlus->setChecked(false);
    userIsTypingSecondNumber=false;

    this->ui->displayText->setText(0);
}

void Calculator::binaryOperationPressed()
{
    QPushButton *button=(QPushButton *)sender();
    firstNumber=this->ui->displayText->text().toDouble();
    button->setChecked(true);

}

void Calculator::on_ButtonEqualto_released()
{
    double labelNumber,secondNumber;
    QString newLabel;

    secondNumber=this->ui->displayText->text().toDouble();

    if(ui->ButtonMod->isChecked())
    {
        labelNumber=(int)firstNumber%(int)secondNumber;
        newLabel=QString::number(labelNumber,'g',15);
        this->ui->displayText->setText(newLabel);
        this->ui->ButtonMod->setChecked(false);
    }
    if(ui->ButtonDivide->isChecked())
    {
        labelNumber=firstNumber/secondNumber;
        newLabel=QString::number(labelNumber,'g',15);
        this->ui->displayText->setText(newLabel);
        this->ui->ButtonDivide->setChecked(false);
    }
    if(ui->ButtonMultiply->isChecked())
    {
        labelNumber=firstNumber*secondNumber;
        newLabel=QString::number(labelNumber,'g',15);
        this->ui->displayText->setText(newLabel);
        this->ui->ButtonMultiply->setChecked(false);
    }
    if(ui->ButtonMinus->isChecked())
    {
        labelNumber=firstNumber-secondNumber;
        newLabel=QString::number(labelNumber,'g',15);
        this->ui->displayText->setText(newLabel);
        this->ui->ButtonMinus->setChecked(false);
    }
    if(ui->ButtonPlus->isChecked())
    {
        labelNumber=firstNumber+secondNumber;
        newLabel=QString::number(labelNumber,'g',15);
        this->ui->displayText->setText(newLabel);
        this->ui->ButtonPlus->setChecked(false);
    }
    userIsTypingSecondNumber=false;

}

void Calculator::on_ButtonBackspace_released()
{
    QString newLabel;
    newLabel=this->ui->displayText->text();
    if(newLabel.size()>0) newLabel.remove(newLabel.size()-1,1);
    this->ui->displayText->setText(newLabel);
}

void Calculator::on_pushButton_clicked()
{
    this->hide();
}
