#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNumericButtonClicked();                          // slot activated when numeric button is pressed
    void onActionButtonClicked();                           // slot activated when action button is pressed

private:
    Ui::MainWindow *ui;
    double component_, result_, action_ = 0;                // component of equation, result of equation,
                                                            // action executet when action button is pressed
    bool reset_view_ = false;                               // reset view flag (activated when action button is pressed)
    bool equals_pressed_ = false;                           // equals pressed flag (activated when equals button is pressed)
    void calculate(int action);                             // calculate method (perform calculation depends on action button)
};
#endif // MAINWINDOW_H
