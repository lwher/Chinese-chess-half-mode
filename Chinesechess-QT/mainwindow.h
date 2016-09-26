#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "classes.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_one_one_clicked();

    void on_one_two_clicked();

    void on_one_three_clicked();

    void on_one_four_clicked();

    void on_one_five_clicked();

    void on_one_six_clicked();

    void on_one_seven_clicked();

    void on_one_eight_clicked();

    void on_two_one_clicked();

    void on_two_two_clicked();

    void on_two_three_clicked();

    void on_two_four_clicked();

    void on_two_five_clicked();

    void on_two_six_clicked();

    void on_two_seven_clicked();

    void on_two_eight_clicked();

    void on_three_one_clicked();

    void on_three_two_clicked();

    void on_three_three_clicked();

    void on_three_four_clicked();

    void on_three_five_clicked();

    void on_three_six_clicked();

    void on_three_seven_clicked();

    void on_three_eight_clicked();

    void on_four_one_clicked();

    void on_four_two_clicked();

    void on_four_three_clicked();

    void on_four_four_clicked();

    void on_four_five_clicked();

    void on_four_six_clicked();

    void on_four_seven_clicked();

    void on_four_eight_clicked();

    void on_close_clicked();

    void on_re_start_clicked();

    void on_re_choose_clicked();

    void on_regret_clicked();

    void on_pvsp_clicked();

    void on_pvsai_clicked();

    void on_AI_hard_button_clicked();

private:
    Ui::MainWindow *ui;

    void show_chess(int x, int y, int id, int ty);

    void Solve_operation(int x, int y);

    void check_over();

};

#endif // MAINWINDOW_H
