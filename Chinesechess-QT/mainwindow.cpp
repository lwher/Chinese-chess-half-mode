#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include "classes.h"
#include <ctime>
#include <QTimer>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::check_over(){
    if(is_over()){
        over = true;
        for(int i = 1; i <= 4; ++i){
            for(int j = 1; j <= 8; ++j){
                if(is_back[i][j]){
                    show_chess(i, j, Map[i][j], 0);
                    is_back[i][j] = false;
                }
            }
        }
    }
    else if(mode && nowturn == AI_id){
        int x, y, xx, yy;
        Sleep(100);
        if(!AI_kind) AI_make_decision(x, y, xx, yy);
        else AI_hard_make_decision(x, y, xx, yy, AI_id);
        ++x; ++y; ++xx; ++yy;
        if(xx == x && yy == y) Solve_operation(x, y);
        else{
            Solve_operation(x, y);
            Solve_operation(xx, yy);
        }
        if(is_over()){
            over = true;
            for(int i = 1; i <= 4; ++i){
                for(int j = 1; j <= 8; ++j){
                    if(is_back[i][j]){
                        show_chess(i, j, Map[i][j], 0);
                        is_back[i][j] = false;
                    }
                }
            }
        }
    }

}

void MainWindow::Solve_operation(int nowx, int nowy){
    if(over) return;
    if(!status && Map[nowx][nowy] == 14){
        QMessageBox::about(NULL, "提示", "该格无棋子！");
        return;
    }
    if(is_back[nowx][nowy]){// click back_chess
        if(status){
            QMessageBox::about(NULL, "提示", "已选中棋子！");
            return;
        }
        if(rtop > 0){
            if(record[rtop].lastx == record[rtop].nx && record[rtop].lasty == record[rtop].ny){
                show_chess(record[rtop].lastx, record[rtop].lasty, Map[record[rtop].lastx][record[rtop].lasty], 0);
            }
            else{
                show_chess(record[rtop].lastx, record[rtop].lasty, Map[record[rtop].lastx][record[rtop].lasty], 0);
                show_chess(record[rtop].nx, record[rtop].ny, Map[record[rtop].nx][record[rtop].ny], 0);
            }
        }
        show_chess(nowx, nowy, Map[nowx][nowy], 1);
        //QMessageBox::about(NULL, "提示", "showed！");
        if(lastX == -1){
            nowturn = (belong(Map[nowx][nowy]) ^ 1);
            if(mode){
                if(!AI_kind) AI_start(nowturn); //P vs AI;
                else AI_hard_start();
                AI_id = nowturn;
            }
            lastX = 0;
        }
        else nowturn ^= 1;
        if(mode){
            if(!AI_kind) AI_change(nowx - 1, nowy - 1, nowx - 1, nowy - 1, belong(Map[nowx][nowy]), Map[nowx][nowy] % 7);
            else AI_hard_change(nowx - 1, nowy - 1, nowx - 1, nowy - 1, belong(Map[nowx][nowy]), Map[nowx][nowy] % 7);
        }
        status = false; is_back[nowx][nowy] = false;
        record[++rtop] = Record(nowx, nowy, nowx, nowy, 15, 0);
        return;
    }
    if(!status){ //first click
        if(nowturn != belong(Map[nowx][nowy])){
            QMessageBox::about(NULL, "提示", "此为对方棋子！");
            return;
        }
        if(rtop > 0){
            if(record[rtop].lastx == record[rtop].nx && record[rtop].lasty == record[rtop].ny){
                show_chess(record[rtop].lastx, record[rtop].lasty, Map[record[rtop].lastx][record[rtop].lasty], 0);
            }
            else{
                show_chess(record[rtop].lastx, record[rtop].lasty, Map[record[rtop].lastx][record[rtop].lasty], 0);
                show_chess(record[rtop].nx, record[rtop].ny, Map[record[rtop].nx][record[rtop].ny], 0);
            }
        }
        show_chess(nowx, nowy, Map[nowx][nowy], 1);
        lastX = nowx; lastY = nowy; status = true;
        return;
    }
    else{ // second click
        if(nowturn == belong(Map[nowx][nowy]) && Map[nowx][nowy] != 14){
            show_chess(lastX, lastY, Map[lastX][lastY], 0);
            lastX = nowx; lastY = nowy;
            show_chess(nowx, nowy, Map[nowx][nowy], 1);
            return;
        }
        if(Can_move(lastX, lastY, nowx, nowy)){
            if(mode){
                if(!AI_kind)
                    AI_change(lastX - 1, lastY - 1, nowx - 1, nowy - 1, belong(Map[lastX][lastY]), Map[lastX][lastY] % 7);
                else
                    AI_hard_change(lastX - 1, lastY - 1, nowx - 1, nowy - 1, belong(Map[lastX][lastY]), Map[lastX][lastY] % 7);
            }
            show_chess(lastX, lastY, 14, 1);
            show_chess(nowx, nowy, Map[lastX][lastY], 1);
            record[++rtop] = Record(lastX, lastY, nowx, nowy, Map[lastX][lastY], Map[nowx][nowy]);
            Map[nowx][nowy] = Map[lastX][lastY];
            Map[lastX][lastY] = 14;
            nowturn ^= 1; status = false;

        }
        else{
            QMessageBox::about(NULL, "提示", "错误的操作！");
            return;
        }
    }
}

void MainWindow::on_one_one_clicked(){
    Solve_operation(1, 1);
    check_over();
}

void MainWindow::on_one_two_clicked(){
    Solve_operation(1, 2);
    check_over();
}

void MainWindow::on_one_three_clicked(){
    Solve_operation(1, 3);
    check_over();
}

void MainWindow::on_one_four_clicked(){
    Solve_operation(1, 4);
    check_over();
}

void MainWindow::on_one_five_clicked(){
    Solve_operation(1, 5);
    check_over();
}

void MainWindow::on_one_six_clicked(){
    Solve_operation(1, 6);
    check_over();
}

void MainWindow::on_one_seven_clicked(){
    Solve_operation(1, 7);
    check_over();
}

void MainWindow::on_one_eight_clicked(){
    Solve_operation(1, 8);
    check_over();
}

void MainWindow::on_two_one_clicked(){
    Solve_operation(2, 1);
    check_over();
}

void MainWindow::on_two_two_clicked(){
    Solve_operation(2, 2);
    check_over();
}

void MainWindow::on_two_three_clicked(){
    Solve_operation(2, 3);
    check_over();
}

void MainWindow::on_two_four_clicked(){
    Solve_operation(2, 4);
    check_over();
}

void MainWindow::on_two_five_clicked(){
    Solve_operation(2, 5);
    check_over();
}

void MainWindow::on_two_six_clicked(){
    Solve_operation(2, 6);
    check_over();
}

void MainWindow::on_two_seven_clicked(){
    Solve_operation(2, 7);
    check_over();
}

void MainWindow::on_two_eight_clicked(){
    Solve_operation(2, 8);
    check_over();
}

void MainWindow::on_three_one_clicked(){
    Solve_operation(3, 1);
    check_over();
}

void MainWindow::on_three_two_clicked(){
    Solve_operation(3, 2);
    check_over();
}

void MainWindow::on_three_three_clicked(){
    Solve_operation(3, 3);
    check_over();
}

void MainWindow::on_three_four_clicked(){
    Solve_operation(3, 4);
    check_over();
}

void MainWindow::on_three_five_clicked(){
    Solve_operation(3, 5);
    check_over();
}

void MainWindow::on_three_six_clicked(){
    Solve_operation(3, 6);
    check_over();
}

void MainWindow::on_three_seven_clicked(){
    Solve_operation(3, 7);
    check_over();
}

void MainWindow::on_three_eight_clicked(){
    Solve_operation(3, 8);
    check_over();
}

void MainWindow::on_four_one_clicked(){
    Solve_operation(4, 1);
    check_over();
}

void MainWindow::on_four_two_clicked(){
    Solve_operation(4, 2);
    check_over();
}

void MainWindow::on_four_three_clicked(){
    Solve_operation(4, 3);
    check_over();
}

void MainWindow::on_four_four_clicked(){
    Solve_operation(4, 4);
    check_over();
}

void MainWindow::on_four_five_clicked(){
    Solve_operation(4, 5);
    check_over();
}

void MainWindow::on_four_six_clicked(){
    Solve_operation(4, 6);
    check_over();
}

void MainWindow::on_four_seven_clicked(){
    Solve_operation(4, 7);
    check_over();
}

void MainWindow::on_four_eight_clicked(){
    Solve_operation(4, 8);
    check_over();
}

void MainWindow::on_close_clicked(){
    close();
}

void MainWindow::on_re_start_clicked(){
    set_start();
    for(int i = 1; i <= 4; ++i)
        for(int j = 1; j <= 8; ++j)
            show_chess(i, j, 15, 0);
}

void MainWindow::on_re_choose_clicked(){
    if(status){
        show_chess(lastX, lastY, Map[lastX][lastY], 0);
        status = false;
    }
}

void MainWindow::on_regret_clicked(){
    if(over){
        QMessageBox::about(NULL, "提示", "胜负已分！");
        return;
    }
    if(!rtop){
        QMessageBox::about(NULL, "提示", "你在逗我！？");
        return;
    }
    if(status){
        QMessageBox::about(NULL, "提示", "已选中棋子！");
        return;
    }
    if(mode){
        QMessageBox::about(NULL, "提示", "AI酱不许你悔棋！");
        return;
    }
    if(record[rtop].lastx == record[rtop].nx && record[rtop].lasty == record[rtop].ny){
        is_back[record[rtop].lastx][record[rtop].lasty] = true;
        show_chess(record[rtop].lastx, record[rtop].lasty, 15, 0);
        nowturn ^= 1; --rtop;
    }
    else{
        Map[record[rtop].lastx][record[rtop].lasty] = record[rtop].lastp;
        Map[record[rtop].nx][record[rtop].ny] = record[rtop].np;
        show_chess(record[rtop].lastx, record[rtop].lasty, record[rtop].lastp, 0);
        show_chess(record[rtop].nx, record[rtop].ny, record[rtop].np, 0);
        nowturn ^= 1; --rtop;
    }
    if(rtop > 0){
        if(record[rtop].lastx == record[rtop].nx && record[rtop].lasty == record[rtop].ny){
            show_chess(record[rtop].lastx, record[rtop].lasty, Map[record[rtop].lastx][record[rtop].lasty], 1);
        }
        else{
            show_chess(record[rtop].lastx, record[rtop].lasty, Map[record[rtop].lastx][record[rtop].lasty], 1);
            show_chess(record[rtop].nx, record[rtop].ny, Map[record[rtop].nx][record[rtop].ny], 1);
        }
    }
}

void MainWindow::on_pvsp_clicked(){
    mode = false;
    set_start();
    for(int i = 1; i <= 4; ++i)
        for(int j = 1; j <= 8; ++j)
            show_chess(i, j, 15, 0);
}


void MainWindow::on_pvsai_clicked(){
    mode = true; AI_kind = false;
    set_start();
    for(int i = 1; i <= 4; ++i)
        for(int j = 1; j <= 8; ++j)
            show_chess(i, j, 15, 0);
}



void MainWindow::on_AI_hard_button_clicked(){
    mode = true; AI_kind = true;
    set_start();
    for(int i = 1; i <= 4; ++i)
        for(int j = 1; j <= 8; ++j)
            show_chess(i, j, 15, 0);
}
