#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>

namespace Ui {
class Calculator;
}

class Calculator : public QDialog
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    double firstNumber;
    bool userIsTypingSecondNumber;

private slots:

    void buttonPressed();

    void on_ButtonDot_released();
    void on_ButtonClear_released();
    void binaryOperationPressed();
    void on_ButtonEqualto_released();
    void on_ButtonBackspace_released();
    void on_pushButton_clicked();
};

#endif // CALCULATOR_H
